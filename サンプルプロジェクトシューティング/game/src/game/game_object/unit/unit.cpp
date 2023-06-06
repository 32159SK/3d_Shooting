#include "../game_object.h"
#include "unit.h"

IUnit::
IUnit(aqua::IGameObject* parent, const std::string& object_name)
	: aqua::IGameObject(parent,object_name)
	, m_Height(0.0f)
	, m_Width(0.0f)
	, m_Depth(0.0f)
	, m_Speed(0.0f)
	, m_MaxLife(5)
	, m_Life(0)
	, m_DeadFlag(false)
	, m_Rotate(0.0f)
	, m_Position(aqua::CVector3::ZERO)
	, m_Velocity(aqua::CVector3::ZERO)
{
}

void IUnit::Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m , CBulletManager* bm)
{
	m_Position = pop_pos;
	m_Width = wid;
	m_Height = hei;
	m_Depth = dep;
	m_Color = color;
	m_BulletManager = bm;
	m_StageManager = st_m;
	m_Life = m_MaxLife;
	m_Cube.Setup(m_Position, m_Width, m_Height, m_Depth, m_Color);
	aqua::CreateGameObject<CLifeBar>(this);

	IGameObject::Initialize();
}

void IUnit::Draw(void)
{
	m_Cube.Draw();
	IGameObject::Draw();
}

void IUnit::Update(void)
{
	Move();
	m_Cube.position = m_Position;

	IGameObject::Update();
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
	DeleteObject();
}
