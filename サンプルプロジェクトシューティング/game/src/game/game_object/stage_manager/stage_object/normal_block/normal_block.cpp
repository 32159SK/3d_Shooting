#include "normal_block.h"


CNormalBlock::CNormalBlock(aqua::IGameObject* parent)
	:IStageObject(parent, "NormalBlock")
{
}

void CNormalBlock::Initialize(const STAGE_OBJECT_ID& id, int x, int z)
{
	IStageObject::Initialize(id, x, z);

	m_Cube.Setup(m_Position, m_default_size, m_default_size, m_default_size, aqua::CColor::WHITE);
	m_Model.Load("data\\model\\nomal_block.mv1");
	m_Model.position = m_Cube.position;

	if (!m_StageEdge)
		m_Model.position.y = -m_Cube.height;
}

void CNormalBlock::Update(void)
{
	IStageObject::Update();
}

void CNormalBlock::Draw(void)
{
	//m_Cube.Draw();
	IStageObject::Draw();
}

void CNormalBlock::Finalize(void)
{
	IStageObject::Finalize();
}

bool CNormalBlock::CollisionCheck(aqua::CVector3 position, aqua::CVector3 destination, bool this_bullet)
{
	return IStageObject::CollisionCheck(position, destination,this_bullet);
}

