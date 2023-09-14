#include "../game_object.h"
#include "player.h"

const float CPlayer::m_shot_ct = 0.5f;
const float CPlayer::m_change_shotCT = 0.5f;
const float CPlayer::m_ago_pos_time = 0.2f;
const float CPlayer::m_invincible_time = 2.0f;
const float CPlayer::m_flash_time = 0.1f;
const float CPlayer::m_lock_range = 200.0f;
const float CPlayer::m_width = 10.0f;
const float CPlayer::m_height = 10.0f;
const float CPlayer::m_depth = 10.0f;
const float CPlayer::m_speed = 1.0f;
const float CPlayer::m_font_size = 30.0f;
const int   CPlayer::m_max_life = 20;

CPlayer::CPlayer(aqua::IGameObject* parent)
	: IUnit(parent, "Player", "Player")
	, m_Invincible(false)
	, m_AgoPosition(aqua::CVector3::ZERO)
	, m_Floor(nullptr)
	, m_EnemyManager(nullptr)
	, m_LockOnEnemy(nullptr)
	, m_LockOnMarker(nullptr)
{
}

void CPlayer::Initialize(aqua::CVector3 pop_pos, CStageManager* st_m, CBulletManager* bm)
{
	// ���C�t�o�[�̐���
	m_LifeBar = aqua::CreateGameObject<CUniqueLifeBar>(this);

	// ���b�N�I���}�[�J�[�N���X�𐶐����|�C���^������
	m_LockOnMarker = aqua::CreateGameObject<CLockOnMarker>(this);

	// ���C�t�ő�l����
	m_MaxLife = m_max_life;
	m_Life = m_MaxLife;

	// ��{�I�ȃ��j�b�g�̏����������N���X�̏��������Ăяo���čs��
	IUnit::Initialize(pop_pos, m_width, m_height, m_depth,st_m, bm);
	
	// ���̑���{�ݒ�
	m_UnitType = UNIT_TYPE::PLAYER;
	m_ShotBullet = BULLET_TYPE::NORMAL;
	m_BulletManager->SetPlayer(this);
	m_Speed = m_speed;

	// ���G���Ԃ̐ݒ�
	m_InvincibleTimer.Setup(m_invincible_time);

	// �t���b�V���^�C�}�[�̐ݒ�
	m_FlashTimer.Setup(m_flash_time);

	// �؂�ւ��^�C�}�[�̃Z�b�g�A�b�v
	m_ChangeCT.Setup(m_change_shotCT);
	// �ˌ��Ԋu�^�C�}�[�̃Z�b�g�A�b�v
	m_ShotCT.Setup(m_shot_ct);
	
	// �ǔ����W�Ԋu�^�C�}�[�̃Z�b�g�A�b�v
	m_AgoPosTimer.Setup(m_ago_pos_time);

	// ���b�N�I���^�C�}�[�̃Z�b�g�A�b�v
	m_LockonTimer.Setup(0.1f);

	// ���f���̃��[�h
	m_Model.Load("data\\model\\player.mv1");

	// ���̃|�C���^�����
	m_Floor = (CFloor*)aqua::FindGameObject("Floor");

	// �e�A�C�R���̕`��ʒu�ϐ���錾
	aqua::CVector2 icon_pos = aqua::CVector2::ZERO;

	// �e�̃A�C�R���̐���
	for (int i = 0; i < (int)BULLET_TYPE::MAX; ++i)
	{
		// �e�햼���Ǘ��N���X����󂯎��A�����p���ăt�@�C���p�X�ɂ���
		m_BulletIcon[i].Create("data\\texture\\ui\\icon\\" + m_BulletManager->GetBulletName((BULLET_TYPE)i) + ".png");
		// X���W�͈�Ԓ[�AY���W�̓��C�t�o�[�̏�ɂ���
		icon_pos.x = (float)(aqua::GetWindowWidth() - m_BulletIcon[i].GetTextureWidth());
		icon_pos.y = m_LifeBar->GetFramePosition().y - m_BulletIcon[i].GetTextureHeight();
		// �Ō�Ɍv�Z�������W����
		m_BulletIcon[i].position = icon_pos;
	}
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
	{
		m_InvincibleTimer.Update();
		// �����Ńt���b�V���^�C�}�[���X�V
		m_FlashTimer.Update();
		// ���@������ł��Ȃ����A�t���b�V���^�C�}�[���I�������玩�@�̉����t���O�����ւ��^�C�}�[�����Z�b�g
		if (!m_DeadFlag && m_FlashTimer.Finished())
		{
			m_Model.visible = !m_Model.visible;
			m_FlashTimer.Reset();
		}
	}
	// �I�����ɖ��G���������^�C�}�[�����Z�b�g
	if (m_InvincibleTimer.Finished())
	{
		// �����t���O��߂��A�^�C�}�[�����Z�b�g���Ă���
		m_Model.visible = true;
		m_FlashTimer.Reset();
		m_Invincible = false;
		m_InvincibleTimer.Reset();
	}

	// �ړ�
	Move();

	// ���g�̎q�I�u�W�F�N�g(���̏ꍇ�̓��C�t�o�[)�̍X�V
	IGameObject::Update();

	// �����œG���ǔ�����p�̃|�W�V����������Ă���
	if (m_AgoPosTimer.Finished())
	{
		m_AgoPosition = m_Position;
		m_AgoPosTimer.Reset();
	}

	// �����蔻��̃L���[�u�ƍ��W�����킹��
	m_Cube.position = m_Position;

	// ���f���̍��W�Ɖ�]�p�x�����킹��
	m_Model.position = m_Cube.position;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CPlayer::Draw(void)
{
	IUnit::Draw();
	// �e�A�C�R���̕`��(���ݑI�𒆂̒e��̂ݕ`�悷��)
	for (int i = 0; i < (int)BULLET_TYPE::MAX; ++i)
		if (i == (int)m_ShotBullet)
			m_BulletIcon[i].Draw();
}

void CPlayer::Finalize(void)
{
	IUnit::Finalize();
	// �e�A�C�R���̉��
	for (int i = 0; i < (int)BULLET_TYPE::MAX; ++i)
		m_BulletIcon[i].Delete();
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
	// ��ꃆ�j�b�g�N���X�̔�e�m�F���Ăяo��
	if (IUnit::CheckHitBeam(type, capsule, damage))
		return true;
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

	// �񕜌�̒l�Ń��C�t�o�[���Čv�Z
	m_LifeBar->CalcLifeBar();
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
		// �z�C�[���̓��͒l���擾
		float wheel_value = (float)aqua::mouse::GetWheel();

		// �}�C�i�X�ł���ΑO�̒e�ɕύX(��REFLECT��NOMAL)
		if (wheel_value > 0 && m_ShotBullet != BULLET_TYPE::NORMAL)
		{
			m_ShotBullet = (BULLET_TYPE)((int)m_ShotBullet - 1);
			m_ChangeCT.Reset();
			// SE���Đ�
			m_SoundManager->Play(SOUND_ID::s_SELECT);
		}
		// �v���X�ł���Ύ��̒e�ɕύX(��NOMAL��REFLECT)
		else if (wheel_value < 0 && (int)m_ShotBullet < (int)BULLET_TYPE::MAX - 1)
		{
			// +1�̒e�ɕύX(��NOMAL��FAST)
			m_ShotBullet = (BULLET_TYPE)((int)m_ShotBullet + 1);
			m_ChangeCT.Reset();
			// SE���Đ�
			m_SoundManager->Play(SOUND_ID::s_SELECT);
		}

	}

	// ���ʍ��W
	aqua::CVector3 front;

	front.x = sin(aqua::DegToRad(m_Rotate));
	front.z = cos(aqua::DegToRad(m_Rotate));

	if (m_ShotCT.Finished() && (aqua::mouse::Button(aqua::mouse::BUTTON_ID::LEFT)))
	{
		// �r�[���łȂ����SE���Đ�(�r�[���̓`���[�W����������Ȃ̂Ńr�[���N���X���ōĐ�)
		if (m_ShotBullet != BULLET_TYPE::BEAM)
			m_SoundManager->Play(SOUND_ID::s_SHOT);
		// ���@�̐��ʂ���e������
			m_BulletManager->Create(m_Position + front * 10.0f, front * 10.5f, m_UnitType, m_ShotBullet, this);
			m_ShotCT.Reset();
	}
}

void CPlayer::Move(void)
{
	// �s���s��(�r�[���ҋ@��)
	if (!m_MoveFlag)
	{
		// �}�E�X�����{�^��(�z�C�[����������)�ŃL�����Z��
		if (aqua::mouse::Button(aqua::mouse::BUTTON_ID::MIDDLE))
		{
			// �C���[�W�I�ɂ͖�����蒆�f����̂Ŏ����_���[�W
			Damage(2);
			m_EffectManager->Create(EFFECT_ID::BEAM_HIT, m_Position,0.0f,8.0f);
			m_MoveFlag = true;
		}
		else
			return;
	}

	// ����
	Operation();

	// ���b�N�I��
	LockOn();

	// �}�E�X�Ǐ]
	MouseTrack();
}

void CPlayer::Damage(int damage)
{
	// �`���[�g���A�����̓_���[�W���󂯂Ȃ�
	if (m_TutorialMode)
		return;

	// ����ȊO�͊��N���X�Ɠ���
	IUnit::Damage(damage);
}

void CPlayer::Dead(void)
{
	IUnit::Dead();
	m_Model.visible = false;
}

void CPlayer::Operation(void)
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

