
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
	// キューブの判定を先に行い偽ならそのままfalseを返して先を処理しない
	if (!m_Cube.CheckCollision(position, destination))
		return false;
	// 接触したのが弾だった場合
	if (this_bullet)
	{
		// 耐久値を削り0になったら破損
		m_Endurance--;
		if (m_Endurance == 0)
			Broken();
	}
	// ここまで処理した時点で真なのでtrueを返す
	return true;
}

void CBrittleBlock::Broken(void)
{
	// アクティブ状態でなくす
	m_ActiveFlag = false;
	// エフェクトとサウンドを再生して自身を削除
	m_EfectManager->Create(EFFECT_ID::BROKEN, m_Position);
	m_SoundManager->Play(SOUND_ID::s_BROKEN);
	DeleteObject();
}
