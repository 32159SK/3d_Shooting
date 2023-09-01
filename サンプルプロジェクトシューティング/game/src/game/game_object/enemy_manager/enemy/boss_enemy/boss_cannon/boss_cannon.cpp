#include "../../../../game_object.h"
#include "../boss_enemy.h"
#include "boss_cannon.h"

const float CBossCannon::m_player_distance = 100.0f;
const float CBossCannon::m_move_time = 2.0f;
const int   CBossCannon::m_position_pattern = 40;

CBossCannon::CBossCannon(aqua::IGameObject* parent)
	: CEnemy(parent, "BossCannon")
	, m_ShotAngle(0.0f)
	, m_AllRangeAttacking(false)
	, m_ReturnFlag(false)
	, m_AllRangeFinish(true)
	, m_AllRangeState(ALLRANGE_STATE::DEFAULT)
	, m_StartPos(aqua::CVector3::ZERO)
	, m_EndPos(aqua::CVector3::ZERO)
	, m_BossEnemy(nullptr)
	, m_Beam(nullptr)
{
}

void CBossCannon::
Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)
{
	// ロックオンマーカークラスを生成してターゲットをプレイヤーに設定
	m_LockOnMarker = aqua::CreateGameObject<CLockOnMarker>(this);
	m_LockOnMarker->SetTarget(m_Player);

	// モデルのロード
	m_Model.Load("data\\model\\boss_cannon.mv1");

	// 基本的なユニットの初期化を基底クラスの初期化を呼び出して行う
	CEnemy::Initialize(pop_pos, enemy_info, st_m, bm);
}

void CBossCannon::Update(void)
{
	// 射撃はあくまでもボス依存なので継承元のCEnemyのアップデートは呼び出さない
	IGameObject::Update();

	// ボスが死んでなければ自身の行動可能フラグを代入して合わせる
	if (!m_BossEnemy->GetDead())
		m_BossEnemy->SetMoveFlag(m_MoveFlag);

	// 動けないなら処理しない
	if (!m_BossEnemy->GetMoveFlag())
		return;
	Move();

	m_Cube.m_HRotate = m_Rotate;
	m_Model.position = m_Position;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CBossCannon::SetPosition(aqua::CVector3 pos)
{
	// 戻る最中ではない
	if (!m_ReturnFlag)
	{
		// 渡された座標をそのまま代入
		m_Position = pos;
		return;
	}
	else if (m_ReturnFlag && m_EndPos != pos)	// 戻る最中かつ終了地点とposが一致しない(戻ろうとしてから呼び出されていない)
	{
		// 移動先の終点として代入し現在座標を始点にする
		m_EndPos = pos;
		m_StartPos = m_Position;
	}
}

void CBossCannon::SetAllRange(float angle)
{
	// オールレンジ攻撃中フラグを真にし、終了検知フラグを偽にする
	m_AllRangeAttacking = true;
	m_AllRangeFinish = false;
	// 移動タイマーを設定
	m_MoveTimer.Setup(m_move_time);

	// ロックオンフラグを真にする(これでロックオンマーカーが描画される)
	m_LockON = true;

	// 移動の始点に現在座標を代入
	m_StartPos = m_Position;

	// 引数の角度を代入する
	m_ShotAngle = angle;

	m_AllRangeState = ALLRANGE_STATE::MOVE;
}

void CBossCannon::Shot(void)
{
	CEnemy::Shot();
}

void CBossCannon::Move(void)
{
	// 状態に合わせた処理を行う
	switch (m_AllRangeState)
	{
	case CBossCannon::DEFAULT:		Default();			break;
	case CBossCannon::MOVE:			AllRangeMove();		break;
	case CBossCannon::IRRADIATION:	Irradiation();		break;
	case CBossCannon::RETURN:		ReturnPosition();	break;
	}
	m_Cube.position = m_Position;
}

void CBossCannon::Default(void)
{
	// プレイヤーと自身の距離
	aqua::CVector3 v = m_Player->GetPosition() - m_Position;

	// ベクトルのノーマライズ
	v.Normalize();

	// 2点から回転角度を求める
	m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));
}

void CBossCannon::EasingMove(void)
{
	m_MoveTimer.Update();

	aqua::CVector3 easing_pos = aqua::CVector3::ZERO;
	aqua::CVector3 dir = aqua::CVector3::ZERO;

	// イージングで移動先座標を決める
	easing_pos.x = aqua::easing::OutCubic(m_MoveTimer.GetTime(), m_MoveTimer.GetLimit(), m_StartPos.x, m_EndPos.x);
	easing_pos.z = aqua::easing::OutCubic(m_MoveTimer.GetTime(), m_MoveTimer.GetLimit(), m_StartPos.z, m_EndPos.z);

	// 移動の向きを差分で取る
	dir = easing_pos - m_Position;

	// 座標を合わせる
	m_Position = easing_pos;

	// 向きのベクトルに合わせて回転角度を算出
	m_Rotate = aqua::RadToDeg(atan2(dir.x, dir.z));
	m_Cube.m_HRotate = m_Rotate;

	// タイマー終了
	if (m_MoveTimer.Finished())
		// 座標を終点に合わせる
		m_Position = m_EndPos;
}

void CBossCannon::AllRangeMove(void)
{
	// オールレンジ攻撃の終点(発射座標)の仮決め
	m_EndPos = aqua::CVector3(0.0f, 0.0f, m_player_distance);

	// 先ほど取った角度と行列を使ってプレイヤー座標を中心とした回転処理を行う
	aqua::CMatrix mat;
	mat.RotationY(aqua::DegToRad(m_ShotAngle * m_position_pattern));
	mat.Translate(m_Player->GetPosition());

	// 終点の算出完了
	m_EndPos *= mat;

	// イージングで移動させる
	EasingMove();
	// 終点と現在座標が一致したら射撃開始
	if (m_MoveTimer.Finished() && m_EndPos == m_Position)
	{
		m_MoveTimer.Reset();
		// 状態を照射に遷移
		m_AllRangeState = ALLRANGE_STATE::IRRADIATION;
		// ロックオンフラグを偽にする
		m_LockON = false;

		m_ReturnFlag = true;
	}
}

void CBossCannon::Irradiation(void)
{
	// ビームのポインタがnullなら生成しポインタを取得する関数を呼び出す
	if (!m_Beam)
	{
		// 一度基本の動きを呼び出して向きをプレイヤーに合わせる
		Default();

		aqua::CVector3 front;
		front.x = sin(aqua::DegToRad(m_Rotate));
		front.z = cos(aqua::DegToRad(m_Rotate));
		m_Beam = m_BulletManager->CreateGetBeam(m_Position, front, m_UnitType, this);
	}
	// ビームが終了
	else if ( m_Beam && m_Beam->GetFinishFlag())
	{
		// ポインタにnullを代入
		m_Beam = nullptr;
		// ボスエネミーの砲座標セットクラスを呼び出す
		m_BossEnemy->SetCannonPosition(m_BossEnemy->GetRotate());
		// 状態をRETURNへ遷移
		m_AllRangeState = ALLRANGE_STATE::RETURN;
	}
}

void CBossCannon::ReturnPosition(void)
{
	// イージングで移動させる
	EasingMove();
	if (m_MoveTimer.Finished()&&m_Position == m_EndPos)
	{
		m_MoveTimer.Reset();

		// オールレンジ攻撃が完全に終了
		m_AllRangeFinish = true;
		m_AllRangeAttacking = false;
		m_ReturnFlag = false;

		// 始点をリセット
		m_StartPos = aqua::CVector3::ZERO;
		m_EndPos = m_StartPos;

		m_AllRangeState = ALLRANGE_STATE::DEFAULT;
	}
}

void CBossCannon::Dead(void)
{
	m_BossEnemy->ResetCannon(m_CannonNumber);
	CEnemy::Dead();
}

