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

	// ��]�p�x���Z�o
	m_Rotate = aqua::RadToDeg(atan2(m_Dir.x, m_Dir.z));

	// �I�_���W�̉�����
	m_EndPos = m_StartPos;
	m_EndPos.z = m_StartPos.z + m_max_range;

	// �s����g���Ďn�_�𒆐S�Ƃ�����]�������s���A���m�ȏI�_���W�����߂�
	aqua::CMatrix mat;
	mat.RotationY(aqua::DegToRad(m_Rotate));
	mat.Translate(m_StartPos);
	m_EndPos *= mat;

	// �I�_���W�����߂�ꂽ�̂ŉ�]�p�x����U���Z�b�g����(�J�v�Z���N���X�̉�]�p�x��m_Rotate�ɐH���Ⴂ�����邽��)
	m_Rotate = 0.0f;

	// �R���C�_�[�p�̃J�v�Z���N���X�̐ݒ�
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
