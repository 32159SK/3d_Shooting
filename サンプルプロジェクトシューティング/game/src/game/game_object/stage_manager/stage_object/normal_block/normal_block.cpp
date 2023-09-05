#include "normal_block.h"


CNormalBlock::CNormalBlock(aqua::IGameObject* parent)
	:IStageObject(parent, "NormalBlock")
{
}

void CNormalBlock::Initialize(const STAGE_OBJECT_ID& id, int x, int z)
{
	// 基底クラスの初期化
	IStageObject::Initialize(id, x, z);

	// 判定用キューブを呼び出す
	m_Cube.Setup(m_Position, m_default_size, m_default_size, m_default_size, aqua::CColor::WHITE);
	// モデルを読み込んで座標をキューブに合わせる
	m_Model.Load("data\\model\\nomal_block.mv1");
	m_Model.position = m_Cube.position;

	// 端でないなら沈んどいてもらう
	if (!m_StageEdge)
		m_Model.position.y = -m_Cube.height;
}

