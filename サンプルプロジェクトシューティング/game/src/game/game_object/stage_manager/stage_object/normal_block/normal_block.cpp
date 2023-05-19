#include "normal_block.h"


CNormalBlock::CNormalBlock(aqua::IGameObject* parent)
	:IStageObject(parent, "")
	, m_StageEdge(false)
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
	m_Model.Draw();
}

void CNormalBlock::Finalize(void)
{
	m_Model.Unload();
}

bool CNormalBlock::CollisionCheck(aqua::CVector3 position, aqua::CVector3 destination)
{
	return m_Cube.CheckCollision(position, destination);
}

void CNormalBlock::GoIn(void)
{
	if (m_StageEdge)
	{
		m_ObjectState = PLAY;
		return;
	}
	// position‚Ì‰¼•Ï”
	m_Model.position.y += 0.5f;

	if (m_Model.position.y > m_Position.y)
		m_ObjectState = PLAY;
}

void CNormalBlock::GoOut(void)
{
	// position‚Ì‰¼•Ï”
	m_Model.position.y -=0.5f;

	if (m_Model.position.y<m_Cube.height)
		m_ObjectState = FINISH;
}
