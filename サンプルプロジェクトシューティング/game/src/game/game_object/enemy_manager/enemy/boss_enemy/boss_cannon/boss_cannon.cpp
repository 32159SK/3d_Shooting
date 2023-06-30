#include "../../../../game_object.h"
#include "../boss_enemy.h"
#include "boss_cannon.h"

const float CBossCannon::m_player_distance = 100.0f;
const float CBossCannon::m_move_time = 5.0f;

CBossCannon::CBossCannon(aqua::IGameObject* parent)
	: CEnemy(parent, "BossCannon")
{
}

void CBossCannon::
Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)
{
	CEnemy::Initialize(pop_pos, enemy_info, st_m, bm);
	// ���f���͉�
	m_Model.Load("data\\model\\fixed_enemy.mv1");
	m_Model.position = m_Position;

	m_BossEnemy = (CBossEnemy*)aqua::FindGameObject("BossEnemy");

	m_Cube.visible = false;
}

void CBossCannon::Update(void)
{
	// �ˌ��͂����܂ł��{�X�ˑ��Ȃ̂Ōp������CEnemy�̃A�b�v�f�[�g�͌Ăяo���Ȃ�
	IGameObject::Update();

	if (m_Player->GetTimeStop())
		return;

	m_MoveTimer.Update();


	if (!m_MoveFlag)
		return;
	
	Move();

	m_Cube.m_HRotate = m_Rotate;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CBossCannon::Draw(void)
{
	m_Model.Draw();
	CEnemy::Draw();
}

void CBossCannon::Finalize(void)
{
	CEnemy::Finalize();
	m_Model.Unload();
}

void CBossCannon::SetPosition(aqua::CVector3 pos)
{
	// �߂�Œ��ł͂Ȃ�
	if (!m_ReturnFlag)
	{
		m_Position = pos;
		return;
	}
	else if (m_EndPos != pos)	// �߂�Œ����I���n�_��pos����v���Ȃ�(�߂낤�Ƃ��Ă���Ăяo����Ă��Ȃ�)
	{
		m_EndPos = pos;
		m_StartPos = m_Position;
	}
}

void CBossCannon::SetAllRange(void)
{
	m_AllRangeAttacking = true;
	m_MoveTimer.Setup(m_move_time);

	// �ړ��̎n�_�Ɍ��ݍ��W����
	m_StartPos = m_Position;

	// �I�[�������W�U���̏I�_(���ˍ��W)�̉�����
	m_EndPos = aqua::CVector3(0.0f, 0.0f, m_player_distance);

	// �����Ŋp�x�����
	float rotate = (float)aqua::Rand(360);

	// ��قǎ�����p�x�ƍs����g���ăv���C���[���W�𒆐S�Ƃ�����]�������s��
	aqua::CMatrix mat;
	mat.RotationY(aqua::DegToRad(rotate));
	mat.Translate(m_Player->GetAgoPos());

	// �I�_�̎Z�o����
	m_EndPos *= mat;
}

void CBossCannon::SetMoveFlag(bool flag)
{
	// ���̊֐����Ăяo�����̂̓r�[�������or�Ǝ˂��I���̍�
	// �����Ȃ����͖߂�Ȃ������A�ēx������悤�ɂ���̂Ɩ߂��n�߂�^�C�~���O�������Ȃ̂�m_ReturnFlag�ɂ�flag��������
	m_MoveFlag = flag;
	m_ReturnFlag = flag;
}

void CBossCannon::Shot(void)
{
	CEnemy::Shot();
}

void CBossCannon::Move(void)
{
	if (m_MoveTimer.Finished())
	{
		m_Position = m_EndPos;

		// �v���C���[�Ǝ��g�̋���
		aqua::CVector3 v = m_Player->GetPosition() - m_Position;

		// �x�N�g���̃m�[�}���C�Y
		v.Normalize();

		// 2�_�����]�p�x�����߂�
		m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));
	}

	if (m_AllRangeAttacking)// �I�[�������W�U�����s��
		AllRangeAttack();
	else if (m_ReturnFlag && m_EndPos != m_Position)// �߂��̍��W�͊��Ɏw��ς݂Ȃ̂ł����Ɍ����Ĉړ��������OK
		EasingMove();

	m_Cube.position = m_Position;
}

void CBossCannon::EasingMove(void)
{
	aqua::CVector3 easing_pos = aqua::CVector3::ZERO;
	aqua::CVector3 dir = aqua::CVector3::ZERO;

	// �C�[�W���O�ňړ�������
	easing_pos.x = aqua::easing::OutCubic(m_MoveTimer.GetTime(), m_MoveTimer.GetLimit(), m_StartPos.x, m_EndPos.x);
	easing_pos.z = aqua::easing::OutCubic(m_MoveTimer.GetTime(), m_MoveTimer.GetLimit(), m_StartPos.z, m_EndPos.z);

	// �ړ��̌����������Ŏ��
	dir = m_Position - easing_pos;

	// ���W�����킹��
	m_Position = easing_pos;

	// �^�C�}�[�I��
	if (m_MoveTimer.Finished())
	{
		// ���W���I�_�ɍ��킹��
		m_Position = m_EndPos;
		// m_ReturnFlag���^���A��
		if (m_ReturnFlag)
			// �A��I�����̂ŃI�[�������W�U�������S�ɏI��
			m_AllRangeFinish = true;
	}

	// �ړ����x�ɍ��킹�ĉ�]�p�x���Z�o
	m_Rotate = aqua::RadToDeg(atan2(dir.x, dir.z));
	m_Cube.m_HRotate = m_Rotate;
}

void CBossCannon::AllRangeAttack(void)
{
	// �C�[�W���O�ňړ�������
	EasingMove();
	// �I�_�ƌ��ݍ��W����v������ˌ��J�n
	if (m_EndPos == m_Position)
		Shot();
}

