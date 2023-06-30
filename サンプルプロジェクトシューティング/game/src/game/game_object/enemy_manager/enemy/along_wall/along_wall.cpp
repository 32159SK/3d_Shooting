#include "../../../game_object.h"
#include "along_wall.h"


CAlongWallEnemy::CAlongWallEnemy(aqua::IGameObject* parent)
	: CEnemy(parent,"AlongWallEnemy")
	, m_AlongWall(false)
	,m_WallDire(WALL_DIRE::UP)
{
}

void CAlongWallEnemy::
Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)
{
	CEnemy::Initialize(pop_pos, enemy_info, st_m, bm);
	m_ShotBullet = BULLET_TYPE::REFLECT;
}

void CAlongWallEnemy::Update(void)
{
	CEnemy::Update();
}

void CAlongWallEnemy::Shot(void)
{
	aqua::CVector3 bull_dir;

	for (int i = 0; i < 4; i++)
	{
		bull_dir.x = sin(aqua::DegToRad(m_Rotate + 45.0f + 90.0f * i));
		bull_dir.z = cos(aqua::DegToRad(m_Rotate + 45.0f + 90.0f * i));
		m_BulletManager->Create(m_Position, bull_dir, m_UnitType, m_ShotBullet, this);
	}
}

void CAlongWallEnemy::Move(void)
{
	const float to_delta = 60.0f * aqua::GetDeltaTime();

	if (m_StageManager->StageObjectCollision(m_Position, m_Position + m_surroundings[(int)m_WallDire] * m_Width,false))
	{
		m_AlongWall = true;

		// ç∂Ç…Ç†ÇÍÇŒè„Ç…å¸Ç©Ç§ÅAÇªÇ§Ç≈Ç»ÇØÇÍÇŒéûåvâÒÇËÇ…
		if (m_WallDire == WALL_DIRE::LEFT)
			m_WallDire = WALL_DIRE::UP;
		else
			m_WallDire = (WALL_DIRE)(m_WallDire + 1);
	}


	m_Velocity.x = (m_Speed * to_delta) * m_surroundings[m_WallDire].x;
	m_Velocity.z = (m_Speed * to_delta) * m_surroundings[m_WallDire].z;

	CEnemy::Move();
}
