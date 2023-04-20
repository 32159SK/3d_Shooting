#include "player.h"

CPlayer::CPlayer(aqua::IGameObject* parent)
	: IUnit(parent,"Player")
{
}

void CPlayer::Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color)
{
}

void CPlayer::Update(void)
{
}

bool CPlayer::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive shot)
{
	return false;
}

void CPlayer::Shot(void)
{
}

void CPlayer::Move(void)
{
}

void CPlayer::Dead(void)
{
}
