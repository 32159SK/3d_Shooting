#include "../../../../game_object.h"
#include "../boss_enemy.h"
#include "boss_cannon.h"

const float CBossCannon::m_player_distance = 100.0f;
const float CBossCannon::m_move_time = 2.0f;
const int   CBossCannon::m_position_pattern = 40;

CBossCannon::CBossCannon(aqua::IGameObject* parent)
	: CEnemy(parent, "BossCannon")
	, m_ShotAngle(0.0f)
	, m_AllRangeAttacking(false)
	, m_ReturnFlag(false)
	, m_AllRangeFinish(true)
	, m_AllRangeState(ALLRANGE_STATE::DEFAULT)
	, m_StartPos(aqua::CVector3::ZERO)
	, m_EndPos(aqua::CVector3::ZERO)
	, m_BossEnemy(nullptr)
	, m_Beam(nullptr)
{
}

void CBossCannon::
Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)
{
	// ���b�N�I���}�[�J�[�N���X�𐶐����ă^�[�Q�b�g���v���C���[�ɐݒ�
	m_LockOnMarker = aqua::CreateGameObject<CLockOnMarker>(this);
	m_LockOnMarker->SetTarget(m_Player);

	// ���f���̃��[�h
	m_Model.Load("data\\model\\boss_cannon.mv1");

	// ��{�I�ȃ��j�b�g�̏����������N���X�̏��������Ăяo���čs��
	CEnemy::Initialize(pop_pos, enemy_info, st_m, bm);
}

void CBossCannon::Update(void)
{
	// �ˌ��͂����܂ł��{�X�ˑ��Ȃ̂Ōp������CEnemy�̃A�b�v�f�[�g�͌Ăяo���Ȃ�
	IGameObject::Update();

	// �{�X������łȂ���Ύ��g�̍s���\�t���O�������č��킹��
	if (!m_BossEnemy->GetDead())
		m_BossEnemy->SetMoveFlag(m_MoveFlag);

	// �����Ȃ��Ȃ珈�����Ȃ�
	if (!m_BossEnemy->GetMoveFlag())
		return;
	Move();

	m_Cube.m_HRotate = m_Rotate;
	m_Model.position = m_Position;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CBossCannon::SetPosition(aqua::CVector3 pos)
{
	// �߂�Œ��ł͂Ȃ�
	if (!m_ReturnFlag)
	{
		// �n���ꂽ���W�����̂܂ܑ��
		m_Position = pos;
		return;
	}
	else if (m_ReturnFlag && m_EndPos != pos)	// �߂�Œ����I���n�_��pos����v���Ȃ�(�߂낤�Ƃ��Ă���Ăяo����Ă��Ȃ�)
	{
		// �ړ���̏I�_�Ƃ��đ�������ݍ��W���n�_�ɂ���
		m_EndPos = pos;
		m_StartPos = m_Position;
	}
}

void CBossCannon::SetAllRange(float angle)
{
	// �I�[�������W�U�����t���O��^�ɂ��A�I�����m�t���O���U�ɂ���
	m_AllRangeAttacking = true;
	m_AllRangeFinish = false;
	// �ړ��^�C�}�[��ݒ�
	m_MoveTimer.Setup(m_move_time);

	// ���b�N�I���t���O��^�ɂ���(����Ń��b�N�I���}�[�J�[���`�悳���)
	m_LockON = true;

	// �ړ��̎n�_�Ɍ��ݍ��W����
	m_StartPos = m_Position;

	// �����̊p�x��������
	m_ShotAngle = angle;

	m_AllRangeState = ALLRANGE_STATE::MOVE;
}

void CBossCannon::Shot(void)
{
	CEnemy::Shot();
}

void CBossCannon::Move(void)
{
	// ��Ԃɍ��킹���������s��
	switch (m_AllRangeState)
	{
	case CBossCannon::DEFAULT:		Default();			break;
	case CBossCannon::MOVE:			AllRangeMove();		break;
	case CBossCannon::IRRADIATION:	Irradiation();		break;
	case CBossCannon::RETURN:		ReturnPosition();	break;
	}
	m_Cube.position = m_Position;
}

void CBossCannon::Default(void)
{
	// �v���C���[�Ǝ��g�̋���
	aqua::CVector3 v = m_Player->GetPosition() - m_Position;

	// �x�N�g���̃m�[�}���C�Y
	v.Normalize();

	// 2�_�����]�p�x�����߂�
	m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));
}

void CBossCannon::EasingMove(void)
{
	m_MoveTimer.Update();

	aqua::CVector3 easing_pos = aqua::CVector3::ZERO;
	aqua::CVector3 dir = aqua::CVector3::ZERO;

	// �C�[�W���O�ňړ�����W�����߂�
	easing_pos.x = aqua::easing::OutCubic(m_MoveTimer.GetTime(), m_MoveTimer.GetLimit(), m_StartPos.x, m_EndPos.x);
	easing_pos.z = aqua::easing::OutCubic(m_MoveTimer.GetTime(), m_MoveTimer.GetLimit(), m_StartPos.z, m_EndPos.z);

	// �ړ��̌����������Ŏ��
	dir = easing_pos - m_Position;

	// ���W�����킹��
	m_Position = easing_pos;

	// �����̃x�N�g���ɍ��킹�ĉ�]�p�x���Z�o
	m_Rotate = aqua::RadToDeg(atan2(dir.x, dir.z));
	m_Cube.m_HRotate = m_Rotate;

	// �^�C�}�[�I��
	if (m_MoveTimer.Finished())
		// ���W���I�_�ɍ��킹��
		m_Position = m_EndPos;
}

void CBossCannon::AllRangeMove(void)
{
	// �I�[�������W�U���̏I�_(���ˍ��W)�̉�����
	m_EndPos = aqua::CVector3(0.0f, 0.0f, m_player_distance);

	// ��قǎ�����p�x�ƍs����g���ăv���C���[���W�𒆐S�Ƃ�����]�������s��
	aqua::CMatrix mat;
	mat.RotationY(aqua::DegToRad(m_ShotAngle * m_position_pattern));
	mat.Translate(m_Player->GetPosition());

	// �I�_�̎Z�o����
	m_EndPos *= mat;

	// �C�[�W���O�ňړ�������
	EasingMove();
	// �I�_�ƌ��ݍ��W����v������ˌ��J�n
	if (m_MoveTimer.Finished() && m_EndPos == m_Position)
	{
		m_MoveTimer.Reset();
		// ��Ԃ��Ǝ˂ɑJ��
		m_AllRangeState = ALLRANGE_STATE::IRRADIATION;
		// ���b�N�I���t���O���U�ɂ���
		m_LockON = false;

		m_ReturnFlag = true;
	}
}

void CBossCannon::Irradiation(void)
{
	// �r�[���̃|�C���^��null�Ȃ琶�����|�C���^���擾����֐����Ăяo��
	if (!m_Beam)
	{
		// ��x��{�̓������Ăяo���Č������v���C���[�ɍ��킹��
		Default();

		aqua::CVector3 front;
		front.x = sin(aqua::DegToRad(m_Rotate));
		front.z = cos(aqua::DegToRad(m_Rotate));
		m_Beam = m_BulletManager->CreateGetBeam(m_Position, front, m_UnitType, this);
	}
	// �r�[�����I��
	else if ( m_Beam && m_Beam->GetFinishFlag())
	{
		// �|�C���^��null����
		m_Beam = nullptr;
		// �{�X�G�l�~�[�̖C���W�Z�b�g�N���X���Ăяo��
		m_BossEnemy->SetCannonPosition(m_BossEnemy->GetRotate());
		// ��Ԃ�RETURN�֑J��
		m_AllRangeState = ALLRANGE_STATE::RETURN;
	}
}

void CBossCannon::ReturnPosition(void)
{
	// �C�[�W���O�ňړ�������
	EasingMove();
	if (m_MoveTimer.Finished()&&m_Position == m_EndPos)
	{
		m_MoveTimer.Reset();

		// �I�[�������W�U�������S�ɏI��
		m_AllRangeFinish = true;
		m_AllRangeAttacking = false;
		m_ReturnFlag = false;

		// �n�_�����Z�b�g
		m_StartPos = aqua::CVector3::ZERO;
		m_EndPos = m_StartPos;

		m_AllRangeState = ALLRANGE_STATE::DEFAULT;
	}
}

void CBossCannon::Dead(void)
{
	m_BossEnemy->ResetCannon(m_CannonNumber);
	CEnemy::Dead();
}

