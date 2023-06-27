#include "../../game_object.h"
#include "enemy.h"

const aqua::CVector3 CEnemy::m_surroundings[] =
{
	aqua::CVector3(1.0f,0.0f,0.0f),
	aqua::CVector3(0.0f,0.0f,-1.0f),
	aqua::CVector3(-1.0f,0.0f,0.0f),
	aqua::CVector3(0.0f,0.0f,1.0f),
};

CEnemy::CEnemy(aqua::IGameObject* parent)
	: IUnit(parent,"Enemy")
	, m_Angle(180.0f)
{
}

void 
CEnemy::
Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m,CBulletManager* bm)
{
	IUnit::Initialize(pop_pos, enemy_info.width, enemy_info.height, enemy_info.depth, enemy_info.color,st_m, bm);
	m_MaxLife = enemy_info.life;
	m_Life = m_MaxLife;
	m_UnitType = UNIT_TYPE::ENEMY;
	m_ShotCT.Setup(10);
	m_Speed = enemy_info.speed;
}

void CEnemy::Update(void)
{
	IGameObject::Update();
	// Œ±‰^—p
	if (!m_MoveFlag)
		return;

	if (m_Player->GetTimeStop())
		return;

	m_ShotCT.Update();
	if(m_ShotCT.Finished())
	{
		Shot();
		m_ShotCT.Reset();
	}
	Move();
}

void CEnemy::Draw(void)
{
	IGameObject::Draw();
	m_Cube.Draw();
}

void CEnemy::Finalize(void)
{
	IGameObject::Finalize();
}


void CEnemy::Shot(void)
{

	aqua::CVector3 front;

	front.x = sin(aqua::DegToRad(m_Rotate));
	front.z = cos(aqua::DegToRad(m_Rotate));

	m_BulletManager->Create(m_Position, front, m_UnitType, m_ShotBullet, this);
}

void CEnemy::Move(void)
{
	// ˆÚ“®‘¬“x‚É‡‚í‚¹‚Ä‰ñ“]Šp“x‚ğZo
	m_Rotate = aqua::RadToDeg(atan2(m_Velocity.x, m_Velocity.z));
	m_Cube.m_HRotate = m_Rotate;

	m_Position += m_Velocity;

	m_Cube.position = m_Position;
}

void CEnemy::Dead(void)
{
	IUnit::Dead();
}
