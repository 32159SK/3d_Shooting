#include "normal_bullet.h"

CNormalBullet::CNormalBullet(aqua::IGameObject* parent)
	: IBullet(parent,"NomalBullet")
{
}

void CNormalBullet::Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user, CEffectManager* em)
{
	// ÉÇÉfÉãÇÃÉçÅ[Éh
	m_Model.Load("data\\model\\bullet.mv1");
	IBullet::Initialize(bullet_info, attri, pop_pos, front, user, em);
}