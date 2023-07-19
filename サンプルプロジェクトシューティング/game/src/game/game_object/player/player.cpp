#include "../game_object.h"
#include "player.h"

const float CPlayer::m_change_shotCT = 0.5f;
const float CPlayer::m_ago_pos_time = 0.2f;
const float CPlayer::m_lock_range = 200.0f;
const float CPlayer::m_width = 10.0f;
const float CPlayer::m_height = 10.0f;
const float CPlayer::m_depth = 10.0f;
const float CPlayer::m_invincible_time = 2.0f;
const float CPlayer::m_font_size = 30.0f;
const int   CPlayer::m_max_life = 20;

CPlayer::CPlayer(aqua::IGameObject* parent)
	: IUnit(parent,"Player")
	, m_Invincible(false)
	, m_AgoPosition(aqua::CVector3::ZERO)
	, m_MousePosition(aqua::CVector3::ZERO)
	, m_OperateStyle(OPERATE_STYLE::MOUSE_ONRY)
	, m_Floor(nullptr)
	, m_EnemyManager(nullptr)
	, m_LockOnEnemy(nullptr)
	, m_LockOnMarker(nullptr)
{
}

void CPlayer::Initialize(aqua::CVector3 pop_pos, CStageManager* st_m, CBulletManager* bm)
{
	// ���b�N�I���}�[�J�[�N���X�𐶐����|�C���^������
	m_LockOnMarker = aqua::CreateGameObject<CLockOnMarker>(this);

	// �f�[�^�v�[���N���X����x�Ăяo���A�^�C�g���őI�����ꂽ������@���m�F����
	CDataRelay* data_pool = (CDataRelay*)aqua::FindGameObject("DataRelay");
	m_OperateStyle = data_pool->GetOperateStyle();

	// ���C�t�ő�l����
	m_MaxLife = m_max_life;
	m_Life = m_MaxLife;

	// ��{�I�ȃ��j�b�g�̏����������N���X�̏��������Ăяo���čs��
	IUnit::Initialize(pop_pos, m_width, m_height, m_depth,st_m, bm);
	

	m_UnitType = UNIT_TYPE::PLAYER;
	m_ShotBullet = BULLET_TYPE::NORMAL;
	m_BulletManager->SetPlayer(this);
	m_Speed = 1.0f;

	// ���G���Ԃ̐ݒ�
	m_InvincibleTimer.Setup(m_invincible_time);

	// ���݂̒e��̉��\��
	m_DrawBT.Create(m_font_size);
	m_DrawBT.position = aqua::CVector2(aqua::GetWindowWidth() / 2.0f, 0.0f);

	// �؂�ւ��^�C�}�[�̃Z�b�g�A�b�v
	m_ChangeCT.Setup(m_change_shotCT);
	m_ShotCT.Setup(0.5f);
	
	// �ǔ����W�Ԋu�^�C�}�[�̃Z�b�g�A�b�v
	m_AgoPosTimer.Setup(m_ago_pos_time);

	// ���b�N�I���^�C�}�[�̃Z�b�g�A�b�v
	m_LockonTimer.Setup(0.1f);

	// ����^�C�}�[�̃Z�b�g�A�b�v
	m_OperateTimer.Setup(0.1f);

	m_Cube.visible = false;
	// ���f���̃��[�h
	m_Model.Load("data\\model\\player.mv1");

	// ���̃|�C���^�����
	m_Floor = (CFloor*)aqua::FindGameObject("Floor");

	// ����X�^�C�����}�E�X�̎��ŏ����珟��ɓ����̂�h��
	if (m_OperateStyle == MOUSE_ONRY)
		m_MousePosition = m_Position;
}

void CPlayer::Update(void)
{
	// �L���[�u�̐�����]�p�x�����킹��
	m_Cube.m_HRotate = m_Rotate;

	// �ǔ����W�Ԋu�^�C�}�[�̍X�V
	m_AgoPosTimer.Update();

	// �ˌ�
	Shot();
	
	// ���G��ԂȂ�^�C�}�[���X�V
	if (m_Invincible)
		m_InvincibleTimer.Update();
	// �I�����ɖ��G���������^�C�}�[�����Z�b�g
	if (m_InvincibleTimer.Finished())
	{
		m_Invincible = false;
		m_InvincibleTimer.Reset();
	}

	// ���j�b�g�̍X�V
	IUnit::Update();

	// �����œG���ǔ�����p�̃|�W�V����������Ă���
	if (m_AgoPosTimer.Finished())
	{
		m_AgoPosition = m_Position;
		m_AgoPosTimer.Reset();
	}

	// ���f���̍��W�Ɖ�]�p�x�����킹��
	m_Model.position = m_Cube.position;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CPlayer::Draw(void)
{
	// ���ݎg�p���̒e��
	switch (m_ShotBullet)
	{
	case BULLET_TYPE::NORMAL:	m_DrawBT.text = "BULLET:NOMAL"; break;
	case BULLET_TYPE::REFLECT:	m_DrawBT.text = "BULLET:REFLECT"; break;
	case BULLET_TYPE::PENETRATE:m_DrawBT.text = "BULLET:PENETRATE"; break;
	case BULLET_TYPE::BEAM:		m_DrawBT.text = "BULLET:BEAM"; break;
	
	default:
		break;
	}
	// 
	m_DrawBT.Draw();
	m_Model.Draw();
	IUnit::Draw();
}

void CPlayer::Finalize(void)
{
	IUnit::Finalize();
	m_DrawBT.Delete();
	m_Model.Unload();
}

bool CPlayer::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)
{
	// ���G�Ȃ珈������߂�
	if (m_Invincible)
		return false;
	// ��ꃆ�j�b�g�N���X�̔�e�m�F���Ăяo���������Ă����疳�G�t���O��^�ɂ���
	if (IUnit::CheckHitBullet(type, sphere, damage))
	{
		m_Invincible = true;
		return true;
	}
	else
		return false;
}

bool CPlayer::CheckHitBeam(UNIT_TYPE type, aqua::CCapsulePrimitive capsule, int damage)
{
	// ���G�Ȃ珈������߂�
	if (m_Invincible)
		return false;
	// ��ꃆ�j�b�g�N���X�̔�e�m�F���Ăяo���������Ă����疳�G�t���O��^�ɂ���
	if (IUnit::CheckHitBeam(type, capsule, damage))
	{
		m_Invincible = true;
		return true;
	}
	else
		return false;
}

void CPlayer::LifeHeal(int heal_value)
{
	// �񕜒l�ƌ��ݎc���C�t�̌v������𒴂���Ȃ����ɍ��킹��
	if (m_max_life <= m_Life + heal_value)
		m_Life = m_max_life;
	else
		m_Life += heal_value;	// �z���Ȃ���΂��̂܂܉񕜒l�����Z����
}

void CPlayer::Shot(void)
{
	// �e��؂�ւ��^�C�}�[�Ǝˌ��^�C�}�[�̍X�V
	m_ChangeCT.Update();
	m_ShotCT.Update();

	if (!m_MoveFlag)
		return;

	// �e�̎�ނ̐؂�ւ�
	if (m_ChangeCT.Finished())
	{
		float wheel_value = (float)aqua::mouse::GetWheel();

		if (wheel_value > 0 && m_ShotBullet != BULLET_TYPE::NORMAL)
		{
			// -1�̒e�ɕύX(��FAST��NOMAL)
			m_ShotBullet = (BULLET_TYPE)((int)m_ShotBullet - 1);
			m_ChangeCT.Reset();
		}
		// ���L�[
		else if (wheel_value < 0 && (int)m_ShotBullet < (int)BULLET_TYPE::MAX - 1)
		{
			// +1�̒e�ɕύX(��NOMAL��FAST)
			m_ShotBullet = (BULLET_TYPE)((int)m_ShotBullet + 1);
			m_ChangeCT.Reset();
		}

	}

	// ���ʍ��W
	aqua::CVector3 front;

	front.x = sin(aqua::DegToRad(m_Rotate));
	front.z = cos(aqua::DegToRad(m_Rotate));

	if (m_ShotCT.Finished())
	{
		switch (m_OperateStyle)
		{
		case COMPOUND:
			if (aqua::mouse::Button(aqua::mouse::BUTTON_ID::LEFT))
			{
				// ���@�̐��ʂ���e������
				m_BulletManager->Create(m_Position + front * 10.0f, front * 10.5f, m_UnitType, m_ShotBullet, this);
				m_ShotCT.Reset();
			}
			break;
		case MOUSE_ONRY: // �e�̎�ނ��r�[���łȂ���Ύ����ŁA�r�[���Ȃ�}�E�X�����{�^���Ŕ���
			if (m_ShotBullet != BULLET_TYPE::BEAM
				||(m_ShotBullet == BULLET_TYPE::BEAM && aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::MIDDLE)))
			{
				// ���@�̐��ʂ��狅������
				m_BulletManager->Create(m_Position + front * 10.0f, front * 10.5f, m_UnitType, m_ShotBullet, this);
				m_ShotCT.Reset();
			}
			break;
		default:
			break;
		}
	}
}

void CPlayer::Move(void)
{
	// �s���s��(�r�[���ҋ@��)�Ȃ珈�����~�߂�
	if (!m_MoveFlag)
		return;

	m_OperateTimer.Update();

	// �X�y�[�X�L�[���������瑀��X�^�C����؂�ւ���
	if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::SPACE)&&m_OperateTimer.Finished())
	{
		if (m_OperateStyle != OPERATE_STYLE::COMPOUND)
			m_OperateStyle = OPERATE_STYLE::COMPOUND;
		else
			m_OperateStyle = OPERATE_STYLE::MOUSE_ONRY;
		m_OperateTimer.Reset();
	}


	// ����X�^�C���ɂ���ď����𕪂���
	switch (m_OperateStyle)
	{
	case OPERATE_STYLE::COMPOUND:	CompoundOperation();break;
	case OPERATE_STYLE::MOUSE_ONRY:	MouseOparation();	break;
	}
	// ���b�N�I��
	LockOn();

	// �}�E�X�Ǐ]
	MouseTrack();
}

void CPlayer::CompoundOperation(void)
{
	using namespace aqua::keyboard;
	const float to_delta = 60.0f * aqua::GetDeltaTime();

	// �ړ����x�͍X�V�̓x�Ƀ��Z�b�g
	m_Velocity = aqua::CVector3::ZERO;


	if (Button(KEY_ID::W)) m_Velocity += aqua::CVector3::FRONT;
	if (Button(KEY_ID::S)) m_Velocity += aqua::CVector3::BACK;
	if (Button(KEY_ID::A)) m_Velocity += aqua::CVector3::LEFT;
	if (Button(KEY_ID::D)) m_Velocity += aqua::CVector3::RIGHT;

	m_Velocity.Normalize();
	m_Velocity *= (m_Speed * to_delta);

	// �ǂƓ������Ă��炻���Ŏ~�܂�
	if (m_StageManager->StageObjectCollision(m_Position, m_Position + m_Velocity * m_Width, false))
		return;

	// ���W�Ɉړ����x�����Z����
	m_Position += m_Velocity;
	AQUA_DEBUG_LOG("X:" + std::to_string(m_Position.x) + ",Z" + std::to_string(m_Position.z));
}

void CPlayer::MouseOparation(void)
{
	// ���N���b�N����Ă���Ԃ͂��̏�ɂƂǂ܂�
	if (aqua::mouse::Button(aqua::mouse::BUTTON_ID::LEFT))
		return;
	const float to_delta = 60.0f * aqua::GetDeltaTime();

	// �v���C���[�Ǝ��g�̋���
	aqua::CVector3 v = m_MousePosition - m_Position;
	v.y = 0.0f;

	// �񎟌��̌������O�ς�����
	float dir = aqua::CVector2::Cross(aqua::CVector2(v.x, v.z), aqua::CVector2(m_Velocity.x, m_Velocity.z));

	// �����̒l�ɂ���Ċp�x��ω�������
	if (dir > 0.001f)
		m_Angle -= aqua::DegToRad(10.0f);
	else if (dir < 0.001f)
		m_Angle += aqua::DegToRad(10.0f);
	
	// �x�N�g���̃m�[�}���C�Y
	m_Velocity.Normalize();
	// �����Ɋp�x�ƎO�p��̒l�������Ĉړ����x�����߂�
	m_Velocity.x = (m_Speed * to_delta) * cos(m_Angle);
	m_Velocity.z = (m_Speed * to_delta) * sin(m_Angle);

	// �ǂƓ������Ă��炻���Ŏ~�܂�
	if (m_StageManager->StageObjectCollision(m_Position, m_Position + m_Velocity * m_Width, false))
		return;

	// ���W�Ɉړ����x�����Z����
	m_Position += m_Velocity;
}

void CPlayer::MouseTrack(void)
{
	// �}�E�X���W����O�Ɖ���2�_���A3�����̃x�N�g���N���X�ŕϐ��ɓ����
	aqua::CVector3 mpos_A = aqua::CVector3((float)aqua::mouse::GetCursorPos().x
		, (float)aqua::mouse::GetCursorPos().y, 0.0f) ;
	aqua::CVector3 mpos_B = aqua::CVector3((float)aqua::mouse::GetCursorPos().x
		, (float)aqua::mouse::GetCursorPos().y, 1.0f) ;

	// �X�N���[�����W�����[���h���W�ɕϊ�����֐����g���A2�_��ϊ�
	mpos_A = ConvScreenPosToWorldPos(mpos_A);
	mpos_B = ConvScreenPosToWorldPos(mpos_B);

	// ����2�_�̃}�E�X���W�Ń��C�L���X�g���s���ڐG���W�����߂�
	m_Floor->Raycast(mpos_A, mpos_B);
	aqua::CVector3 raycast = m_Floor->GetRaycastPos();

	// ���b�N�I�����Ă��Ȃ��Ȃ�}�E�X��Ǐ]���ĉ�]
	if (!m_LockON)
	{
		// ���C�L���X�g���W�Ǝ��g�̍��W�̍��������߂�
		aqua::CVector3 v = raycast - m_Position;

		// �x�N�g���̃m�[�}���C�Y
		v.Normalize();

		// 2�_�����]�l�����߂�
		m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));
	}

	// ����X�^�C�����}�E�X�݂̂łȂ���Α����͏������Ȃ�
	if (m_OperateStyle != OPERATE_STYLE::MOUSE_ONRY)
		return;

	// ���C�L���X�g���W�Ǝ��g�̍��W���ǂ��u�ĂĂȂ��ꍇ���̍��W��������
	if (!m_StageManager->StageObjectCollision(m_Position, raycast))
		m_MousePosition = raycast;
	m_MousePosition.y = 0.0f;
}

void CPlayer::LockOn(void)
{
	// ���b�N�I���^�C�}�[�̍X�V
	m_LockonTimer.Update();

	// �^�C�}�[���I�����Ă��邩�A�L�[�����͂��ꂽ
	if (aqua::mouse::Released(aqua::mouse::BUTTON_ID::RIGHT) && m_LockonTimer.Finished())
	{
		m_LockON = !m_LockON;
		// ��x���b�N�I�����������G���߂��Ȃ��̂ɍēx���b�N�I�����Ȃ��悤null��^����
		m_LockOnEnemy = nullptr;
		m_LockOnMarker->SetTarget(m_LockOnEnemy);
		m_LockonTimer.Reset();
	}

	// �����������b�N�I�����ĂȂ�(�]�v�ȏ��������Ȃ��悤if���͕�����)
	if (!m_LockON)
		return;

	// �G�l�~�[��null�܂��́A�擾�����G�l�~�[������
	if (!m_LockOnEnemy || m_LockOnEnemy->GetDead())
	{
		m_LockOnEnemy = m_EnemyManager->GetNearest(m_Position);
		m_LockOnMarker->SetTarget(m_LockOnEnemy);
		return;
	}

	// �v���C���[�Ǝ��g�̋���
	aqua::CVector3 v = m_LockOnEnemy->GetPosition() - m_Position;

	// �͈͊O�Ȃ烍�b�N�I�����I��
	if (m_lock_range < abs(aqua::CVector3::Length(v)))
	{
		m_LockOnEnemy = nullptr;
		m_LockOnMarker->SetTarget(m_LockOnEnemy);
		m_LockON = false;
		return;
	}

	// �x�N�g���̃m�[�}���C�Y
	v.Normalize();

	// 2�_�����]�p�x�����߂�
	m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));
}

