#include "bullet.h"

IBullet::IBullet(aqua::IGameObject* parent, const std::string& object_name)
	: IGameObject(parent, object_name, "Bullet")
{
}


void IBullet::Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user,CEffectManager* em)
{
	m_Attri = attri;
	m_Position = pop_pos;
	m_Dir = front;
	m_Damage = bullet_info.damage;
	m_Speed = bullet_info.speed;
	m_Radius = bullet_info.radius;
	m_Unit = user;
	m_EffectManager = em;

	m_StartPos = m_Position;
	m_Sphere.Setup(m_Position, m_Radius);
	Update();
}

void IBullet::Draw(void)
{
	m_Sphere.Draw();
	m_Model.Draw();
}

void IBullet::Update(void)
{
	const float to_delta = 60.0f * aqua::GetDeltaTime();

	m_Velocity = aqua::CVector3::ZERO;
	m_Velocity += m_Dir;
	m_Velocity = m_Velocity.Normalize();

	m_Velocity *= (m_Speed * to_delta);

	m_Position += m_Velocity;


	// 移動速度に合わせて回転角度を算出
	m_Rotate = aqua::RadToDeg(atan2(m_Velocity.x, m_Velocity.z));

	m_Sphere.position = m_Position;

	m_Model.position = m_Position;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void IBullet::Finalize(void)
{
	m_Model.Unload();
}

void IBullet::Hit(void)
{
	m_EffectManager->Create(EFFECT_ID::HIT, m_Position);
	DeleteObject();
}

void IBullet::StageObjectHit(aqua::CCubePrimitive::COLL_DIRE c_dire)
{
	Hit();
}

