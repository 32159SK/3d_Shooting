
#include "../../game_object/game_object.h"
#include "bullet_manager.h"
#include "bullet/normal_bullet/normal_bullet.h"
#include "bullet/reflection_bullet/reflection_bullet.h"
#include "bullet/penetrate_bullet/penetrate_bullet.h"

CBulletManager::CBulletManager(aqua::IGameObject* parent)
	: IGameObject(parent,"BulletManager")
	, m_CSVReader(nullptr)
	, m_Player(nullptr)
	, m_Enemy{nullptr}
{
}

void CBulletManager::Initialize(CCSVReader* csv_r, CStageManager* st_m)
{
	m_CSVReader = csv_r;
	m_StageManager = st_m;
	m_CSVReader->Initialize(FILE_TYPE::BULLET_INFO, "bullet_info");

	m_EffectManager = (CEffectManager*)aqua::FindGameObject("EffectManager");

	// for���p�̍s���擾
	int row = m_CSVReader->GetFileRow(FILE_TYPE::BULLET_INFO);
	// �e���̊i�[
	for (int i = 0; i < row; ++i)
		m_BulletInfo.push_back(m_CSVReader->GetBullInfo(i));
}

void CBulletManager::Update(void)
{
	if (m_Player->GetTimeStop())
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
		beam->Initialize(m_BulletInfo[(int)bullet_type], unit_type, shot_pos, shot_front, user, m_EffectManager);
		return;
	}

	// �V������������e�̗e��
 	IBullet* bullet = nullptr;
	// �e�̐��������Ə�����
	switch (bullet_type)
	{
	case BULLET_TYPE::NOMAL:bullet = aqua::CreateGameObject<CNormalBullet>(this);break;
	case BULLET_TYPE::FAST:bullet = aqua::CreateGameObject<CNormalBullet>(this); break;
	case BULLET_TYPE::REFLECT:bullet = aqua::CreateGameObject<CReflectionBullet>(this); break;
	case BULLET_TYPE::PENETRATE:bullet = aqua::CreateGameObject<CPenetrateBullet>(this); break;
	case BULLET_TYPE::MAX:
		break;
	default:
		break;
	}
	bullet->Initialize(m_BulletInfo[(int)bullet_type], unit_type, shot_pos, shot_front, user,m_EffectManager);
}

void CBulletManager::Finalize(void)
{
	m_Enemy.clear();
	IGameObject::Finalize();
}

void CBulletManager::CheakHit(void)
{
	if (m_ChildObjectList.empty())
		return;

	int e_count = (int)m_Enemy.size();

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
			if (!m_Enemy[e])
				continue;
			// ����łȂ��G�ƒe�̏Փˊm�F
			if (!m_Enemy[e]->GetDead()
				&& m_Enemy[e]->CheckHitBullet(bullet->GetAttri(), bullet->GetSphere(), bullet->GetDamage()))
			{
				bullet->Hit();
				return;
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
		if (!m_Enemy[e])
			continue;
		// ����łȂ��G�ƒe�̏Փˊm�F
		if (!m_Enemy[e]->GetDead())
			m_Enemy[e]->CheckHitBeam(beam->GetAttri(), beam->GetCapsule(), beam->GetDamage());
	}

	// �v���C���[�Ƃ̏Փˊm�F
	if (m_Player && !m_Player->GetDead())
		m_Player->CheckHitBeam(beam->GetAttri(), beam->GetCapsule(), beam->GetDamage());
}