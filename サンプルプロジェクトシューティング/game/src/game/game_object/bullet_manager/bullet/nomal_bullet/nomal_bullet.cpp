#include "nomal_bullet.h"

CNomalBullet::CNomalBullet(aqua::IGameObject* parent)
	: IBullet(parent,"NomalBullet")
{
}

void CNomalBullet::Update(void)
{
	IBullet::Update();
}
