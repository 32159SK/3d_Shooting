#include "../../../../game_object.h"
#include "../boss_enemy.h"
#include "boss_cannon.h"

const float CBossCannon::m_player_distance = 100.0f;
const float CBossCannon::m_move_time = 5.0f;
const int   CBossCannon::m_position_pattern = 12;

CBossCannon::CBossCannon(aqua::IGameObject* parent)
	: CEnemy(parent, "BossCannon")
	, m_ShotAngle(0.0f)
	, m_AllRangeAttacking(false)
	, m_ReturnFlag(false)
	, m_AllRangeFinish(false)
	, m_StartPos(aqua::CVector3::ZERO)
	, m_EndPos(aqua::CVector3::ZERO)
{
}

void CBossCannon::
Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)
{
	CEnemy::Initialize(pop_pos, enemy_info, st_m, bm);
	// モデルは仮
	m_Model.Load("data\\model\\fixed_enemy.mv1");
	m_Model.position = m_Position;

	m_BossEnemy = (CBossEnemy*)aqua::FindGameObject("BossEnemy");

	m_Cube.visible = false;
}

void CBossCannon::Update(void)
{
	// 射撃はあくまでもボス依存なので継承元のCEnemyのアップデートは呼び出さない
	IGameObject::Update();

	if (m_Player->GetTimeStop())
		return;

	if (!m_MoveFlag)
		return;
	
	Move();

	m_Cube.m_HRotate = m_Rotate;
	m_Model.position = m_Position;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CBossCannon::Draw(void)
{
	m_Model.Draw();
	CEnemy::Draw();
}

void CBossCannon::Finalize(void)
{
	CEnemy::Finalize();
	m_Model.Unload();
}

void CBossCannon::SetPosition(aqua::CVector3 pos)
{
	// 戻る最中ではない
	if (!m_ReturnFlag)
	{
		m_Position = pos;
		return;
	}
	else if (m_ReturnFlag&&m_EndPos != pos)	// 戻る最中かつ終了地点とposが一致しない(戻ろうとしてから呼び出されていない)
	{
		m_EndPos = pos;
		m_StartPos = m_Position;
	}
}

void CBossCannon::SetAllRange(void)
{
	m_AllRangeAttacking = true;
	m_MoveTimer.Setup(m_move_time);

	// 移動の始点に現在座標を代入
	m_StartPos = m_Position;

	// 乱数で角度を取る
	m_ShotAngle = (float)aqua::Rand(360.0f / (float)m_position_pattern);

}

void CBossCannon::Shot(void)
{
	CEnemy::Shot();
}

void CBossCannon::Move(void)
{
	if (!m_AllRangeAttacking||!m_ReturnFlag)
	{
		// プレイヤーと自身の距離
		aqua::CVector3 v = m_Player->GetPosition() - m_Position;

		// ベクトルのノーマライズ
		v.Normalize();

		// 2点から回転角度を求める
		m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));
	}

	if (m_AllRangeAttacking)// オールレンジ攻撃を行う
		AllRangeAttack();
	else if (m_ReturnFlag && m_EndPos != m_Position)// 終了したら元居た場所へ戻る
		ReturnPosition();

	m_Cube.position = m_Position;
}

void CBossCannon::EasingMove(void)
{
	m_MoveTimer.Update();

	aqua::CVector3 easing_pos = aqua::CVector3::ZERO;
	aqua::CVector3 dir = aqua::CVector3::ZERO;

	// イージングで移動させる
	easing_pos.x = aqua::easing::OutCubic(m_MoveTimer.GetTime(), m_MoveTimer.GetLimit(), m_StartPos.x, m_EndPos.x);
	easing_pos.z = aqua::easing::OutCubic(m_MoveTimer.GetTime(), m_MoveTimer.GetLimit(), m_StartPos.z, m_EndPos.z);

	// 移動の向きを差分で取る
	dir = easing_pos - m_Position;

	// 座標を合わせる
	m_Position = easing_pos;

	// 移動速度に合わせて回転角度を算出
	m_Rotate = aqua::RadToDeg(atan2(dir.x, dir.z));
	m_Cube.m_HRotate = m_Rotate;

	// タイマー終了
	if (m_MoveTimer.Finished())
	{
		m_MoveTimer.Reset();
		// 座標を終点に合わせる
		m_Position = m_EndPos;
	}
}

void CBossCannon::AllRangeAttack(void)
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
	if (m_EndPos == m_Position && !m_ReturnFlag)
	{
		// プレイヤーと自身の距離
		aqua::CVector3 v = m_Player->GetPosition() - m_Position;

		// ベクトルのノーマライズ
		v.Normalize();

		// 2点から回転角度を求める
		m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));
		Shot();
		m_ReturnFlag = true;
		m_AllRangeAttacking = false;
	}
}

void CBossCannon::ReturnPosition(void)
{
	// イージングで移動させる
	EasingMove();
	if (m_Position == m_EndPos)
	{
		// オールレンジ攻撃が完全に終了
		m_AllRangeFinish = true;
		m_AllRangeAttacking = false;
		m_ReturnFlag = false;

		m_StartPos = aqua::CVector3::ZERO;
		m_EndPos = m_StartPos;


		m_MoveTimer.Reset();
	}
}

