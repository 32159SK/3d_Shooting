#include "../game_object.h"
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
	, m_Rotate(0.0f)
{
}

void IUnit::Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CBulletManager* bm)
{
	m_Position = pop_pos;
	m_Width = wid;
	m_Height = hei;
	m_Depth = dep;
	m_Color = color;
	m_BulletManager = bm;
	m_Life = m_max_life;
	m_Cube.Setup(m_Position, m_Width, m_Height, m_Depth, m_Color);
}

void IUnit::Draw(void)
{
	m_Cube.Draw();
	IGameObject::Draw();
}

void IUnit::Update(void)
{
}

bool IUnit::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere,int damage)
{
	if (m_UnitType == type)
		return false;
	if (m_Cube.CheckCollision(sphere.position, sphere.radius))
	{
		Damage(damage);
		return true;
	}
	return false;
}

void IUnit::Shot(void)
{
}

void IUnit::Move(void)
{
}

void IUnit::Damage(int damage)
{
	m_Life -= damage;
	if (m_Life <= 0)
		Dead();
}
void IUnit::Dead(void)
{
	m_DeadFlag = true;
	m_Cube.visible = false;
	//DeleteObject();
}
