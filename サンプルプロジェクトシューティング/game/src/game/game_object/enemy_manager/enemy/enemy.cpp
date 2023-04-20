#include "enemy.h"

CEnemy::CEnemy(aqua::IGameObject* parent)
	: IUnit(parent,"Enemy")
{
}

void 
CEnemy::
Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color,CBulletManager* bm)
{
	IUnit::Initialize(pop_pos, wid, hei, dep, color, bm);
	m_UnitType = UNIT_TYPE::ENEMY;
}

void CEnemy::Update(void)
{
}


void CEnemy::Shot(void)
{
}

void CEnemy::Move(void)
{
}

void CEnemy::Dead(void)
{
}
