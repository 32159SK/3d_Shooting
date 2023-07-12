
#include "../../game_object/game_object.h"
#include "bullet_manager.h"
#include "beam/beam.h"
#include "bullet/normal_bullet/normal_bullet.h"
#include "bullet/reflection_bullet/reflection_bullet.h"
#include "bullet/penetrate_bullet/penetrate_bullet.h"

const std::string CBulletManager::m_bullet_info_path = "data\\csv\\bullet_info.csv";

CBulletManager::CBulletManager(aqua::IGameObject* parent)
	: IGameObject(parent,"BulletManager")
	, m_Player(nullptr)
	, m_EnemyList{nullptr}
{
}

void CBulletManager::Initialize(void)
{
	m_StageManager = (CStageManager*)aqua::FindGameObject("StageManager");

	m_EffectManager = (CEffectManager*)aqua::FindGameObject("EffectManager");

	m_EnemyList.clear();

	BulletDataLoad();
}

void CBulletManager::Update(void)
{
	CheakHit();
	IGameObject::Update();
}

void CBulletManager::Draw(void)
{
	IGameObject::Draw();
}

void CBulletManager::Create(aqua::CVector3 shot_pos, aqua::CVector3 shot_front, UNIT_TYPE unit_type, BULLET_TYPE bullet_type, IUnit* user)
{
	if (bullet_type == BULLET_TYPE::BEAM)
	{
		// �V������������e�̗e��
		CBeam* beam = aqua::CreateGameObject<CBeam>(this);
		beam->Initialize(m_BulletInfo[(int)bullet_type], unit_type, shot_pos, shot_front, user, m_EffectManager);
		return;
	}

	// �V������������e�̗e��
 	IBullet* bullet = nullptr;
	// �e�̐��������Ə�����
	switch (bullet_type)
	{
	case BULLET_TYPE::NOMAL:bullet = aqua::CreateGameObject<CNormalBullet>(this);break;
	case BULLET_TYPE::REFLECT:bullet = aqua::CreateGameObject<CReflectionBullet>(this); break;
	case BULLET_TYPE::PENETRATE:bullet = aqua::CreateGameObject<CPenetrateBullet>(this); break;
	case BULLET_TYPE::MAX:
		break;
	default:
		break;
	}
	bullet->Initialize(m_BulletInfo[(int)bullet_type], unit_type, shot_pos, shot_front, user,m_EffectManager);
}

CBeam* CBulletManager::CreateGetBeam(aqua::CVector3 shot_pos, aqua::CVector3 shot_front, UNIT_TYPE unit_type, IUnit* user)
{
	Create(shot_pos, shot_front, unit_type, BULLET_TYPE::BEAM, user);
	return (CBeam*)m_ChildObjectList.back();
}

void CBulletManager::Finalize(void)
{
	m_EnemyList.clear();
	IGameObject::Finalize();
}

void CBulletManager::EnemyReset(void)
{
	if (m_EnemyList.empty())
		return;

	m_EnemyList.clear();
}

void CBulletManager::EnemyReset(CEnemy* enemy)
{
	int e_count = (int)m_EnemyList.size();
	for (int e = 0; e < e_count; ++e)
		if (m_EnemyList[e] == enemy)
			m_EnemyList[e] = nullptr;
}

void CBulletManager::BulletDataLoad(void)
{
	aqua::CCSVLoader csv;
	csv.Load(m_bullet_info_path);

	int file_row = csv.GetRows();

	BULLET_INFO info;
	for (int i = 0; i < file_row; ++i)
	{
		info =
		{
			(BULLET_TYPE)i,
			std::stoi(csv.GetString(i,0)),	// damage
			std::stof(csv.GetString(i,1)),	// radius
			std::stof(csv.GetString(i,2))	// speed
		};
		m_BulletInfo.push_back(info);
	}

	csv.Unload();

}

void CBulletManager::CheakHit(void)
{
	if (m_ChildObjectList.empty())
		return;

	int e_count = (int)m_EnemyList.size();

	// ���̃��X�g���g���ČJ��Ԃ�����������
	for (auto it : m_ChildObjectList)
	{
		// it�̃J�e�S���[��Bullet�łȂ��Ȃ�
		if (it->GetGameObjectCategory() != "Bullet")
		{
			CheakHitBeam((CBeam*)it,e_count);
			continue;
		}
		IBullet* bullet = (IBullet*)it;


		for (int e = 0; e < e_count; ++e)
		{
			if (m_EnemyList[e] != nullptr)
			{
				// ����łȂ��G�ƒe�̏Փˊm�F
				if (!m_EnemyList[e]->GetDead()
					&& m_EnemyList[e]->CheckHitBullet(bullet->GetAttri(), bullet->GetSphere(), bullet->GetDamage()))
				{
					bullet->Hit();
					// ���񂾂�|�C���^���폜
					if (m_EnemyList[e]->GetDead())
						m_EnemyList.erase(m_EnemyList.begin() + e);
					return;
				}
			}
		}
		
		// �v���C���[�Ƃ̏Փˊm�F
		if (m_Player && !m_Player->GetDead() && m_Player->CheckHitBullet(bullet->GetAttri(), bullet->GetSphere(), bullet->GetDamage()))
		{
			bullet->Hit();
			return;
		}

		// �X�e�[�W�I�u�W�F�N�g�Ƃ̏Փˊm�F(�u���b�N��)
		if (m_StageManager->StageObjectCollision(bullet->GetPosition(), bullet->GetDestination(),true))
		{
			bullet->StageObjectHit(m_StageManager->GetCollDire());
			return;
		}
	}

}

void CBulletManager::CheakHitBeam(CBeam* beam,int e_count)
{
	if (!beam->GetDamageFlag())
		return;

	for (int e = 0; e < e_count; ++e)
	{
		if (!m_EnemyList[e])
			continue;
		// ����łȂ��G�ƒe�̏Փˊm�F
		if (!m_EnemyList[e]->GetDead())
			m_EnemyList[e]->CheckHitBeam(beam->GetAttri(), beam->GetCapsule(), beam->GetDamage());
	}

	// �v���C���[�Ƃ̏Փˊm�F
	if (m_Player && !m_Player->GetDead())
		m_Player->CheckHitBeam(beam->GetAttri(), beam->GetCapsule(), beam->GetDamage());
}