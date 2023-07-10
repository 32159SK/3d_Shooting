#include "../../stage_manager.h"
#include "move_block.h"


CMoveBlock::CMoveBlock(aqua::IGameObject* parent)
	:IStageObject(parent, "NormalBlock")
{
}

void CMoveBlock::Initialize(const STAGE_OBJECT_ID& id, int x, int z)
{
	IStageObject::Initialize(id, x, z);

	m_Cube.Setup(m_Position, m_default_size, m_default_size, m_default_size, aqua::CColor::WHITE);
	m_Model.Load("data\\model\\nomal_block.mv1");
	m_Model.position = m_Cube.position;

	// 親(ステージ管理)クラスを取得
	m_StageManager = (CStageManager*)IGameObject::GetParent();

	if (!m_StageEdge)
		m_Model.position.y = -m_Cube.height;
}

void CMoveBlock::Update(void)
{
	IStageObject::Update();
	Move();
}

void CMoveBlock::Draw(void)
{
	//m_Cube.Draw();
	IStageObject::Draw();
}

void CMoveBlock::Finalize(void)
{
	IStageObject::Finalize();
}

bool CMoveBlock::CollisionCheck(aqua::CVector3 position, aqua::CVector3 destination, bool this_bullet)
{
	return IStageObject::CollisionCheck(position, destination, this_bullet);
}

void CMoveBlock::Move(void)
{
	if (m_StageManager->StageObjectCollision(m_Position, m_Position, false))
		return;
}
