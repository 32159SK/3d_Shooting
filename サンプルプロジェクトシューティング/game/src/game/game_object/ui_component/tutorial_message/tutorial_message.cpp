#include "tutorial_message.h"

const float CTutorialMessage::m_pop_time = 1.0f;
const float CTutorialMessage::m_wait_time = 5.0f;
const float CTutorialMessage::m_background_panel_height = 50.0f;

CTutorialMessage::CTutorialMessage(aqua::IGameObject* parent)
	:IUIComponent(parent,"TutorialMassage")
{
}

void CTutorialMessage::Initialize(std::string text)
{
    // �^�C�}�[�̃Z�b�g�A�b�v
    m_Timer.Setup(m_pop_time);

    // ���x���̐���
    m_Message.Create(20, 2);

    // �\������e�L�X�g����
    m_Message.text = text;

    // ���W�v�Z
    m_Message.position.x = ((float)aqua::GetWindowWidth() + (float)m_Message.GetTextWidth()) / 2.0f;
    m_Message.position.y = (float)aqua::GetWindowHeight() - m_background_panel_height;

    // �w�i�E�C���h�E�p�l���̃Z�b�g�A�b�v
    m_WindowPanel.Setup({ 0.0f,(float)aqua::GetWindowHeight() }, (float)aqua::GetWindowWidth(), m_background_panel_height, 0x80000000);

    // ��Ԃ��|�b�v�C��(����)��
    m_State = STATE::POP_IN;

}

void CTutorialMessage::Update(void)
{
    // �^�C�}�[�̍X�V
    m_Timer.Update();

    // ��Ԃɂ���ď����𕪂���
    switch (m_State)
    {
    case STATE::POP_IN:        PopIn();        break;
    case STATE::WAIT:          Wait();         break;
    case STATE::POP_OUT:       PopOut();       break;
    case STATE::END:           DeleteObject(); break;
    default:
        break;
    }
}

void CTutorialMessage::Draw(void)
{
	// �E�C���h�E�ƃ��b�Z�[�W�̕`��
	m_WindowPanel.Draw();
	m_Message.Draw();
}

void CTutorialMessage::Finalize(void)
{
	m_Message.Delete();
}

void CTutorialMessage::PopIn(void)
{
    // �p�l���̎n�_�ƏI�_�����߂�
    float start = (float)aqua::GetWindowHeight();
    float end = (float)aqua::GetWindowHeight() - m_background_panel_height;

    // position�̉��ϐ�
    float pos_y = aqua::easing::OutCubic(m_Timer.GetTime(), m_Timer.GetLimit(), start, end);

    // �v�Z�������W�̑��
    m_WindowPanel.position.y = pos_y;
    m_Message.position.y = pos_y;

    // �^�C�}�[�I��
    if (m_Timer.Finished())
    {
        // �^�C�}�[�̍Đݒ�
        m_Timer.Setup(m_wait_time);
        // ��Ԃ̑J��
        m_State = STATE::WAIT;
    }
}

void CTutorialMessage::Wait(void)
{
    // �^�C�}�[�I��
    if (m_Timer.Finished())
    {
        // �^�C�}�[�̍Đݒ�
        m_Timer.Setup(m_pop_time);
        // ��Ԃ̑J��
        m_State = STATE::POP_OUT;
    }
}

void CTutorialMessage::PopOut(void)
{
    // �p�l���̎n�_�ƏI�_�����߂�
    float start = (float)aqua::GetWindowHeight() - m_background_panel_height;
    float end = (float)aqua::GetWindowHeight();

    // position�̉��ϐ�
    float pos_y = aqua::easing::InCubic(m_Timer.GetTime(), m_Timer.GetLimit(), start, end);

    // �v�Z�������W�̑��
    m_WindowPanel.position.y = pos_y;
    m_Message.position.y = pos_y;

    // �^�C�}�[�I���ŏI���
    if (m_Timer.Finished()) m_State = STATE::END;
}
