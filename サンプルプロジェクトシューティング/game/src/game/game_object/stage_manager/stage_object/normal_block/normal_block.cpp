#include "normal_block.h"


CNormalBlock::CNormalBlock(aqua::IGameObject* parent)
	:IStageObject(parent, "NormalBlock")
{
}

void CNormalBlock::Initialize(const STAGE_OBJECT_ID& id, int x, int z)
{
	// ���N���X�̏�����
	IStageObject::Initialize(id, x, z);

	// ����p�L���[�u���Ăяo��
	m_Cube.Setup(m_Position, m_default_size, m_default_size, m_default_size, aqua::CColor::WHITE);
	// ���f����ǂݍ���ō��W���L���[�u�ɍ��킹��
	m_Model.Load("data\\model\\nomal_block.mv1");
	m_Model.position = m_Cube.position;

	// �[�łȂ��Ȃ璾��ǂ��Ă��炤
	if (!m_StageEdge)
		m_Model.position.y = -m_Cube.height;
}

