
#include "../game_object.h"
#include "enemy_manager.h"

CEnemyManager::CEnemyManager(aqua::IGameObject* parent)
	: IGameObject(parent, "EnemyManager")
	, m_Player(nullptr)
	, m_BulletManagar(nullptr)
	, m_EnemyCount(0)
{
}

void CEnemyManager::Initialize(CBulletManager* bm, CPlayer* player, CRader* rader)
{
	m_Player = player;
	m_BulletManagar = bm;
	m_Rader = rader;

	Create(aqua::CVector3(0.0f, 0.0f, 50.0f), 15.0f, 15.0f, 15.0f, aqua::CColor::WHITE);
	Create(aqua::CVector3::ZERO, 15.0, 15.0f, 15.0f, aqua::CColor::BLACK);

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
	enemy->SetPlayer(m_Player);
	m_EnemyCount++;

	m_BulletManagar->SetEnemy(enemy);
	m_Rader->SetEnemy(enemy);
}

void CEnemyManager::Finalize(void)
{
	IGameObject::Finalize();
}
