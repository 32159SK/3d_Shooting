#include "../../../game_object.h"
#include "tutorial.h"

const int	CTutorial::m_max_text_count = 12;
const int	CTutorial::m_lock_on_text_num = 7;
const float CTutorial::m_tutorial_move_length = 250.0f;
const float CTutorial::m_mouse_move_time = 1.0f;
const float CTutorial::m_shot_time = 4.0f;
const std::string CTutorial::m_tutorial_path = "data\\csv\\tutorial_text.csv";

CTutorial::CTutorial(aqua::IGameObject* parent)
	:CGameMain(parent)
	,m_TextDrawCount(0)
	,m_MoveLength(0.0f)
	,m_EnemyPop(false)
	,m_ShotFlag(false)
	,m_NotBeamFiring(true)
	,m_PlayerPos(aqua::CVector3::ZERO)
	,m_State(STATE::START)
	,m_Phase(TUTORIAL_PHASE::MOVE)
	,m_TutorialEnemy(nullptr)
	,m_TutorialMessage(nullptr)
{
}

void CTutorial::Initialize(void)
{
	// ���N���X�ƂȂ��Ă���g�Q�[�����C���V�[���̏��������Ă�
	CGameMain::Initialize();

	// �`���[�g���A���e�L�X�g�̃��[�h
	TextDataLoad();
}

void CTutorial::Update(void)
{
	// ��Ԃɉ����ď����𕪂���
	switch (m_State)
	{
	case CTutorial::STATE::START:	TutorialStart();	break;
	case CTutorial::STATE::PLAY:	TutorialPlay();		break;
	case CTutorial::STATE::END:		TutorialFinish();	break;
	}

	// �q�I�u�W�F�N�g�̍X�V
	IGameObject::Update();

	// Z�L�[�ł��ł��^�C�g���V�[���ɖ߂��
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
		Change(SCENE_ID::TITLE);
}

void CTutorial::Draw(void)
{
	IGameObject::Draw();
}

void CTutorial::Finalize(void)
{
	IGameObject::Finalize();
}

void CTutorial::TutorialStart(void)
{
	// �q�I�u�W�F�N�g��T�����X�e�[�W�Ǘ��̃|�C���^�擾
	CStageManager* sm = (CStageManager*)IGameObject::FindChild("StageManager");
	// �`���[�g���A���Z�b�g
	m_Player->SetTutorial();
	m_EnemyManager->SetTutorial();
	sm->SetTutorial();
	// �E�F�[�u�؂�ւ��������Ăяo���A�X�e�[�W�𐶐�
	sm->WaveChange(0);

	// �ŏ��̃��b�Z�[�W��`��
	MessageSetUp();

	// ��Ԃ�J��
	m_State = STATE::PLAY;
}

void CTutorial::TutorialPlay(void)
{
	// �J�����̍X�V
	m_Camera.m_Target = m_Player->GetPosition();
	m_Camera.Update();


	// �i�K�ɉ����ď����𕪂���
	switch (m_Phase)
	{
	case CTutorial::TUTORIAL_PHASE::MOVE:	TutorialMove();		break;
	case CTutorial::TUTORIAL_PHASE::MOUSE:	TutorialMouse();	break;
	case CTutorial::TUTORIAL_PHASE::SHOT:	TutorialShot();		break;
	case CTutorial::TUTORIAL_PHASE::LOCKON:	TutorialLockOn();	break;
	case CTutorial::TUTORIAL_PHASE::BEAM:	TutorialBeam();		break;
	}

}

void CTutorial::TutorialFinish(void)
{
}

void CTutorial::TutorialMove(void)
{
	// �v���C���[�̌��ݍ��W�����̃N���X�ŋL�^���Ă�����W�ƈقȂ遨�ړ����Ă���
	if (m_Player->GetPosition() != m_PlayerPos)
	{
		// �������ړ������Ƃ��ĉ��Z
		m_MoveLength += abs(aqua::CVector3::Length(m_Player->GetPosition() - m_PlayerPos));
		// ���W���ĕۑ�
		m_PlayerPos = m_Player->GetPosition();
	}
	
	// �ړ����������l�𒴂����烁�b�Z�[�W��\�������̒i�K��
	if (m_MoveLength > m_tutorial_move_length)
	{
		// ���b�Z�[�W�̃Z�b�g�A�b�v����
		if (MessageSetUp())
		{
			// ���̒i�K��
			m_Phase = TUTORIAL_PHASE::MOUSE;

			// �}�E�X���W�����̒i�K�ŕۑ����Ă���
			m_MousePos = aqua::mouse::GetCursorPos();
			// �^�C�}�[�̃Z�b�g�A�b�v
			m_TutorialTimer.Setup(m_mouse_move_time);
		}
	}
}

void CTutorial::TutorialMouse(void)
{
	// �}�E�X���W�����̃N���X�ŋL�^���Ă�����W�ƈقȂ遨�ړ����Ă���
	if (aqua::mouse::GetCursorPos() != m_MousePos)
	{
		// �^�C�}�[���X�V
		m_TutorialTimer.Update();

		// �^�C�}�[���I��
		if (m_TutorialTimer.Finished())
			// ���b�Z�[�W�̃Z�b�g�A�b�v
			MessageSetUp();

		// �}�E�X���W���ĕۑ�
		m_MousePos = aqua::mouse::GetCursorPos();
	}

	// �^�C�}�[���I��
	else if (m_TutorialTimer.Finished() && MessageSetUp())
	{
		// ���̒i�K��
		m_Phase = TUTORIAL_PHASE::SHOT;

		// �^�C�}�[�̍Đݒ�
		m_TutorialTimer.Setup(m_shot_time);
	}
}

void CTutorial::TutorialShot(void)
{
	// �}�E�X���N���b�N
	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
		m_ShotFlag = true;

	// �ˌ������ꂽ��^�C�}�[�̍X�V
	if (m_ShotFlag)
		m_TutorialTimer.Update();

		// �^�C�}�[���I��
	if (m_TutorialTimer.Finished() && MessageSetUp())
	{
		// ���̒i�K��
		m_Phase = TUTORIAL_PHASE::LOCKON;

		// �^�C�}�[�̃��Z�b�g
		m_TutorialTimer.Reset();
	}
}

void CTutorial::TutorialLockOn(void)
{
	m_TutorialTimer.Update();

	// �^�C�}�[���I�����Ă��邩���̉񐔈ȏチ�b�Z�[�W��`�悵�Ȃ�
	if (m_TutorialTimer.Finished() && m_TextDrawCount < m_lock_on_text_num)
	{
		// �G���o�������Ă��Ȃ�
		if (!m_EnemyPop && MessageSetUp())
		{
			// ���b�N�I���m�F�p�̓G���o��������(�{�X���ʐ����𗬗p���ă|�C���^���󂯎���悤�ɂ���)
			m_TutorialEnemy = m_EnemyManager->CreateBossParts(aqua::CVector3::ZERO, ENEMY_ID::FIXED);
			// �o���������̂Ńt���O��^��
			m_EnemyPop = true;

			// �^�C�}�[�̃��Z�b�g
			m_TutorialTimer.Reset();
		}
		// �^�C�}�[���I��������V�������b�Z�[�W�𗬂�
		else if(m_EnemyPop)
		{
			MessageSetUp();			// �^�C�}�[�̃��Z�b�g
			m_TutorialTimer.Reset();
		}
	}

	// �G������ł��`��񐔂������Ă��胁�b�Z�[�W�̕`�悪�s�����玟�̒i�K��
	if (m_TutorialEnemy->GetDead() && m_TextDrawCount == m_lock_on_text_num &&MessageSetUp())
		m_Phase = TUTORIAL_PHASE::BEAM;
}

void CTutorial::TutorialBeam(void)
{
	// �e�����Ƀr�[����
	m_Player->SetBulletType(BULLET_TYPE::BEAM);

	// �s���t���O�ƈ�v���Ȃ�
	if (m_Player->GetMoveFlag() != m_NotBeamFiring && MessageSetUp())
	{
		// �r�[���m�F�t���O�ɍs���t���O����
		// ����ň�v���Ȃ��̂̓r�[��������or�I�������ŏ��̃t���[���݂̂ɂȂ�(���̕����̏����̓r�[���O��ł����s�������Ȃ�)
		m_NotBeamFiring = m_Player->GetMoveFlag();
	}
	
	// ���b�Z�[�W�̕`��񐔂��e�L�X�g�����𒴂���Ȃ��Ԃ�J��
	if (m_TextDrawCount > m_max_text_count)
		m_State = STATE::END;
}

void CTutorial::TextDataLoad(void)
{
	// aqua����CSV�N���X���Ăяo���ă��[�h
	aqua::CCSVLoader csv;
	csv.Load(m_tutorial_path);

	int file_row = csv.GetRows();

	for (int i = 0; i < file_row; ++i)
		// �ǂݍ��񂾃e�L�X�g�𖖔��ɒǉ�
		m_TutorialText.push_back(csv.GetString(i, 0));

	// CSV�̃A�����[�h
	csv.Unload();
}

bool CTutorial::MessageSetUp(void)
{
	// ���̃��b�Z�[�W�����݂��A���ꂪ�I�����Ă��Ȃ��Ȃ珈���������U��Ԃ�
	if (m_TutorialMessage && !m_TutorialMessage->GetEnd())
		return false;
	else if(m_TutorialMessage)
		// ���g���폜����(null���͒ʂ�Ȃ�)
		m_TutorialMessage->DeleteObject();

	// ���b�Z�[�W�`��p�N���X�𐶐�����
	m_TutorialMessage = aqua::CreateGameObject<CTutorialMessage>(this);
	m_TutorialMessage->Initialize(m_TutorialText[m_TextDrawCount]);

	// �J�E���g�𑝂₷
	m_TextDrawCount++;
	return true;
}
