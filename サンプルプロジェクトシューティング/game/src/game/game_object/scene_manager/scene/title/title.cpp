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

const float CTitleScene::m_un_operation_time = 0.4f;             // ����s�\����
const float CTitleScene::m_dump_width = 64.0f;            // �����ĂȂ�����
const aqua::CVector2 CTitleScene::m_frame_thick = { 12.0f, 9.0f };   // �g�̑���

    /*
     *  @brief      ���쎞�̕����̋K��ʒu
     *
     *  @param[in]  [0] = �^�C�g���X�v���C�g
     *  @param[in]  [1] = �u�X�^�[�g�v�̃{�^��
     */
const aqua::CVector2 CTitleScene::m_basis_position[] = {
    { aqua::CVector2(260.0f  , 480.0f) },  // �u�X�^�[�g�v�̃{�^��
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
    //// �O��BGM���~�����ĐV�K��BGM�Đ�
    //m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");
    //if (m_SoundManager) { m_SoundManager->BGMStop(); m_SoundManager->Play(SOUND_ID::b_TITLE); }

    // �w�i�X�v���C�g�̐���
    m_BackgroundSprite.Create("data\\texture\\title_background2.png");
    m_BackgroundSprite.position = aqua::CVector2::ZERO;

    // ��΂ɔw�i������������ς��Ă�邩���
    m_StartSprite.Create("data\\texture\\ui\\menu\\start.png");
    m_StartSprite.scale = aqua::CVector2(2.0f, 2.0f);
    m_StartSprite.position = m_basis_position[0];

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


    m_StartSprite.Draw();

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


    m_StartSprite.Delete();

    //m_LicenseLabel.Delete();
}


/*
 *  ���쏈��
 */
void CTitleScene::Operation(void)
{
    // Z�L�[  ( ���� )
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
        Change(SCENE_ID::GAMEMAIN);
}