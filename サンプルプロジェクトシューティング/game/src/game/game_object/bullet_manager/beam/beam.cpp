
#include "beam.h"

const float CBeam::m_max_range = 250.0f;
const float CBeam::m_charge_time = 4.0f;

CBeam::CBeam(aqua::IGameObject* parent)
	:IGameObject(parent,"Beam")
	, m_Damage(0)
	, m_Rotate(0.0f)
	, m_Radius(0.0f)
	, m_DamageFlag(false)
	, m_StartPos(aqua::CVector3::ZERO)
	, m_EndPos(aqua::CVector3::ZERO)
	, m_Dir(aqua::CVector3::ZERO)
	, m_Attri(UNIT_TYPE::PLAYER)
	, m_BeamState(BEAM_STATE::CHARGE)
	, m_Effect(nullptr)
	, m_EffectManager(nullptr)
	, m_User(nullptr)
{
}

void CBeam::Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 dir, IUnit* user, CEffectManager* em)
{
	m_StartPos = pop_pos;
	m_Radius = bullet_info.radius;
	m_Damage = bullet_info.damage;
	m_Attri = attri;
	m_Dir = dir;
	m_User = user;

	m_EffectManager = em;

	m_Dir.Normalize();

	// ��]�p�x���Z�o
	m_Rotate = aqua::RadToDeg(atan2(m_Dir.x, m_Dir.z));

	// �I�_���W�̉�����
	m_EndPos = aqua::CVector3(0.0f, 0.0f, m_max_range);

	// �s����g���Ďn�_�𒆐S�Ƃ�����]�������s���A���m�ȏI�_���W�����߂�
	aqua::CMatrix mat;
	mat.RotationY(aqua::DegToRad(m_Rotate));
	mat.Translate(m_StartPos);

	m_EndPos *= mat;

	// �R���C�_�[�p�̃J�v�Z���N���X�̐ݒ�
	m_Capsule.Setup(m_StartPos, m_EndPos, m_Radius);

	// �G�t�F�N�g�̍Đ�
	m_Effect = m_EffectManager->CreateGetEffect(EFFECT_ID::BEAM, m_StartPos, m_Rotate);


	// �^�C�}�[�̃Z�b�g
	m_Timer.Setup(m_charge_time);

	// �J�v�Z����`�悷��K�v�͂Ȃ�(�����܂ł��R���C�_�[����)�̂�visible��false�ɂ���
	m_Capsule.visible = false;

	m_User->SetMoveFlag(false);
}

void CBeam::Draw(void)
{
	m_Capsule.Draw();
}

void CBeam::Update(void)
{
	switch (m_BeamState)
	{
	case CBeam::BEAM_STATE::CHARGE:Charge();break;
	case CBeam::BEAM_STATE::FIRING:Firing();break;
	case CBeam::BEAM_STATE::DESTROY:Destroy();break;
	}

}

void CBeam::Finalize(void)
{
}

void CBeam::Charge(void)
{
	// �`���[�W���̓_���[�W����Ȃ�
	m_DamageFlag = false;

	// �`���[�W���Ɏg�p�҂����񂾂璆�f(�`���[�W������������Β��f�������˂���)
	if(!m_User||m_User->GetDead())
		m_BeamState = BEAM_STATE::DESTROY;

	m_Timer.Update();
	if (m_Timer.Finished())
		m_BeamState = BEAM_STATE::FIRING;
}

void CBeam::Firing(void)
{
	m_DamageFlag = true;
	if (m_Effect->Finished())
		m_BeamState = BEAM_STATE::DESTROY;
}

void CBeam::Destroy(void)
{
	m_DamageFlag = false;
	m_Effect->visible = false;
	m_User->SetMoveFlag(true);
	DeleteObject();
}
