#include "penetrate_bullet.h"

CPenetrateBullet::CPenetrateBullet(aqua::IGameObject* parent)
	: IBullet(parent, "PenetrateBullet")
{
}

void CPenetrateBullet::Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user, CEffectManager* em)
{
	m_Model.Load("data\\model\\bullet.mv1");
	IBullet::Initialize(bullet_info, attri, pop_pos, front, user, em);
}

