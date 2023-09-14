#include "../../../game_object.h"
#include "tutorial.h"

const float CTutorial::m_tutorial_move_length = 150.0f;
const float CTutorial::m_key_icon_size = 100.0f;
const float CTutorial::m_mouse_icon_width = 150.0f;
const std::string CTutorial::m_tutorial_path = "data\\csv\\tutorial_text.csv";
const std::string CTutorial::m_key_icon_path = "data\\csv\\key_icon_";
const std::string CTutorial::m_mouse_path = "data\\csv\\mouse_icon_";
const aqua::CVector2 CTutorial::m_icon_pos = aqua::CVector2(aqua::GetWindowWidth() / 2.0f, aqua::GetWindowHeight() / 2.0f);
const aqua::CVector2 CTutorial::m_key_icon_formation[] =
{
	aqua::CVector2(1.0f,0.0f),	// W
	aqua::CVector2(0.0f,1.0f),	// A
	aqua::CVector2(1.0f,1.0f),	// S
	aqua::CVector2(2.0f,1.0f)	// D
};

CTutorial::CTutorial(aqua::IGameObject* parent)
	:CGameMain(parent)
	,m_TextDrawCount(0)
	,m_MoveLength(0.0f)
	,m_NotBeamFiring(true)
	,m_PlayerPos(aqua::CVector3::ZERO)
	,m_State(STATE::START)
	,m_Phase(TUTORIAL_PHASE::MOVE)
	,m_TutorialMessage(nullptr)
{
}

void CTutorial::Initialize(void)
{
	// ���N���X�ƂȂ��Ă���g�Q�[�����C���V�[���̏��������Ă�
	CGameMain::Initialize();

	// �X�v���C�g�̐���
	for (int i = 0; i < 4; ++i)
	{
		// i�������Ă��ꂼ��̃t�@�C���p�X�ɂ���
		m_KeyIcon[i].Create(m_key_icon_path + std::to_string(i) + ".png");
		// �`����W�̌v�Z
		m_KeyIcon[i].position = m_key_icon_formation[i] * m_key_icon_size + m_icon_pos;
		
		// ���łɃ}�E�X�A�C�R������������
		if (i < 3)
		{
			// �L�[�A�C�R�����l��i�������Ă��ꂼ��̃t�@�C���p�X�ɂ���
			m_MouseIcon[i].Create(m_mouse_path + std::to_string(i) + ".png");
			// �}�E�X�A�C�R���͑S���������W��OK(�킴�킴���炷�����b�g���Ȃ�)
			m_MouseIcon[i].position = m_icon_pos;
		}
	}
}

void CTutorial::Update(void)
{
	// �q�I�u�W�F�N�g�̍X�V
	IGameObject::Update();

	// ��Ԃɉ����ď����𕪂���
	switch (m_State)
	{
	case CTutorial::STATE::START:	TutorialStart();	break;
	case CTutorial::STATE::PLAY:	TutorialPlay();		break;
	case CTutorial::STATE::END:		TutorialFinish();	break;
	}
}

void CTutorial::Draw(void)
{
	IGameObject::Draw();


	// �L�[�A�C�R���̕`��
	if(m_Phase== TUTORIAL_PHASE::MOVE)
		for (int i = 0; i < 4; ++i)
			m_KeyIcon[i].Draw();

	// �}�E�X�A�C�R���`��
	else if(m_Phase== TUTORIAL_PHASE::MOUSE
		|| m_Phase == TUTORIAL_PHASE::SHOT
		|| m_Phase == TUTORIAL_PHASE::LOCKON)
		MouseIconDraw();
}

void CTutorial::Finalize(void)
{
	IGameObject::Finalize();

	// �A�C�R���̍폜
	for (int i = 0; i < 4; ++i)
	{
		m_KeyIcon[i].Delete();
		if (i < 3)
			m_MouseIcon[i].Delete();
	}
}

void CTutorial::TutorialStart(void)
{
	// �q�I�u�W�F�N�g��T�����X�e�[�W�Ǘ��̃|�C���^�擾
	CStageManager* sm = (CStageManager*)IGameObject::FindChild("StageManager");
	// �`���[�g���A���Z�b�g
	m_Player->SetTutorial();
	m_EnemyManager->SetTutorial();
	sm->SetTutorial();

	// ��Ԃ�J��
	m_State = STATE::PLAY;
}

void CTutorial::TutorialPlay(void)
{
	// �J�����̍X�V
	m_Camera.m_Target = m_Player->GetPosition();
	m_Camera.Update();
	// �q�I�u�W�F�N�g�̍X�V
	IGameObject::Update();

	// �i�K�ɉ����ď����𕪂���
	switch (m_Phase)
	{
	case CTutorial::TUTORIAL_PHASE::MOVE:	TutorialMove();		break;
	case CTutorial::TUTORIAL_PHASE::MOUSE:	TutorialMouse();	break;
	case CTutorial::TUTORIAL_PHASE::LOCKON:	TutorialLockOn();	break;
	case CTutorial::TUTORIAL_PHASE::SHOT:	TutorialShot();		break;
	case CTutorial::TUTORIAL_PHASE::BEAM:	TutorialBeam();		break;
	}

}

void CTutorial::TutorialFinish(void)
{
	// �^�C�g���V�[���ɐ؂�ւ���
	Change(SCENE_ID::TITLE);
}

void CTutorial::TutorialMove(void)
{
	// �v���C���[�̌��ݍ��W�����̃N���X�ŋL�^���Ă�����W�ƈقȂ遨�ړ����Ă���
	if (m_Player->GetPosition() != m_PlayerPos)
		// �������ړ������Ƃ��ĉ��Z
		m_MoveLength += abs(aqua::CVector3::Length(m_Player->GetPosition() - m_PlayerPos));

	if (m_MoveLength > m_tutorial_move_length)
	{
		// 
		MessageSetUp();
	}
}

void CTutorial::TutorialMouse(void)
{
}

void CTutorial::TutorialLockOn(void)
{
	m_EnemyManager->Create(aqua::CVector3::ZERO, ENEMY_ID::MOB);
}

void CTutorial::TutorialShot(void)
{

}

void CTutorial::TutorialBeam(void)
{
	// �������͒e�����Ƀr�[����
	m_Player->SetBulletType(BULLET_TYPE::BEAM);

	// �s���t���O�ƈ�v���Ȃ�
	if (m_Player->GetMoveFlag() != m_NotBeamFiring)
	{
		// �r�[���m�F�t���O�ɍs���t���O����
		// ����ň�v���Ȃ��̂̓r�[��������or�I�������ŏ��̃t���[���݂̂ɂȂ�(���̕����̏����̓r�[���O��ł����s�������Ȃ�)
		m_NotBeamFiring = m_Player->GetMoveFlag();
		
		// ���b�Z�[�W�`�揈�����s���A���̒i�K��
		MessageSetUp();
	}
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

void CTutorial::MouseIconDraw(void)
{
	// �}�E�X�A�C�R���̕`��
	m_MouseIcon[0].Draw();
	// ����"������Ă��鎞����"�`�悷��
	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
		m_MouseIcon[1].Draw();
	// �N���b�N�摜
	else if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::RIGHT))
	{
		// �E�N���b�N�͔��]
		m_MouseIcon[1].scale.x *= -1.0f;
		m_MouseIcon[1].Draw();
	}
	// �z�C�[���摜
	else if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::MIDDLE)
		|| aqua::mouse::GetWheel() != 0.0f)
		m_MouseIcon[2].Draw();
}

void CTutorial::MessageSetUp(void)
{
	// �O�̂���null�łȂ��Ȃ珈�����Ȃ�
	if (m_TutorialMessage)
		return;

	// �J�E���g�𑝂₵���b�Z�[�W�`��p�N���X�𐶐�����
	m_TextDrawCount++;

	m_TutorialMessage = aqua::CreateGameObject<CTutorialMessage>(this);
	m_TutorialMessage->Initialize(m_TutorialText[m_TextDrawCount]);
}
