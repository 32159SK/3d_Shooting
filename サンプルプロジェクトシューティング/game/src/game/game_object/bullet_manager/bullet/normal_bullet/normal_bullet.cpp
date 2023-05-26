#include "normal_bullet.h"

CNormalBullet::CNormalBullet(aqua::IGameObject* parent)
	: IBullet(parent,"NomalBullet")
{
}

void CNormalBullet::Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user)
{
	IBullet::Initialize(bullet_info, attri, pop_pos, front, user);
	m_Sphere.visible = false;
	m_Model.Load("data\\model\\bullet.mv1");
	Update();
}

void CNormalBullet::Update(void)
{
	IBullet::Update();
	m_Model.position = m_Position;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CNormalBullet::Draw(void)
{
	IBullet::Draw();
	m_Model.Draw();
}

void CNormalBullet::Finalize(void)
{
	IBullet::Finalize();
	m_Model.Unload();
}
