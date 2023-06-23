#include "penetrate_bullet.h"

CPenetrateBullet::CPenetrateBullet(aqua::IGameObject* parent)
	: IBullet(parent, "PenetrateBullet")
{
}

void CPenetrateBullet::Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user, CEffectManager* em)
{
	IBullet::Initialize(bullet_info, attri, pop_pos, front, user, em);
	m_Sphere.visible = false;
	m_Model.Load("data\\model\\bullet.mv1");
	m_Model.position = m_Position;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}