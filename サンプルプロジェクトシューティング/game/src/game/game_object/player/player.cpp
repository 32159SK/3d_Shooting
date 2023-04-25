#include "../game_object.h"
#include "player.h"

CPlayer::CPlayer(aqua::IGameObject* parent)
	: IUnit(parent,"Player")
{
}

void CPlayer::Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CBulletManager* bm)
{
	IUnit::Initialize(pop_pos, wid, hei, dep, color, bm);
	m_UnitType = UNIT_TYPE::PLAYER;
	m_BulletManager->SetPlayer(this);
	m_Speed = 1.0f;
	m_ShotCT.Setup(0.5f);
}

void CPlayer::Update(void)
{


	m_Cube.m_HRotate = m_Rotate;
	Shot();
	IUnit::Update();
	IGameObject::Update();
}

void CPlayer::Draw(void)
{
	aqua::CVector3 front;
	
	front.x = sin(aqua::DegToRad(m_Rotate));
	front.z = cos(aqua::DegToRad(m_Rotate));

	m_Line.pointA = m_Position;
	m_Line.pointB = m_Position + (front * 20.0f);
	m_Line.Draw();

	IUnit::Draw();
}

bool CPlayer::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)
{
	return IUnit::CheckHitBullet(type,sphere,damage);
}


void CPlayer::Shot(void)
{
	m_ShotCT.Update();

	aqua::CVector3 front;

	front.x = sin(aqua::DegToRad(m_Rotate));
	front.z = cos(aqua::DegToRad(m_Rotate));


	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::SPACE) && m_ShotCT.Finished())
	{
		m_BulletManager->Create(m_Position,front, m_UnitType, BULLET_TYPE::NOMAL,this);
		m_ShotCT.Reset();
	}
}

void CPlayer::Move(void)
{
	using namespace aqua::keyboard;
	const float to_delta = 60.0f * aqua::GetDeltaTime();

	m_Velocity = aqua::CVector3::ZERO;


	if (Button(KEY_ID::W)) m_Velocity += aqua::CVector3(0.0f, 0.0f, 1.0f);
	if (Button(KEY_ID::S)) m_Velocity -= aqua::CVector3(0.0f, 0.0f, 1.0f);
	if (Button(KEY_ID::A)) m_Velocity -= aqua::CVector3(1.0f, 0.0f, 0.0f);
	if (Button(KEY_ID::D)) m_Velocity += aqua::CVector3(1.0f, 0.0f, 0.0f);

	if (Button(KEY_ID::RIGHT)) m_Rotate += 1.0f;
	if (Button(KEY_ID::LEFT)) m_Rotate -= 1.0f;

	m_Velocity = m_Velocity.Normalize();
	m_Velocity *= (m_Speed * to_delta);
	m_Position += m_Velocity;

}

void CPlayer::Dead(void)
{
}
