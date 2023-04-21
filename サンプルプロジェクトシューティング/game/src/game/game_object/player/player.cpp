#include "../game_object.h"
#include "player.h"

CPlayer::CPlayer(aqua::IGameObject* parent)
	: IUnit(parent,"Player")
{
}

void CPlayer::Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CBulletManager* bm)
{
	IUnit::Initialize(pop_pos, wid, hei, dep, color, bm);
	m_UnitType = UNIT_TYPE::PLAYER;
	m_BulletManager->SetPlayer(this);
	m_ShotCT.Setup(0.5f);
}

void CPlayer::Update(void)
{
	Shot();
	IGameObject::Update();
}

bool CPlayer::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)
{
	return IUnit::CheckHitBullet(type,sphere,damage);
}


void CPlayer::Shot(void)
{
	m_ShotCT.Update();
	if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::Z) && m_ShotCT.Finished())
	{
		m_BulletManager->Create(m_Position, m_UnitType, BULLET_TYPE::NOMAL,this);
		m_ShotCT.Reset();
	}
}

void CPlayer::Move(void)
{
}

void CPlayer::Dead(void)
{
}
