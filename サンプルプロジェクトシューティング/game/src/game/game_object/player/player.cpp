#include "../game_object.h"
#include "player.h"

const float CPlayer::m_change_shotCT = 0.5f;
const float CPlayer::m_ago_pos_time = 0.2f;
const float CPlayer::m_lock_range = 200.0f;
const int   CPlayer::m_max_life = 20;

CPlayer::CPlayer(aqua::IGameObject* parent)
	: IUnit(parent,"Player")
	, m_AgoPosition(aqua::CVector3::ZERO)
	, m_Invincible(false)
	, m_EnemyManager(nullptr)
	, m_LockOnEnemy(nullptr)
{
}

void CPlayer::Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m, CBulletManager* bm)
{
	// ���b�N�I���}�[�J�[�N���X�𐶐����|�C���^������
	m_LockOnMarker = aqua::CreateGameObject<CLockOnMarker>(this);

	// ���C�t�ő�l����
	m_MaxLife = m_max_life;
	m_Life = m_MaxLife;

	// ��{�I�ȃ��j�b�g�̏����������N���X�̏��������Ăяo���čs��
	IUnit::Initialize(pop_pos, wid, hei, dep, color, st_m, bm);
	

	m_UnitType = UNIT_TYPE::PLAYER;
	m_ShotBullet = BULLET_TYPE::NORMAL;
	m_BulletManager->SetPlayer(this);
	m_Speed = 1.0f;

	// ���G���Ԃ̐ݒ�
	m_InvincibleTimer.Setup(2.0f);

	// ���݂̒e��̉��\��
	m_DrawBT.Create(30.0f);
	m_DrawBT.position = aqua::CVector2(aqua::GetWindowWidth() / 2.0f, 0.0f);

	// �e��؂�ւ��^�C�}�[�̃Z�b�g�A�b�v
	m_ChangeCT.Setup(m_change_shotCT);
	m_ShotCT.Setup(0.5f);
	
	// �ǔ����W�Ԋu�^�C�}�[�̃Z�b�g�A�b�v
	m_AgoPosTimer.Setup(m_ago_pos_time);

	// ���b�N�I���^�C�}�[�̃Z�b�g�A�b�v
	m_LockonTimer.Setup(0.1f);

	m_Cube.visible = false;
	// ���f���̃��[�h
	m_Model.Load("data\\model\\player.mv1");

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
		if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::UP) && m_ShotBullet != BULLET_TYPE::NORMAL)
		{
			// -1�̒e�ɕύX(��FAST��NOMAL)
			m_ShotBullet = (BULLET_TYPE)((int)m_ShotBullet - 1);
			m_ChangeCT.Reset();
		}
		// ���L�[
		if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::DOWN) && (int)m_ShotBullet < (int)BULLET_TYPE::MAX - 1)
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
		if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::SPACE))
		{
			// ���@�̐��ʂ��狅������
			m_BulletManager->Create(m_Position + front * 10.0f, front * 10.5f, m_UnitType, m_ShotBullet, this);
			m_ShotCT.Reset();
		}
	}
}

void CPlayer::Move(void)
{
	using namespace aqua::keyboard;
	const float to_delta = 60.0f * aqua::GetDeltaTime();

	// �ړ����x�͍X�V�̓x�Ƀ��Z�b�g
	m_Velocity = aqua::CVector3::ZERO;

	// �s���s��(�r�[���ҋ@��)�Ȃ珈�����~�߂�
	if (!m_MoveFlag)
		return;


	if (Button(KEY_ID::W)) m_Velocity += aqua::CVector3::FRONT;
	if (Button(KEY_ID::S)) m_Velocity += aqua::CVector3::BACK;
	if (Button(KEY_ID::A)) m_Velocity += aqua::CVector3::LEFT;
	if (Button(KEY_ID::D)) m_Velocity += aqua::CVector3::RIGHT;

	if (Button(KEY_ID::RIGHT)) m_Rotate += 2.0f;
	if (Button(KEY_ID::LEFT)) m_Rotate -= 2.0f;

	m_Velocity = m_Velocity.Normalize();
	m_Velocity *= (m_Speed * to_delta);

	// ���b�N�I��
	LockOn();

	
	// �ǂƓ������Ă��炻���Ŏ~�܂�
	if (m_StageManager->StageObjectCollision(m_Position, m_Position + m_Velocity * m_Width, false))
		return;

	// ���W�Ɉړ����x�����Z����
	m_Position += m_Velocity;
	AQUA_DEBUG_LOG("X:" + std::to_string(m_Position.x) + ",Z" + std::to_string(m_Position.z));
}

void CPlayer::LockOn(void)
{
	// ���b�N�I���^�C�}�[�̍X�V
	m_LockonTimer.Update();

	// �^�C�}�[���I�����Ă��邩�A�L�[�����͂��ꂽ
	if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::Q) && m_LockonTimer.Finished())
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
