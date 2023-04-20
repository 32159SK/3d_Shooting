#include "bullet.h"

IBullet::IBullet(aqua::IGameObject* parent, const std::string& object_name)
{
}


void IBullet::Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos)
{
	m_Attri = attri;
	m_Position = pop_pos;
	m_Damage = bullet_info.damage;
	m_Radius = bullet_info.radius;
	m_Color = bullet_info.color;
	m_Sphere.Setup(m_Position, m_Radius, m_Color);
}

void IBullet::Draw(void)
{
	m_Sphere.Draw();
}

void IBullet::Update(void)
{
	m_Sphere.position.z -= 1.0f;
}

void IBullet::Hit(void)
{
	DeleteObject();
}

