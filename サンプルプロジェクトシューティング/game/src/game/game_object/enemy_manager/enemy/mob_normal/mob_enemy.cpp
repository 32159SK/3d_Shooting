#include "../../../game_object.h"
#include "mob_enemy.h"

CMobEnemy::CMobEnemy(aqua::IGameObject* parent)
	: CEnemy(parent)
{
}

void
CMobEnemy::
Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m, CBulletManager* bm)
{
	CEnemy::Initialize(pop_pos, wid, hei, dep, color, st_m, bm);
}

void CMobEnemy::Update(void)
{
	CEnemy::Update();
}


void CMobEnemy::Shot(void)
{
	aqua::CVector3 front;

	front.x = sin(aqua::DegToRad(m_Rotate));
	front.z = cos(aqua::DegToRad(m_Rotate));

	m_BulletManager->Create(m_Position, front, m_UnitType, BULLET_TYPE::NOMAL, this);
}

void CMobEnemy::Move(void)
{
	const float to_delta = 60.0f * aqua::GetDeltaTime();
	aqua::CVector3 player_pos = m_Player->GetAgoPos();

	// プレイヤーと自身の距離
	aqua::CVector3 v = player_pos - m_Position;

	float dir = aqua::CVector2::Cross(aqua::CVector2(v.x, v.z), aqua::CVector2(m_Velocity.x, m_Velocity.z));

	if (dir > 0.001f)
		m_Angle -= aqua::DegToRad(1.0f);
	else if (dir < 0.001f)
		m_Angle += aqua::DegToRad(1.0f);

	m_Velocity.x = (m_Speed * to_delta) * cos(m_Angle);
	m_Velocity.z = (m_Speed * to_delta) * sin(m_Angle);

	// 移動速度に合わせて回転角度を算出
	m_Rotate = aqua::RadToDeg(atan2(m_Velocity.x, m_Velocity.z));

	m_Cube.m_HRotate = m_Rotate;

	// 壁と当たってたらそこで止まる
	if (m_StageManager->StageObjectCollision(m_Position, m_Position + m_Velocity * m_Width * 1.5f))
		return;

	m_Position += m_Velocity;

	m_Cube.position = m_Position;
}

void CMobEnemy::Dead(void)
{
	IUnit::Dead();
}

void CMobEnemy::Follow(void)
{
	// プレイヤーと自身の距離
	aqua::CVector3 v = m_Player->GetPosition() - m_Position;

	// 範囲内かつ、壁を隔てていないなら追跡開始
	if (m_follow_range > abs(aqua::CVector3::Length(v))&&m_StageManager->StageObjectCollision(m_Player->GetPosition(),m_Position))
		m_Follow = true;
}
