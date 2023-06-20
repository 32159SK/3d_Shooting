#include "bullet.h"

const float IBullet::m_radius = 5.0f;


IBullet::IBullet(aqua::IGameObject* parent, const std::string& object_name)
	: IGameObject(parent, object_name, "Bullet")
{
}


void IBullet::Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user)
{
	m_Attri = attri;
	m_Position = pop_pos;
	m_Dir = front;
	m_Damage = bullet_info.damage;
	m_Speed = bullet_info.speed;
	m_Color = bullet_info.color;
	m_Unit = user;



	m_Range = 700.0f;

	m_StartPos = m_Position;
	m_Sphere.Setup(m_Position, m_radius, m_Color);
}

void IBullet::Draw(void)
{
	m_Sphere.Draw();
}

void IBullet::Update(void)
{
	const float to_delta = 60.0f * aqua::GetDeltaTime();

	m_Velocity = aqua::CVector3::ZERO;
	m_Velocity += m_Dir;
	m_Velocity = m_Velocity.Normalize();

	m_Velocity *= (m_Speed * to_delta);

	m_Position += m_Velocity;

	if (aqua::CVector3::Length(m_StartPos - m_Position) > abs(m_Range))
		Hit();

	// ˆÚ“®‘¬“x‚É‡‚í‚¹‚Ä‰ñ“]Šp“x‚ğZo
	m_Rotate = aqua::RadToDeg(atan2(m_Velocity.x, m_Velocity.z));

	m_Sphere.position = m_Position;
}

void IBullet::Hit(void)
{
	DeleteObject();
	m_Sphere.visible = false;
}

void IBullet::StageObjectHit(aqua::CCubePrimitive::COLL_DIRE c_dire)
{
	Hit();
}

