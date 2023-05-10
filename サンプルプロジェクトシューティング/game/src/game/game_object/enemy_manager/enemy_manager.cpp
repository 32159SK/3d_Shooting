
#include "../game_object.h"
#include "enemy_manager.h"

CEnemyManager::CEnemyManager(aqua::IGameObject* parent)
	: IGameObject(parent, "EnemyManager")
	, m_Player(nullptr)
	, m_BulletManagar(nullptr)
	, m_EnemyCount(0)
	, m_WaveCount(0)
	, m_Finish(false)
{
}

void CEnemyManager::Initialize(CBulletManager* bm, CPlayer* player, CRader* rader)
{
	m_CSVReader = (CCSVReader*)aqua::FindGameObject("CSVReader");
	m_Player = player;
	m_BulletManagar = bm;
	m_Rader = rader;

	m_CSVReader->Initialize(FILE_TYPE::POP_LIST, "pop_list");
	int row = m_CSVReader->GetFileRow(FILE_TYPE::POP_LIST);
	for (int i = 0; i < row; ++i)
		m_PopList.push_back(m_CSVReader->GetPopList(i));

	m_CSVReader->Initialize(FILE_TYPE::ENEMY_INFO, "enemy_info");
	row = m_CSVReader->GetFileRow(FILE_TYPE::ENEMY_INFO);
	for (int i = 0; i < row; ++i)
		m_EnemyInfo.push_back(m_CSVReader->GetEneInfo(i));

}

void CEnemyManager::Update(void)
{
	IGameObject::Update();


	if (m_ChildObjectList.empty())
		WaveChange();
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

void CEnemyManager::Create(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info)
{
	CEnemy* enemy = aqua::CreateGameObject<CEnemy>(this);

	enemy->Initialize( pop_pos, enemy_info.width, enemy_info.height, enemy_info.depth, enemy_info.color, m_BulletManagar);
	enemy->SetPlayer(m_Player);
	m_EnemyCount++;

	m_BulletManagar->SetEnemy(enemy);
	m_Rader->SetEnemy(enemy);

}

void CEnemyManager::Finalize(void)
{
	IGameObject::Finalize();
}

void CEnemyManager::WaveChange(void)
{
	if (m_WaveCount > 3)
	{
		m_Finish = true;
		return;
	}
	m_EnemyCount = 0;
	m_BulletManagar->EnemyReset();

	for (int i = 0; i < m_PopList.size(); ++i)
		if (m_PopList[i].wave == m_WaveCount+1) 
			Create(m_PopList[i].pop_pos, m_EnemyInfo[1]);

	m_WaveCount++;
}