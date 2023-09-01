
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

	m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");

	m_EnemyList.clear();

	BulletDataLoad();
}

void CBulletManager::Update(void)
{
	// ���g��null�Ȃ珈�����Ȃ�
	if (!this)
		return;
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
		beam->Initialize(m_BulletInfo[(int)bullet_type], unit_type, shot_pos, shot_front, user, m_SoundManager, m_EffectManager);
		return;
	}

	// �V������������e�̗e��
 	IBullet* bullet = nullptr;
	// �e�̐��������Ə�����
	switch (bullet_type)
	{
	case BULLET_TYPE::NORMAL:bullet = aqua::CreateGameObject<CNormalBullet>(this);break;
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
	WaveChange();
	m_EnemyList.clear();
}

void CBulletManager::EnemyReset(CEnemy* enemy)
{
	int e_count = (int)m_EnemyList.size();
	for (int e = 0; e < e_count; ++e)
		if (m_EnemyList[e] == enemy)
			m_EnemyList[e] = nullptr;
}

void CBulletManager::WaveChange(void)
{
	// �q�I�u�W�F�N�g����Ȃ牽�����Ȃ�
	if (m_ChildObjectList.empty())
		return;
	// �q�I�u�W�F�N�g�S��(�t�B�[���h�Ɍ�������e)���폜
	for (auto it : m_ChildObjectList)
	{
		// �r�[���͏����𕪂���(�P���ɍ폜������g�p�҂������Ȃ��Ȃ�)
		if (it->GetGameObjectName() == "Beam")
		{
			CBeam* beam = (CBeam*)it;
			beam->Destroy();
		}
		// ���͂��̂܂܍폜
		if (it)
			it->DeleteObject();
	}
	// ���X�g�̃N���A
	m_ChildObjectList.clear();
}

void CBulletManager::BulletDataLoad(void)
{
	// aqua����CSV�N���X���Ăяo���ă��[�h
	aqua::CCSVLoader csv;
	csv.Load(m_bullet_info_path);

	int file_row = csv.GetRows();

	// �e���̊�����
	BULLET_INFO info;

	for (int i = 0; i < file_row; ++i)
	{
		// �ǂݍ��񂾏�����
		info =
		{
			(BULLET_TYPE)i,
			std::stoi(csv.GetString(i,0)),	// damage
			std::stof(csv.GetString(i,1)),	// radius
			std::stof(csv.GetString(i,2)),	// speed
			csv.GetString(i,3)				// bullet_name
		};
		// �����ɒǉ�
		m_BulletInfo.push_back(info);
	}

	// CSV�̃A�����[�h
	csv.Unload();
}

void CBulletManager::CheakHit(void)
{
	// �v���C���[�܂��͎q�I�u�W�F�N�g(��ԓ��ɑ��݂���e)�����݂��Ȃ��Ȃ珈�����Ȃ�
	if (m_ChildObjectList.empty())
		return;

	int e_count = (int)m_EnemyList.size();

	// ���̃��X�g���g���ČJ��Ԃ�����������
	for (auto it : m_ChildObjectList)
	{
		if (!it)
			continue;
		// it��name���r�[���Ȃ�
		if (it->GetGameObjectName() == "Beam")
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
	// �r�[���Ƀ_���[�W���肪�Ȃ�(�`���[�W��)�Ȃ珈�����Ȃ�
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