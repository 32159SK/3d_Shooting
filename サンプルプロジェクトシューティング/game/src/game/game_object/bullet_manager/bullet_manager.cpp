#include "../../game_object/game_object.h"
#include "bullet_manager.h"
#include "bullet/normal_bullet/normal_bullet.h"


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

	// for文用の行数取得
	int row = m_CSVReader->GetFileRow(FILE_TYPE::BULLET_INFO);
	// 弾情報の格納
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
	// 新しく生成する弾の容器
 	IBullet* bullet = nullptr;
	// 弾の生成処理と初期化
 	bullet = aqua::CreateGameObject<CNormalBullet>(this);
	bullet->Initialize(m_BulletInfo[(int)bullet_type], unit_type, shot_pos, shot_front, user);
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

	int e_count = m_Enemy.size();

	// このリストを使って繰り返し処理をする
	for (auto it : m_ChildObjectList)
	{
		IBullet* bullet = (IBullet*)it;
		for (int e = 0; e < e_count; ++e)
		{
			// 死んでない敵と弾の衝突確認
			if (m_Enemy[e] && !m_Enemy[e]->GetDead()
				&& m_Enemy[e]->CheckHitBullet(bullet->GetAttri(), bullet->GetSphere(), bullet->GetDamage()))
			{
				bullet->Hit();
				return;
			}
		}

		// プレイヤーとの衝突確認
		if (m_Player && !m_Player->GetDead() && m_Player->CheckHitBullet(bullet->GetAttri(), bullet->GetSphere(), bullet->GetDamage()))
		{
			bullet->Hit();
			return;
		}

		// ステージオブジェクトとの衝突確認(ブロック等)
		if (m_StageManager->StageObjectCollision(bullet->GetPosition(), bullet->GetDestination()))
		{
			bullet->Hit();
			return;
		}
	}


}


