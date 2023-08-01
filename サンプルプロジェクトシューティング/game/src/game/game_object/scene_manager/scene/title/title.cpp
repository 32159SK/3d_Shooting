/*
 *  @file       title_scene.cpp
 *  @brief      �^�C�g���V�[��
 *  @author     Miyu Hujita
 *  @date       2021/07/01
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include"..\title\title.h"
#include "..\..\..\sound_manager\sound_manager.h"

    /*
     *  @brief      ���쎞�̕����̋K��ʒu
     *  @param[in]  [0] = �^�C�g���X�v���C�g
     *  @param[in]  [1] = �u�X�^�[�g�v�̃{�^��
     *  @param[in]  [2] = �u�L�[�}�E����v�̃{�^��
     *  @param[in]  [3] = �u�}�E�X����v�̃{�^��
     */
const aqua::CVector2 CTitleScene::m_basis_position[] = {
    { aqua::CVector2(320.0f  , 520.0f) },  // �u�L�[�}�E����v�̃{�^��
    { aqua::CVector2(640.0f  , 520.0f) }   // �u�}�E�X����v�̃{�^��
};

/*
 *  �R���X�g���N�^
 */
CTitleScene::
CTitleScene(aqua::IGameObject* parent)
    : IScene(parent, "TitleScene")
    , m_OperateStyle(OPERATE_STYLE::COMPOUND)
{
}

/*
 *  ������
 */
void
CTitleScene::
Initialize(void)
{
    // �O��BGM���~�����ĐV�K��BGM�Đ�
    m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");
    if (m_SoundManager)
    {
        m_SoundManager->BGMStop();
        m_SoundManager->Play(SOUND_ID::b_TITLE);
    }

    // �w�i�X�v���C�g�̐���
    m_BackgroundSprite.Create("data\\texture\\title\\title_background.png");
    m_BackgroundSprite.position = aqua::CVector2::ZERO;

    // �I���摜�̐���
    m_ChoiceSprite[0].Create("data\\texture\\title\\compound_button.png");
    m_ChoiceSprite[1].Create("data\\texture\\title\\mouse_button.png");


    for (int i = 0; i < 2; ++i)
        m_ChoiceSprite[i].position = m_basis_position[i];

    // BGM���Đ�
    m_SoundManager->Play(SOUND_ID::b_TITLE);
}

/*
 *  �X�V
 */
void
CTitleScene::
Update(void)
{
    Operation();
}

/*
 *  �`��
 */
void
CTitleScene::
Draw(void)
{
    // �w�i�X�v���C�g�̕`��
    m_BackgroundSprite.Draw();


    for (int i = 0; i < 2; ++i)
        m_ChoiceSprite[i].Draw();

}

/*
 *  ���
 */
void
CTitleScene::
Finalize(void)
{
    // �w�i�X�v���C�g�̉��
    m_BackgroundSprite.Delete();


    for (int i = 0; i < 2; ++i)
        m_ChoiceSprite[i].Delete();

    //m_LicenseLabel.Delete();
}


/*
 *  ���쏈��
 */
void CTitleScene::Operation(void)
{

    // ����Ȃ̂ł�₱�����������͂��邾�����ʂƔ��f
    if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::RIGHT))
    {
        m_OperateStyle = OPERATE_STYLE::MOUSE_ONRY;     // ������@���}�E�X�݂̂�
        m_SoundManager->Play(SOUND_ID::s_SELECT);
    }
    else if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::LEFT))
    {
        m_OperateStyle = OPERATE_STYLE::COMPOUND;       // ������@���L�[�}�E��
        m_SoundManager->Play(SOUND_ID::s_SELECT);
    }

    // Z�L�[  ( ���� )
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
    {
        CDataRelay* data_relay = (CDataRelay*)aqua::FindGameObject("DataRelay");
        data_relay->SetOPerateStyle(m_OperateStyle);
        Change(SCENE_ID::GAMEMAIN);
    }
}