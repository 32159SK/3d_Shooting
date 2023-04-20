
#include "enemy_manager.h"
#include "../game_object.h"

CEnemyManager::CEnemyManager(aqua::IGameObject* parent, const std::string& name)
	: IGameObject(parent,"EnemyManager")
{
}

void CEnemyManager::Initialize(CBulletManager* bm, CPlayer* player)
{
	m_Player = player;
	m_BulletManagar = bm;
}

void CEnemyManager::Update(void)
{
	IGameObject::Update();
}

void CEnemyManager::Draw(void)
{
	IGameObject::Draw();
}

void CEnemyManager::Create(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color)
{
	CEnemy* enemy = aqua::CreateGameObject<CEnemy>(this);

	enemy->Initialize(pop_pos, wid, hei, dep, color,m_BulletManagar);
}

void CEnemyManager::Finalize(void)
{
	IGameObject::Finalize();
}
