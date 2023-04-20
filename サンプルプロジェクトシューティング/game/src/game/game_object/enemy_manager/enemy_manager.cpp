#include "enemy_manager.h"

CEnemyManager::CEnemyManager(aqua::IGameObject* parent, const std::string& name)
{
}

void CEnemyManager::Initialize(void)
{
	Create(aqua::CVector3(0.0f, 0.0f, -50.0f), 20.0f, 20.0f, 20.0f, aqua::CColor::BLACK);
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

	enemy->Initialize(pop_pos, wid, hei, dep, color);
}

void CEnemyManager::Finalize(void)
{
	IGameObject::Finalize();
}
