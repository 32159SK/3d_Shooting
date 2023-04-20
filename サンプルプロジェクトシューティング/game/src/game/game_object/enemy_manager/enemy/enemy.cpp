#include "../../game_object.h"
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
	m_ShotTimer.Setup(10.0f);
}

void CEnemy::Update(void)
{
	m_ShotTimer.Update();
	if(m_ShotTimer.Finished())
	{
		Shot();
		m_ShotTimer.Reset();
	}
}


void CEnemy::Shot(void)
{
	m_BulletManager->Create(m_Position, m_UnitType, BULLET_TYPE::NOMAL);
}

void CEnemy::Move(void)
{
}

void CEnemy::Dead(void)
{
}
