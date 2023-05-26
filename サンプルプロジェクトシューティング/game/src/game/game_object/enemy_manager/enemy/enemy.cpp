#include "../../game_object.h"
#include "enemy.h"

CEnemy::CEnemy(aqua::IGameObject* parent)
	: IUnit(parent,"Enemy")
	, m_Angle(180.0f)
{
}

void 
CEnemy::
Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m,CBulletManager* bm)
{
	IUnit::Initialize(pop_pos, wid, hei, dep, color,st_m, bm);
	m_UnitType = UNIT_TYPE::ENEMY;
	m_ShotCT.Setup(5.0f);
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

	// ƒvƒŒƒCƒ„[‚ÆŽ©g‚Ì‹——£
	aqua::CVector3 v = player_pos - m_Position;

	float dir = aqua::CVector2::Cross(aqua::CVector2(v.x, v.z), aqua::CVector2(m_Velocity.x, m_Velocity.z));

	if (dir > 0.001f)
		m_Angle -= aqua::DegToRad(1.0f);
	else if (dir < 0.001f)
		m_Angle += aqua::DegToRad(1.0f);

	m_Velocity.x = (m_Speed * to_delta)*cos(m_Angle);
	m_Velocity.z = (m_Speed * to_delta)*sin(m_Angle);

	// ˆÚ“®‘¬“x‚É‡‚í‚¹‚Ä‰ñ“]Šp“x‚ðŽZo
	m_Rotate = aqua::RadToDeg(atan2(m_Velocity.x, m_Velocity.z));

	m_Cube.m_HRotate = m_Rotate;

	// •Ç‚Æ“–‚½‚Á‚Ä‚½‚ç‚»‚±‚ÅŽ~‚Ü‚é
	if (m_StageManager->StageObjectCollision(m_Position, m_Position + m_Velocity * m_Width*1.5f))
		return;

	m_Position += m_Velocity;
	
	m_Cube.position = m_Position;
}

void CEnemy::Dead(void)
{
	IUnit::Dead();
}
