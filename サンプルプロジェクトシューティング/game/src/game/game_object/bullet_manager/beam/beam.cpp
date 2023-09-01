
#include "beam.h"

const float CBeam::m_max_range = 270.0f;
const float CBeam::m_charge_time = 4.0f;

CBeam::CBeam(aqua::IGameObject* parent)
	:IGameObject(parent,"Beam")
	, m_Damage(0)
	, m_Rotate(0.0f)
	, m_Radius(0.0f)
	, m_DamageFlag(false)
	, m_Finished(false)
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

void CBeam::Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 dir, IUnit* user, CSoundManager* sm, CEffectManager* em)
{
	// ��������r�[���̔��˓_������A�g�p�҂�ݒ�
	m_StartPos = pop_pos;
	m_Radius = bullet_info.radius;
	m_Damage = bullet_info.damage;
	m_Attri = attri;
	m_Dir = dir;
	m_User = user;
	m_SoundManager = sm;
	m_EffectManager = em;

	// �����𐳋K��
	m_Dir.Normalize();

	// ���������]�p�x���Z�o
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

	// �\�����̐ݒ�
	m_PredictionLine.Setup(m_StartPos, m_EndPos, aqua::CColor::RED);

	// �r�[���g�p���͓����Ȃ��悤�g�p�҂̍s���\�t���O���U�ɂ���
	m_User->SetMoveFlag(false);

	// �T�E���h�Ǘ��N���X���擾
	m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");

	// �`���[�W����SE���Đ��J�n
	m_SoundManager->Play(SOUND_ID::s_CHARGE);
}

void CBeam::Draw(void)
{
	m_Capsule.Draw();
	m_PredictionLine.Draw();
}

void CBeam::Update(void)
{
	switch (m_BeamState)
	{
	case CBeam::BEAM_STATE::CHARGE:Charge();break;
	case CBeam::BEAM_STATE::FIRING:Firing();break;
	case CBeam::BEAM_STATE::DESTROY:Destroy();break;
	}
	// �g�p�҂����ʁA�������̓L�����Z��(�Ǝ˒��Ɉړ���)�Œ��f
	if (!m_User || m_User->GetDead() || m_User->GetMoveFlag())
		m_BeamState = BEAM_STATE::DESTROY;

}

void CBeam::Charge(void)
{
	// �`���[�W���̓_���[�W����Ȃ�
	m_DamageFlag = false;
	// �^�C�}�[���X�V���ďI���������Ԃ��ڍs
	m_Timer.Update();
	if (m_Timer.Finished())
		m_BeamState = BEAM_STATE::FIRING;
}

void CBeam::Firing(void)
{
	// ���ˊ֐����Ń_���[�W�t���O���U�Ȃ͍̂ŏ��݂̂Ȃ̂ł��̃^�C�~���O��SE��؂�ւ���
	if (!m_DamageFlag)
	{
		m_SoundManager->Stop(SOUND_ID::s_CHARGE);
		m_SoundManager->Play(SOUND_ID::s_BEAM);
	}
	// �_���[�W�����L���ɂ���
	m_DamageFlag = true;
	// �\�����̉�������߂�
	m_PredictionLine.visible = false;
	
	// �G�t�F�N�g�̍Đ����I���������Ԃ��ڍs
	if (m_Effect->Finished())
		m_BeamState = BEAM_STATE::DESTROY;
}

void CBeam::Destroy(void)
{
	// SE���Đ����Ȃ�~�߂�
	if (m_SoundManager->IsPlaying(SOUND_ID::s_CHARGE))
		m_SoundManager->Stop(SOUND_ID::s_CHARGE);
	else if (m_SoundManager->IsPlaying(SOUND_ID::s_BEAM))
		m_SoundManager->Stop(SOUND_ID::s_BEAM);

	// �_���[�W����𖳌�
	m_DamageFlag = false;

	// �G�t�F�N�g�̕`��𖳌�
	m_Effect->visible = false;

	// �g�p��null�܂��͎���ł��Ȃ��Ȃ�g�p�҂��ēx�s���\�ɂ���
	if (!m_User || !m_User->GetDead())
		m_User->SetMoveFlag(true);
	m_Finished = true;
	DeleteObject();
}
