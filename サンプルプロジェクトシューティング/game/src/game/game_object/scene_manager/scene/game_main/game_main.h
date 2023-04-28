
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
    void        Initialize(void);

    /*
     *  @brief      �X�V
     */
    void        Update(void);

    /*
     *  @brief      �`��
     */
    void        Draw(void);

    /*
     *  @brief      ���
     */
    void        Finalize(void);



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
     *  @brief      ���ID
     */
    enum STATE
    {
        STATE_GAME_START,       //! �Q�[���J�n
        STATE_GAME_PLAY,        //! �Q�[����
        STATE_GAME_FINISH,      //! �Q�[���I��
        STATE_GAME_SAVE,        //! �X�R�A�̃Z�[�u
    };

    STATE               m_State;        //! ���ID
    aqua::CCamera       m_Camera;
    CPlayer*            m_Player;
    aqua::CSprite       m_Sprite;
};
