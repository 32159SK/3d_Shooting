#include "beam.h"

const float CBeam::m_max_range = 500.0f;

CBeam::CBeam(aqua::IGameObject* parent, const std::string& object_name)
	:IGameObject(parent, "Beam")
	, m_Damage(0.0f)
	, m_Rotate(0.0f)
	, m_Radius(0.0f)
	, m_StartPos(aqua::CVector3::ZERO)
	, m_EndPos(aqua::CVector3::ZERO)
	, m_Dir(aqua::CVector3::ZERO)
	, m_Attri(UNIT_TYPE::PLAYER)
	, m_EffectManager(nullptr)
	, m_Unit(nullptr)
{
}

void CBeam::Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 dir, IUnit* user, CEffectManager* em)
{
	m_StartPos = pop_pos;

	m_Radius = bullet_info.radius;

	m_Damage = bullet_info.damage;

	m_Attri = attri;
	m_Dir = dir;

	m_EffectManager = (CEffectManager*)aqua::FindGameObject("EffectManager");

	// 回転角度を算出
	m_Rotate = aqua::RadToDeg(atan2(m_Dir.x, m_Dir.z));

	// 終点座標の仮決め
	m_EndPos = m_StartPos;
	m_EndPos.z = m_StartPos.z + m_max_range;

	// 行列を使って始点を中心とした回転処理を行い、正確な終点座標を求める
	aqua::CMatrix mat;
	mat.RotationY(aqua::DegToRad(m_Rotate));
	mat.Translate(m_StartPos);
	m_EndPos *= mat;

	// 終点座標を求められたので回転角度を一旦リセットする(カプセルクラスの回転角度とm_Rotateに食い違いがあるため)
	m_Rotate = 0.0f;

	// コライダー用のカプセルクラスの設定
	m_Cupsule.Setup(m_StartPos, m_EndPos, m_Radius);

	m_EffectManager->Create(EFFECT_ID::)
}

void CBeam::Draw(void)
{
}

void CBeam::Update(void)
{
}

void CBeam::Finalize(void)
{
}

void CBeam::Destroy(void)
{
}
