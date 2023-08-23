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



    //m_LicenseLabel.Delete();
}


/*
 *  ���쏈��
 */
void CTitleScene::Operation(void)
{

    // Z�L�[  ( ���� )
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
    {
        CDataRelay* data_relay = (CDataRelay*)aqua::FindGameObject("DataRelay");
        Change(SCENE_ID::GAMEMAIN);
    }
}