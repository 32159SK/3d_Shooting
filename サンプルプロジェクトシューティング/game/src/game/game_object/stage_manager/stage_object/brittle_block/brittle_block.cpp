
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

	m_EfectManager = (CEffectManager*)aqua::FindGameObject("EffectManager");
	m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");
	m_Cube.Setup(m_Position, m_default_size, m_default_size, m_default_size, aqua::CColor::WHITE);
	m_Model.Load("data\\model\\brittle_block.mv1");
	m_Model.position = m_Cube.position;

	if (!m_StageEdge)
		m_Model.position.y = -m_Cube.height;
}

void CBrittleBlock::Update(void)
{
	IStageObject::Update();
}

void CBrittleBlock::Draw(void)
{
	IStageObject::Draw();
}

void CBrittleBlock::Finalize(void)
{
	IStageObject::Finalize();
}

bool CBrittleBlock::CollisionCheck(aqua::CVector3 position, aqua::CVector3 destination, bool this_bullet)
{
	if (!m_Cube.CheckCollision(position, destination))
		return false;
	if (this_bullet)
	{
		m_Endurance--;
		if (m_Endurance == 0)
			Broken();
	}
	return true;
}

void CBrittleBlock::Broken(void)
{
	m_ActiveFlag = false;
	m_EfectManager->Create(EFFECT_ID::BROKEN, m_Position);
	m_SoundManager->Play(SOUND_ID::s_BROKEN);
	DeleteObject();
}
