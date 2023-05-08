#include "../../game_object.h"
#include "enemy.h"

CEnemy::CEnemy(aqua::IGameObject* parent)
	: IUnit(parent,"Enemy")
	, m_Angle(0.0f)
{
}

void 
CEnemy::
Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color,CBulletManager* bm)
{
	IUnit::Initialize(pop_pos, wid, hei, dep, color, bm);
	m_UnitType = UNIT_TYPE::ENEMY;
	m_ShotCT.Setup(10.0f);
	m_Speed = 0.5f;
}

void CEnemy::Update(void)
{
	m_ShotCT.Update();
	if(m_ShotCT.Finished())
	{
		Shot();
		m_ShotCT.Reset();
	}
	Move();
	IGameObject::Update();
}


void CEnemy::Shot(void)
{
	aqua::CVector3 front;

	front.x = sin(aqua::DegToRad(m_Rotate));
	front.z = cos(aqua::DegToRad(m_Rotate));

	m_BulletManager->Create(m_Position,front, m_UnitType, BULLET_TYPE::NOMAL,this);
}

void CEnemy::Move(void)
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

	m_Velocity.x = (m_Speed * to_delta)*cos(m_Angle);
	m_Velocity.z = (m_Speed * to_delta)*sin(m_Angle);

	m_Position += m_Velocity;

	// 移動速度に合わせて回転角度を算出
	m_Rotate = aqua::RadToDeg(atan2(m_Velocity.x, m_Velocity.z));

	m_Cube.m_HRotate = m_Rotate;
	m_Cube.position = m_Position;
}

void CEnemy::Dead(void)
{
	IUnit::Dead();
}
