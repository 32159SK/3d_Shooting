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
	m_ShotCT.Setup(10.0f);
}

void CEnemy::Update(void)
{
	m_ShotCT.Update();
	if(m_ShotCT.Finished())
	{
		Shot();
		m_ShotCT.Reset();
	}
	IGameObject::Update();
}


void CEnemy::Shot(void)
{
	m_BulletManager->Create(m_Position, m_UnitType, BULLET_TYPE::NOMAL,this);
}

void CEnemy::Move(void)
{
}

void CEnemy::Dead(void)
{
	IUnit::Dead();
}
