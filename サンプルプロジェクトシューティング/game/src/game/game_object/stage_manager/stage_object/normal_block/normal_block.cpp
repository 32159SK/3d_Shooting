#include "normal_block.h"


CNormalBlock::CNormalBlock(aqua::IGameObject* parent)
	:IStageObject(parent,"")
{
}

void CNormalBlock::Initialize(const STAGE_OBJECT_ID& id, int x, int z)
{
	IStageObject::Initialize(id, x, z);

	m_Cube.Setup(m_Position, m_default_size, m_default_size, m_default_size, aqua::CColor::WHITE);
}

void CNormalBlock::Update(void)
{
}

void CNormalBlock::Draw(void)
{
	m_Cube.Draw();
}

void CNormalBlock::Finalize(void)
{
}

bool CNormalBlock::CollisionCheck(aqua::CVector3 position, aqua::CVector3 destination)
{
	return m_Cube.CheckCollision(position, destination);
}
