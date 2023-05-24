
#include "../game_object.h"
#include "enemy_manager.h"

const int CEnemyManager::m_max_wave = 2;

CEnemyManager::CEnemyManager(aqua::IGameObject* parent)
	: IGameObject(parent, "EnemyManager")
	, m_Player(nullptr)
	, m_BulletManagar(nullptr)
	, m_EnemyCount(0)
	, m_WaveCount(1)
	, m_Finish(false)
{
}

void CEnemyManager::Initialize(CCSVReader* csv_r, CBulletManager* bm, CPlayer* player, CStageManager* st_m, CRader* rader)
{
	m_CSVReader = csv_r;
	m_Player = player;
	m_BulletManagar = bm;
	m_StageManager = st_m;
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
	if (m_Player->GetTimeStop())
		return;

	IGameObject::Update();


	if (m_ChildObjectList.empty())
		WaveChange();
}

void CEnemyManager::Draw(void)
{
	IGameObject::Draw();
}

void CEnemyManager::Create(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info)
{
	// 空のエネミークラスを用意
	CAlongWallEnemy* enemy = aqua::CreateGameObject<CAlongWallEnemy>(this);

	// 初期化とプレイヤーのポインタを渡す
	enemy->Initialize(pop_pos, enemy_info.width, enemy_info.height, enemy_info.depth, enemy_info.color, m_StageManager, m_BulletManagar);
	enemy->SetPlayer(m_Player);
	m_EnemyCount++;

	// 弾との衝突確認用に弾管理クラスに生成したエネミーのポインタを渡す
	m_BulletManagar->SetEnemy(enemy);
	m_Rader->SetEnemy(enemy);
}

void CEnemyManager::Finalize(void)
{
	IGameObject::Finalize();
}

void CEnemyManager::WaveChange(void)
{
	if (m_WaveCount > m_max_wave)
	{
		m_Finish = true;
		return;
	}
	m_EnemyCount = 0;
	m_BulletManagar->EnemyReset();

	for (int i = 0; i < m_PopList.size(); ++i)
		if (m_PopList[i].wave == m_WaveCount) 
			Create(m_PopList[i].pop_pos, m_EnemyInfo[1]);

	// waveに合わせてフィールドを切り替える
   	m_StageManager->WaveChange(m_WaveCount);
	m_WaveCount++;
}