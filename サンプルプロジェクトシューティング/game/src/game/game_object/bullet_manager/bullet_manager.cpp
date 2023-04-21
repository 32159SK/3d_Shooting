#include "../../game_object/game_object.h"
#include "bullet_manager.h"
#include "bullet/nomal_bullet/nomal_bullet.h"


CBulletManager::CBulletManager(aqua::IGameObject* parent)
	: IGameObject(parent,"BulletManager")
{
}

void CBulletManager::Initialize(void)
{
}

void CBulletManager::Update(void)
{
	IGameObject::Update();
	CheakHit();
}

void CBulletManager::Draw(void)
{
	IGameObject::Draw();
}

void CBulletManager::Create(aqua::CVector3 shot_pos, UNIT_TYPE unit_type, BULLET_TYPE bullet_type, IUnit* user)
{
	IBullet* bullet = nullptr;
	switch (bullet_type)
	{
	case BULLET_TYPE::NOMAL:
		bullet = aqua::CreateGameObject<CNomalBullet>(this);
		bullet->Initialize(m_BulletInfo, unit_type, shot_pos, user);
		break;
	}
	m_Bullet.push_back(bullet);
}

void CBulletManager::Finalize(void)
{
	m_Enemy.clear();
	m_Bullet.clear();
}

void CBulletManager::CheakHit(void)
{
	if (m_ChildObjectList.empty())
		return;

	
	int s_count = m_Bullet.size();
	int e_count = m_Enemy.size();

	for (int s = 0; s < s_count; ++s)
		for (int e = 0; e < e_count; ++e)
			if (m_Enemy[e]&&!m_Enemy[e]->GetDead() && m_Enemy[e]->CheckHitBullet(m_Bullet[s]->GetAttri(), m_Bullet[s]->GetSphere(), m_Bullet[s]->GetDamage()))
				m_Bullet[s]->Hit();

	for (int s = 0; s < s_count; ++s)
		if (m_Player && m_Player->GetDead(), m_Player->CheckHitBullet(m_Bullet[s]->GetAttri(), m_Bullet[s]->GetSphere(), m_Bullet[s]->GetDamage()))
			m_Bullet[s]->Hit();
}


