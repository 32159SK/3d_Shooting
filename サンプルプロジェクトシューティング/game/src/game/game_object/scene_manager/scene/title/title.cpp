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
    { aqua::CVector2(300.0f  , 600.0f) },  // �u�X�^�[�g�v�̃{�^��
    { aqua::CVector2(700.0f  , 600.0f) }   // �u�`���[�g���A���v�̃{�^��
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
    m_StartSprite.SetCenterPosition(m_basis_position[0]);

    // �`���[�g���A���X�v���C�g�̐���
    m_TutorialSprite.Create("data\\texture\\title\\tutorial.png");
    m_TutorialSprite.SetCenterPosition(m_basis_position[1]);

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
    m_TutorialSprite.Draw();
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
    m_TutorialSprite.Delete();
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

    // �摜�̒[���i�[����ϐ���錾
    float top[2];
    float left[2];
    float bottom[2];
    float right[2];

    // �X�^�[�g�摜�̒[�̍��W�����߂�
    top[0] = m_StartSprite.position.y;
    left[0] = m_StartSprite.position.x;
    bottom[0] = m_StartSprite.position.y + m_StartSprite.GetTextureHeight();
    right[0] = m_StartSprite.position.x + m_StartSprite.GetTextureWidth();

    // �`���[�g���A���摜�̒[�̍��W�����߂�
    top[1] = m_TutorialSprite.position.y;
    left[1] = m_TutorialSprite.position.x;
    bottom[1] = m_TutorialSprite.position.y + m_StartSprite.GetTextureHeight();
    right[1] = m_TutorialSprite.position.x + m_StartSprite.GetTextureWidth();

    // �X�^�[�g�摜�̏�ō��N���b�N�ŃQ�[�����C���V�[����
    if ((mpos.x > left[0] && mpos.y > top[0] && mpos.x < right[0] && mpos.y < bottom[0]) && Released(BUTTON_ID::LEFT))
        Change(SCENE_ID::GAMEMAIN);
    // �`���[�g���A���摜�̏�ō��N���b�N�Ń`���[�g���A���V�[����
    else if ((mpos.x > left[1] && mpos.y > top[1] && mpos.x < right[1] && mpos.y < bottom[1]) && Released(BUTTON_ID::LEFT))
        Change(SCENE_ID::TUTORIAL);
}