
#include "../../game_object/game_object.h"
#include "bullet_manager.h"
#include "bullet/normal_bullet/normal_bullet.h"
#include "bullet/reflection_bullet/reflection_bullet.h"
#include "bullet/penetrate_bullet/penetrate_bullet.h"

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

	m_EffectManager = (CEffectManager*)aqua::FindGameObject("EffectManager");

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

	if (bullet_type == BULLET_TYPE::BEAM)
	{
		// 新しく生成する弾の容器
		CBeam* beam = aqua::CreateGameObject<CBeam>(this);
		beam->Initialize(m_BulletInfo[(int)bullet_type], unit_type, shot_pos, shot_front, user, m_EffectManager);
		return;
	}

	// 新しく生成する弾の容器
 	IBullet* bullet = nullptr;
	// 弾の生成処理と初期化
	switch (bullet_type)
	{
	case BULLET_TYPE::NOMAL:bullet = aqua::CreateGameObject<CNormalBullet>(this);break;
	case BULLET_TYPE::FAST:bullet = aqua::CreateGameObject<CNormalBullet>(this); break;
	case BULLET_TYPE::REFLECT:bullet = aqua::CreateGameObject<CReflectionBullet>(this); break;
	case BULLET_TYPE::PENETRATE:bullet = aqua::CreateGameObject<CPenetrateBullet>(this); break;
	case BULLET_TYPE::MAX:
		break;
	default:
		break;
	}
	bullet->Initialize(m_BulletInfo[(int)bullet_type], unit_type, shot_pos, shot_front, user,m_EffectManager);
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

	int e_count = (int)m_Enemy.size();

	// このリストを使って繰り返し処理をする
	for (auto it : m_ChildObjectList)
	{
		// itのカテゴリーがBulletでないなら
		if (it->GetGameObjectCategory() != "Bullet")
		{
			CheakHitBeam((CBeam*)it,e_count);
			continue;
		}
		IBullet* bullet = (IBullet*)it;

		for (int e = 0; e < e_count; ++e)
		{
			if (!m_Enemy[e])
				continue;
			// 死んでない敵と弾の衝突確認
			if (!m_Enemy[e]->GetDead()
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
		if (m_StageManager->StageObjectCollision(bullet->GetPosition(), bullet->GetDestination(),true))
		{
			bullet->StageObjectHit(m_StageManager->GetCollDire());
			return;
		}
	}

}

void CBulletManager::CheakHitBeam(CBeam* beam,int e_count)
{
	if (!beam->GetDamageFlag())
		return;

	for (int e = 0; e < e_count; ++e)
	{
		if (!m_Enemy[e])
			continue;
		// 死んでない敵と弾の衝突確認
		if (!m_Enemy[e]->GetDead())
			m_Enemy[e]->CheckHitBeam(beam->GetAttri(), beam->GetCapsule(), beam->GetDamage());
	}

	// プレイヤーとの衝突確認
	if (m_Player && !m_Player->GetDead())
		m_Player->CheckHitBeam(beam->GetAttri(), beam->GetCapsule(), beam->GetDamage());
}