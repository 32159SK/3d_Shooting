#include "../game_object.h"
#include "player.h"

const float CPlayer::m_change_shotCT = 0.5f;
const float CPlayer::m_ago_pos_time = 0.2f;
const float CPlayer::m_lock_range = 200.0f;
const int   CPlayer::m_max_life = 20;

CPlayer::CPlayer(aqua::IGameObject* parent)
	: IUnit(parent,"Player")
	, m_AgoPosition(aqua::CVector3::ZERO)
	, m_Invincible(false)
	, m_EnemyManager(nullptr)
	, m_LockOnEnemy(nullptr)
{
}

void CPlayer::Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m, CBulletManager* bm)
{
	// ロックオンマーカークラスを生成しポインタを入れる
	m_LockOnMarker = aqua::CreateGameObject<CLockOnMarker>(this);

	// ライフ最大値を代入
	m_MaxLife = m_max_life;
	m_Life = m_MaxLife;

	// 基本的なユニットの初期化を基底クラスの初期化を呼び出して行う
	IUnit::Initialize(pop_pos, wid, hei, dep, color, st_m, bm);
	

	m_UnitType = UNIT_TYPE::PLAYER;
	m_ShotBullet = BULLET_TYPE::NORMAL;
	m_BulletManager->SetPlayer(this);
	m_Speed = 1.0f;

	// 無敵時間の設定
	m_InvincibleTimer.Setup(2.0f);

	// 現在の弾種の仮表示
	m_DrawBT.Create(30.0f);
	m_DrawBT.position = aqua::CVector2(aqua::GetWindowWidth() / 2.0f, 0.0f);

	// 弾種切り替えタイマーのセットアップ
	m_ChangeCT.Setup(m_change_shotCT);
	m_ShotCT.Setup(0.5f);
	
	// 追尾座標間隔タイマーのセットアップ
	m_AgoPosTimer.Setup(m_ago_pos_time);

	// ロックオンタイマーのセットアップ
	m_LockonTimer.Setup(0.1f);

	m_Cube.visible = false;
	// モデルのロード
	m_Model.Load("data\\model\\player.mv1");

}

void CPlayer::Update(void)
{
	// キューブの水平回転角度を合わせる
	m_Cube.m_HRotate = m_Rotate;
	// 追尾座標間隔タイマーの更新
	m_AgoPosTimer.Update();
	// 射撃
	Shot();
	
	// 無敵状態ならタイマーを更新
	if (m_Invincible)
		m_InvincibleTimer.Update();
	// 終了時に無敵を解除しタイマーをリセット
	if (m_InvincibleTimer.Finished())
	{
		m_Invincible = false;
		m_InvincibleTimer.Reset();
	}

	// ユニットの更新
	IUnit::Update();

	// ここで敵が追尾する用のポジションを取っておく
	if (m_AgoPosTimer.Finished())
	{
		m_AgoPosition = m_Position;
		m_AgoPosTimer.Reset();
	}

	// モデルの座標と回転角度を合わせる
	m_Model.position = m_Cube.position;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CPlayer::Draw(void)
{
	switch (m_ShotBullet)
	{
	case BULLET_TYPE::NORMAL:	m_DrawBT.text = "BULLET:NOMAL"; break;
	case BULLET_TYPE::REFLECT:	m_DrawBT.text = "BULLET:REFLECT"; break;
	case BULLET_TYPE::PENETRATE:m_DrawBT.text = "BULLET:PENETRATE"; break;
	case BULLET_TYPE::BEAM:		m_DrawBT.text = "BULLET:BEAM"; break;
	
	default:
		break;
	}
	// 
	m_DrawBT.Draw();
	m_Model.Draw();
	IUnit::Draw();
}

void CPlayer::Finalize(void)
{
	IUnit::Finalize();
	m_DrawBT.Delete();
	m_Model.Unload();
}

bool CPlayer::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)
{
	// 無敵なら処理をやめる
	if (m_Invincible)
		return false;
	// 基底ユニットクラスの被弾確認を呼び出し当たっていたら無敵フラグを真にする
	if (IUnit::CheckHitBullet(type, sphere, damage))
	{
		m_Invincible = true;
		return true;
	}
	else
		return false;
}

bool CPlayer::CheckHitBeam(UNIT_TYPE type, aqua::CCapsulePrimitive capsule, int damage)
{
	// 無敵なら処理をやめる
	if (m_Invincible)
		return false;
	// 基底ユニットクラスの被弾確認を呼び出し当たっていたら無敵フラグを真にする
	if (IUnit::CheckHitBeam(type, capsule, damage))
	{
		m_Invincible = true;
		return true;
	}
	else
		return false;
}

void CPlayer::LifeHeal(int heal_value)
{
	// 回復値と現在残ライフの計が上限を超えるなら上限に合わせる
	if (m_max_life <= m_Life + heal_value)
		m_Life = m_max_life;
	else
		m_Life += heal_value;	// 越えなければそのまま回復値分加算する
}

void CPlayer::Shot(void)
{
	// 弾種切り替えタイマーと射撃タイマーの更新
	m_ChangeCT.Update();
	m_ShotCT.Update();

	if (!m_MoveFlag)
		return;

	// 弾の種類の切り替え
	if (m_ChangeCT.Finished())
	{
		if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::UP) && m_ShotBullet != BULLET_TYPE::NORMAL)
		{
			// -1の弾に変更(例FAST→NOMAL)
			m_ShotBullet = (BULLET_TYPE)((int)m_ShotBullet - 1);
			m_ChangeCT.Reset();
		}
		// ↓キー
		if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::DOWN) && (int)m_ShotBullet < (int)BULLET_TYPE::MAX - 1)
		{
			// +1の弾に変更(例NOMAL→FAST)
			m_ShotBullet = (BULLET_TYPE)((int)m_ShotBullet + 1);
			m_ChangeCT.Reset();
		}

	}

	// 正面座標
	aqua::CVector3 front;

	front.x = sin(aqua::DegToRad(m_Rotate));
	front.z = cos(aqua::DegToRad(m_Rotate));

	if (m_ShotCT.Finished())
	{
		if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::SPACE))
		{
			// 自機の正面から球を撃つ
			m_BulletManager->Create(m_Position + front * 10.0f, front * 10.5f, m_UnitType, m_ShotBullet, this);
			m_ShotCT.Reset();
		}
	}
}

void CPlayer::Move(void)
{
	using namespace aqua::keyboard;
	const float to_delta = 60.0f * aqua::GetDeltaTime();

	// 移動速度は更新の度にリセット
	m_Velocity = aqua::CVector3::ZERO;

	// 行動不可(ビーム待機中)なら処理を止める
	if (!m_MoveFlag)
		return;


	if (Button(KEY_ID::W)) m_Velocity += aqua::CVector3::FRONT;
	if (Button(KEY_ID::S)) m_Velocity += aqua::CVector3::BACK;
	if (Button(KEY_ID::A)) m_Velocity += aqua::CVector3::LEFT;
	if (Button(KEY_ID::D)) m_Velocity += aqua::CVector3::RIGHT;

	if (Button(KEY_ID::RIGHT)) m_Rotate += 2.0f;
	if (Button(KEY_ID::LEFT)) m_Rotate -= 2.0f;

	m_Velocity = m_Velocity.Normalize();
	m_Velocity *= (m_Speed * to_delta);

	// ロックオン
	LockOn();

	
	// 壁と当たってたらそこで止まる
	if (m_StageManager->StageObjectCollision(m_Position, m_Position + m_Velocity * m_Width, false))
		return;

	// 座標に移動速度を加算する
	m_Position += m_Velocity;
	AQUA_DEBUG_LOG("X:" + std::to_string(m_Position.x) + ",Z" + std::to_string(m_Position.z));
}

void CPlayer::LockOn(void)
{
	// ロックオンタイマーの更新
	m_LockonTimer.Update();

	// タイマーが終了しているかつ、キーが入力された
	if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::Q) && m_LockonTimer.Finished())
	{
		m_LockON = !m_LockON;
		// 一度ロックオンした同じ敵を近くないのに再度ロックオンしないようnullを与える
		m_LockOnEnemy = nullptr;
		m_LockOnMarker->SetTarget(m_LockOnEnemy);
		m_LockonTimer.Reset();
	}

	// そもそもロックオンしてない(余計な処理をしないようif文は分ける)
	if (!m_LockON)
		return;

	// エネミーがnullまたは、取得したエネミーが死んだ
	if (!m_LockOnEnemy || m_LockOnEnemy->GetDead())
	{
		m_LockOnEnemy = m_EnemyManager->GetNearest(m_Position);
		m_LockOnMarker->SetTarget(m_LockOnEnemy);
		return;
	}

	// プレイヤーと自身の距離
	aqua::CVector3 v = m_LockOnEnemy->GetPosition() - m_Position;

	// 範囲外ならロックオンを終了
	if (m_lock_range < abs(aqua::CVector3::Length(v)))
	{
		m_LockOnEnemy = nullptr;
		m_LockOnMarker->SetTarget(m_LockOnEnemy);
		m_LockON = false;
		return;
	}

	// ベクトルのノーマライズ
	v.Normalize();

	// 2点から回転角度を求める
	m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));
}
