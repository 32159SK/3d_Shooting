
#include "../../../game_object.h"
#include "brittle_block.h"



CBrittleBlock::CBrittleBlock(aqua::IGameObject* parent)
	:IStageObject(parent, "BrittleBlock")
	, m_Endurance(5)
{
}

void CBrittleBlock::Initialize(const STAGE_OBJECT_ID& id, int x, int z)
{
	IStageObject::Initialize(id, x, z);

	// 
	m_EfectManager = (CEffectManager*)aqua::FindGameObject("EffectManager");
	m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");
	m_Cube.Setup(m_Position, m_default_size, m_default_size, m_default_size, aqua::CColor::WHITE);
	m_Model.Load("data\\model\\brittle_block.mv1");
	m_Model.position = m_Cube.position;

	if (!m_StageEdge)
		m_Model.position.y = -m_Cube.height;
}

bool CBrittleBlock::CollisionCheck(aqua::CVector3 position, aqua::CVector3 destination, bool this_bullet)
{
	// �L���[�u�̔�����ɍs���U�Ȃ炻�̂܂�false��Ԃ��Đ���������Ȃ�
	if (!m_Cube.CheckCollision(position, destination))
		return false;
	// �ڐG�����̂��e�������ꍇ
	if (this_bullet)
	{
		// �ϋv�l�����0�ɂȂ�����j��
		m_Endurance--;
		if (m_Endurance == 0)
			Broken();
	}
	// �����܂ŏ����������_�Ő^�Ȃ̂�true��Ԃ�
	return true;
}

void CBrittleBlock::Broken(void)
{
	// �A�N�e�B�u��ԂłȂ���
	m_ActiveFlag = false;
	// �G�t�F�N�g�ƃT�E���h���Đ����Ď��g���폜
	m_EfectManager->Create(EFFECT_ID::BROKEN, m_Position);
	m_SoundManager->Play(SOUND_ID::s_BROKEN);
	DeleteObject();
}
