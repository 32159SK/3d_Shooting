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
     */
const aqua::CVector2 CTitleScene::m_basis_position[] = {
    { aqua::CVector2(100.0f  , 400.0f) },  // �^�C�g���X�v���C�g
    { aqua::CVector2(300.0f  , 600.0f) }   // �u�X�^�[�g�v�̃{�^��
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

    // �X�^�[�g�X�v���C�g�̐���
    m_StartSprite.Create("data\\texture\\title\\start.png");
    m_StartSprite.SetCenterPosition(m_basis_position[1]);

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
    // �X�v���C�g�̕`��
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
    // �X�v���C�g�̉��
    m_BackgroundSprite.Delete();
    m_StartSprite.Delete();
}


/*
 *  ���쏈��
 */
void CTitleScene::Operation(void)
{
    // ���p����̂�namespace�Ŋȗ�
    using namespace aqua::mouse;

    // �}�E�X���W��Vector2�^�Ŏ擾
    aqua::CVector2 mpos = aqua::CVector2(GetCursorPos().x, GetCursorPos().y);

    // �摜�̒[�̍��W�����߂�
    float top = m_StartSprite.position.y;
    float left = m_StartSprite.position.x;
    float bottom = m_StartSprite.position.y + m_StartSprite.GetTextureHeight();
    float right = m_StartSprite.position.x + m_StartSprite.GetTextureWidth();

    // �摜�̏�ō��N���b�N�ŃX�^�[�g
    if ((mpos.x > left && mpos.y > top && mpos.x < right && mpos.y < bottom) && Released(BUTTON_ID::LEFT))
        Change(SCENE_ID::GAMEMAIN);
}