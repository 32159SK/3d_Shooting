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

	m_Rotate += 1.0f;

	m_Cube.m_HRotate = m_Rotate;
	Shot();
	IGameObject::Update();
}

void CPlayer::Draw(void)
{
	aqua::CVector3 front;
	
	front.x = sin(aqua::DegToRad(m_Rotate + 90));
	front.z = cos(aqua::DegToRad(m_Rotate + 90));

	m_Line.pointA = m_Position;
	m_Line.pointB = m_Position + (front * 20.0f);
	m_Line.Draw();

	IUnit::Draw();
}

bool CPlayer::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)
{
	return IUnit::CheckHitBullet(type,sphere,damage);
}


void CPlayer::Shot(void)
{
	m_ShotCT.Update();

	aqua::CVector3 front;

	front.x = sin(aqua::DegToRad(m_Rotate + 90));
	front.z = cos(aqua::DegToRad(m_Rotate + 90));

	if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::Z) && m_ShotCT.Finished())
	{
		m_BulletManager->Create(m_Position,front, m_UnitType, BULLET_TYPE::NOMAL,this);
		m_ShotCT.Reset();
	}
}

void CPlayer::Move(void)
{
}

void CPlayer::Dead(void)
{
}
