
#include "../game_object.h"
#include "enemy_manager.h"
#include "enemy/mob_normal/mob_enemy.h"
#include "enemy/along_wall/along_wall.h"
#include "enemy/fixed_enemy/fixed_enemy.h"
#include "enemy/boss_enemy/boss_enemy.h"
#include "enemy/boss_enemy/boss_cannon/boss_cannon.h"

const int CEnemyManager::m_max_wave = 4;
const int CEnemyManager::m_heal_value = 3;
const std::string CEnemyManager::m_enemy_info_path = "data\\csv\\enemy_info.csv";
const std::string CEnemyManager::m_pop_list_path = "data\\csv\\pop_list.csv";

CEnemyManager::CEnemyManager(aqua::IGameObject* parent)
	: IGameObject(parent, "EnemyManager")
	, m_Player(nullptr)
	, m_BulletManagar(nullptr)
	, m_EnemyCount(0)
	, m_WaveCount(1)
	, m_Finish(false)
{
}

void CEnemyManager::Initialize(CBulletManager* bm, CPlayer* player, CStageManager* st_m, CRader* rader)
{
	m_Player = player;
	m_BulletManagar = bm;
	m_StageManager = st_m;
	m_Rader = rader;
	EnemyDataLoad();
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

void CEnemyManager::Create(aqua::CVector3 pop_pos, ENEMY_ID enemy_id)
{
	// 空のエネミークラスを用意
	CEnemy* enemy = nullptr;
	switch (enemy_id)
	{
	case ENEMY_ID::MOB:  enemy = aqua::CreateGameObject<CMobEnemy>(this); break;
	case ENEMY_ID::ALONG_WALL: enemy = aqua::CreateGameObject<CAlongWallEnemy>(this); break;
	case ENEMY_ID::FIXED: enemy = aqua::CreateGameObject<CFixedEnemy>(this); break;
	case ENEMY_ID::BOSS: enemy = aqua::CreateGameObject<CBossEnemy>(this); break;
	case ENEMY_ID::BOSS_CANNON: enemy = aqua::CreateGameObject<CBossCannon>(this); break;
	default:
		break;
	}

	// 初期化とプレイヤーのポインタを渡す
	enemy->SetPlayer(m_Player);
	enemy->Initialize(pop_pos, m_EnemyInfo[(int)enemy_id], m_StageManager, m_BulletManagar);

	m_EnemyCount++;

	// 弾との衝突確認用に弾管理クラスに生成したエネミーのポインタを渡す
	m_BulletManagar->SetEnemy(enemy);
	m_Rader->SetEnemy(enemy);
}

void CEnemyManager::Finalize(void)
{
	IGameObject::Finalize();
	m_EnemyInfo.clear();
	m_PopList.clear();
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

		// プレイヤーと敵の間に壁があれば次へ(ここでやっておかないと"壁の向こう側だが最も近い敵"にロックオンを合わせようとして何度やっても失敗する)
		if (m_StageManager->StageObjectCollision(enemy->GetPosition(), player_pos, false))
			continue;

		// 敵とプレイヤーの距離
		float nearestDistance = abs(aqua::CVector3::Length(nearestEnemy->GetPosition() - player_pos));
		float itDistance = abs(aqua::CVector3::Length(enemy->GetPosition() - player_pos));

		// よりプレイヤーに近い敵をnearestEnemyにする
		if (itDistance < nearestDistance) nearestEnemy = enemy;

	}

	return nearestEnemy;
}

CEnemy* CEnemyManager::CreateBossParts(aqua::CVector3 pop_pos, ENEMY_ID enemy_id)
{
	// 渡された情報から敵を生成
	Create(pop_pos, enemy_id);
	// 末尾の要素(直前に生成された敵)のポインタを返す
	return (CEnemy*)m_ChildObjectList.back();
}

void CEnemyManager::EnemyDataLoad(void)
{
	aqua::CCSVLoader csv;
	csv.Load(m_enemy_info_path);

	int file_row = csv.GetRows();

	ENEMY_INFO info;

	for (int i = 0; i < file_row; ++i)
	{
		info =
		{
			(ENEMY_ID)i,					// id
				std::stoi(csv.GetString(i, 0)),	// life
				std::stof(csv.GetString(i, 1)),	// width
				std::stof(csv.GetString(i, 2)),	// height
				std::stof(csv.GetString(i, 3)),	// depth
				std::stof(csv.GetString(i, 4)),	// speed
				std::stof(csv.GetString(i, 5))	// shot_ct
		};
		m_EnemyInfo.push_back(info);
	}

	csv.Load(m_pop_list_path);

	file_row = csv.GetRows();

	ENEMY_POP_LIST pop_list;

	for (int i = 0; i < file_row; ++i)
	{
		pop_list =
		{
			std::stoi(csv.GetString(i,0)),	// wave
			(ENEMY_ID)std::stoi(csv.GetString(i,1))		// e_id
		};
		m_PopList.push_back(pop_list);
	}

	csv.Unload();
}

void CEnemyManager::WaveChange(void)
{
	if (m_WaveCount > m_max_wave)
		return;

	m_BulletManagar->EnemyReset();

	// waveのクリア時にプレイヤーのライフを回復させる
	m_Player->LifeHeal(m_heal_value);

	// waveに合わせてフィールドを切り替える
   	m_StageManager->WaveChange(m_WaveCount);

	for (int i = 0; i < m_PopList.size(); ++i)
		if (m_PopList[i].wave == m_WaveCount && m_EnemyCount < m_StageManager->GetEnemyCount())
			Create(m_StageManager->GetEnemyPopPos(i), m_PopList[m_EnemyCount].pop_e_id);
	//ボスの動作試験用なのでコメントアウト
	//Create(m_StageManager->GetEnemyPopPos(0), m_PopList[18].pop_e_id);

	m_WaveCount++;
}