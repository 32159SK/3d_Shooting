#include "bullet_manager.h"
#include "bullet/nomal_bullet/nomal_bullet.h"


CBulletManager::CBulletManager(aqua::IGameObject* parent, const std::string& name)
	: IGameObject(parent,"BulletManager")
{
}

void CBulletManager::Initialize(void)
{
}

void CBulletManager::Update(void)
{
}

void CBulletManager::Draw(void)
{
}

void CBulletManager::Create(aqua::CVector3 shot_pos,UNIT_TYPE unit_type, BULLET_TYPE bullet_type)
{
	IBullet* bullet = nullptr;
	switch (bullet_type)
	{
	case BULLET_TYPE::NOMAL:
		bullet = aqua::CreateGameObject<CNomalBullet>(this);
		bullet->Initialize(m_BulletInfo, unit_type, shot_pos);
		break;
	}

}

void CBulletManager::Finalize(void)
{
}
