
/*
 *  @file       game_main.h
 *  @brief      �Q�[�����C���V�[��
 *  @author
 *  @date
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include"..\scene.h"


 /*
  *  @class      CGameMain
  *
  *  @brief      �Q�[�����C���V�[��
  */
class CGameMain
    : public IScene
{
public:
    /*
     *  @brief      �R���X�g���N�^
     */
    CGameMain(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    ~CGameMain(void);

    /*
     *  @brief      ������
     */
    void            Initialize(void);

    /*
     *  @brief      �X�V
     */
    void            Update(void);

    /*
     *  @brief      �`��
     */
    void            Draw(void);

    /*
     *  @brief      ���
     */
    void            Finalize(void);

    /*
     *  @brief      �J�����擾(�O������J�����Ɋ����邽�߂̃Q�b�^�[)
     */
    aqua::CCamera*  GetCamera(void) { return &m_Camera; }

    void            SetGameClear(bool game_clear) { m_GameClear = game_clear; }

    bool            GetGameClear(void) { return m_GameClear; }

private:
    /*
     *  @brief      �Q�[���J�n
     */
    void            GameStart(void);

    /*
     *  @brief      �Q�[����
     */
    void            GamePlay(void);

    /*
     *  @brief      �Q�[���I��
     */
    void            GameFinish(void);

    /*
     *  @brief      �Q�[���I��
     */
    void            WhiteOut(void);

    /*
     *  @brief      ���ID
     */
    enum STATE
    {
        STATE_GAME_START,       //! �Q�[���J�n
        STATE_GAME_PLAY,        //! �Q�[����
        STATE_GAME_FINISH,      //! �Q�[���I��
        STATE_GAME_SAVE,        //! �X�R�A�̃Z�[�u
    };

    static const float  m_white_out_time;

    bool                m_GameClear;    // �Q�[���N���A�t���O

    STATE               m_State;        //! ���ID
    aqua::CCamera       m_Camera;
    aqua::CTimer        m_WhiteOutTimer;      // �z���C�g�A�E�g�p�^�C�}�[
    CPlayer*            m_Player;
    CEnemyManager*      m_EnemyManager;
    aqua::CSprite       m_WhiteOutSprite;// �z���C�g�A�E�g�p�X�v���C�g
};
