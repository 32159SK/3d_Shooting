
#include "../game_object.h"
#include "enemy_manager.h"
#include "enemy/mob_normal/mob_enemy.h"
#include "enemy/along_wall/along_wall.h"
#include "enemy/fixed_enemy/fixed_enemy.h"

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
	CEnemy* enemy = nullptr;
	switch (enemy_info.id)
	{
	case ENEMY_ID::MOB:  enemy = aqua::CreateGameObject<CMobEnemy>(this); break;
	case ENEMY_ID::ALONG_WALL: enemy = aqua::CreateGameObject<CFixedEnemy>(this); break;
	case ENEMY_ID::FIXED: enemy = aqua::CreateGameObject<CFixedEnemy>(this); break;
	default:
		break;
	}

		

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

CEnemy* CEnemyManager::GetNearest(aqua::CVector3 player_pos)
{
	if (m_ChildObjectList.empty())
		return nullptr;


	// 最も近い敵
	CEnemy* nearestEnemy = nullptr;

	for (auto it : m_ChildObjectList)
	{
		CEnemy* enemy = (CEnemy*)it;

		// 最も近い敵がまだ見つかっていない場合、仮で代入する
		if (!nearestEnemy) nearestEnemy = enemy;

		// 敵とプレイヤーの距離
		float nearestDistance = abs(aqua::CVector3::Length(nearestEnemy->GetPosition() - player_pos));
		float itDistance = abs(aqua::CVector3::Length(enemy->GetPosition() - player_pos));

		// よりプレイヤーに近い敵をnearestEnemyにする
		if (itDistance < nearestDistance) nearestEnemy = enemy;

		// プレイヤーと敵の間に壁があればnull
		if (m_StageManager->StageObjectCollision(enemy->GetPosition(), player_pos, false))
			nearestEnemy = nullptr;

	}
	return nearestEnemy;
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
			Create(m_PopList[i].pop_pos, m_EnemyInfo[(int)m_PopList[i].pop_e_id]);

	// waveに合わせてフィールドを切り替える
   	m_StageManager->WaveChange(m_WaveCount);
	m_WaveCount++;
}