#include "../game_object.h"
#include "unit.h"

const float IUnit::m_beam_damage_interval =0.5f;

IUnit::
IUnit(aqua::IGameObject* parent, const std::string& object_name)
	: aqua::IGameObject(parent,object_name)
	, m_Height(0.0f)
	, m_Width(0.0f)
	, m_Depth(0.0f)
	, m_Speed(0.0f)
	, m_MaxLife(0)
	, m_Life(0)
	, m_DeadFlag(true)
	, m_MoveFlag(true)
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
	m_DeadFlag = false;
	m_Cube.Setup(m_Position, m_Width, m_Height, m_Depth, m_Color);
	aqua::CreateGameObject<CLifeBar>(this);
	// エフェクト管理クラスを探査してポインタを受け取る
	m_EffectManager = (CEffectManager*)aqua::FindGameObject("EffectManager");

	m_BeamInterval.Setup(m_beam_damage_interval);

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

bool IUnit::CheckHitBeam(UNIT_TYPE type, aqua::CCapsulePrimitive capsule, int damage)
{
	m_BeamInterval.Update();
	if (!m_BeamInterval.Finished())
		return false;

	m_BeamInterval.Reset();

	if (m_UnitType == type)
		return false;
	if (m_Cube.CheckCollision(capsule.Apos,capsule.Bpos,capsule.radius))
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
	m_EffectManager->Create(EFFECT_ID::DEAD, m_Position);
	DeleteObject();
}
