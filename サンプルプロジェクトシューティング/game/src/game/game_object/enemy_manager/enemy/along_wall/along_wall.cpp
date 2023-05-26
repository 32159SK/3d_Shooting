#include "../../../game_object.h"
#include "along_wall.h"

const aqua::CVector3 CAlongWallEnemy::m_surroundings[] =
{
	aqua::CVector3(1.0f,0.0f,0.0f),
	aqua::CVector3(0.0f,0.0f,-1.0f),
	aqua::CVector3(-1.0f,0.0f,0.0f),
	aqua::CVector3(0.0f,0.0f,1.0f),
};

CAlongWallEnemy::CAlongWallEnemy(aqua::IGameObject* parent)
	: CEnemy(parent)
	, m_AlongWall(false)
	,m_WallDire(WALL_DIRE::UP)
{
}

void CAlongWallEnemy::Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m, CBulletManager* bm)
{
	CEnemy::Initialize(pop_pos, wid, hei, dep, color, st_m, bm);
}

void CAlongWallEnemy::Update(void)
{
	CEnemy::Update();
}

void CAlongWallEnemy::Shot(void)
{
	aqua::CVector3 bull_dir;

	for (int i = 0; i < 12; i++)
	{
		bull_dir.x = sin(aqua::DegToRad(m_Rotate + 30.0f * i));
		bull_dir.z = cos(aqua::DegToRad(m_Rotate + 30.0f * i));
		m_BulletManager->Create(m_Position, bull_dir, m_UnitType, BULLET_TYPE::NOMAL, this);
	}

}

void CAlongWallEnemy::Move(void)
{
	const float to_delta = 60.0f * aqua::GetDeltaTime();

	if (m_StageManager->StageObjectCollision(m_Position, m_Position + m_surroundings[(int)m_WallDire] * m_Width))
	{
		m_AlongWall = true;

		// 左にあれば上に向かう、そうでなければ時計回りに
		if (m_WallDire == WALL_DIRE::LEFT)
			m_WallDire = WALL_DIRE::UP;
		else
			m_WallDire = (WALL_DIRE)((int)m_WallDire + 1);
	}


	m_Velocity.x = (m_Speed * to_delta) * m_surroundings[(int)m_WallDire].x;
	m_Velocity.z = (m_Speed * to_delta) * m_surroundings[(int)m_WallDire].z;

	// 移動速度に合わせて回転角度を算出
	m_Rotate = aqua::RadToDeg(atan2(m_Velocity.x, m_Velocity.z));

	m_Cube.m_HRotate = m_Rotate;

	m_Position += m_Velocity;

	m_Cube.position = m_Position;
}
