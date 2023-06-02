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
}

void CEnemy::Move(void)
{
}

void CEnemy::Dead(void)
{
	IUnit::Dead();
}
