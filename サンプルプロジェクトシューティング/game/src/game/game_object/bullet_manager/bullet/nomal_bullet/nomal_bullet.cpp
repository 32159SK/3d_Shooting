#include "nomal_bullet.h"

CNomalBullet::CNomalBullet(aqua::IGameObject* parent)
	: IBullet(parent,"NomalBullet")
{
}

void CNomalBullet::Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user)
{
	IBullet::Initialize(bullet_info, attri, pop_pos, front, user);
	m_Sphere.visible = false;
	m_Model.Load("data\\model\\bullet.mv1");
}

void CNomalBullet::Update(void)
{
	IBullet::Update();
	m_Model.position = m_Position;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CNomalBullet::Draw(void)
{
	m_Model.Draw();
}

void CNomalBullet::Finalize(void)
{
	m_Model.Unload();
}
