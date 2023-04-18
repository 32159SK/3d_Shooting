#include "enemy.h"

CEnemy::CEnemy(aqua::IGameObject* parent)
	: IUnit(parent,"Enemy")
{
}

void 
CEnemy::
Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color)
{
	m_Position = pop_pos;
	m_Width = wid;
	m_Height = hei;
	m_Depth = dep;
	m_Color = color;
	IUnit::Initialize();
}

void CEnemy::Update(void)
{
}

bool CEnemy::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive shot)
{
	//if()

	return ;
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
