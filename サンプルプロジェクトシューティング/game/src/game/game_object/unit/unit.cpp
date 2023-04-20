#include "unit.h"


const int IUnit::m_max_life = 5;

IUnit::
IUnit(aqua::IGameObject* parent, const std::string& object_name)
	: aqua::IGameObject(parent,object_name)
	, m_Height(0.0f)
	, m_Width(0.0f)
	, m_Depth(0.0f)
	, m_Life(0)
	, m_DeadFlag(false)
{
}

void IUnit::Initialize(void)
{
	m_Life = m_max_life;
	m_Cube.Setup(m_Position, m_Width, m_Height, m_Depth, m_Color);
}

void IUnit::Draw(void)
{
	m_Cube.Draw();
}

void IUnit::Update(void)
{
}

bool IUnit::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive shot)
{
	return false;
}

void IUnit::Shot(void)
{
}

void IUnit::Move(void)
{
}

void IUnit::Damage(void)
{

}

void IUnit::Dead(void)
{
}
