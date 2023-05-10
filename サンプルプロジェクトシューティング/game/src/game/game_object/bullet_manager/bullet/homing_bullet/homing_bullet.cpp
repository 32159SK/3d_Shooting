#include "homing_bullet.h"

CHomingBullet::CHomingBullet(aqua::IGameObject* parent)
	: IBullet(parent,"HomingBullet")
{
}

void CHomingBullet::Update(void)
{
	IBullet::Update();
}
