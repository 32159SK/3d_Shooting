
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

class CFloor;
class CPlayer;
class CEnemyManager;

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
    ~CGameMain(void) = default;

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

    /*
     *  @brief      �Q�[���N���A�Z�b�^�[
     */
    void            SetGameClear(bool game_clear) { m_GameClear = game_clear; }

protected:
    /*
     *  @brief      ���ID
     */
    enum STATE
    {
        STATE_GAME_START,       //! �Q�[���J�n
        STATE_GAME_PLAY,        //! �Q�[����
        STATE_GAME_FINISH,      //! �Q�[���I��
    };

    static const float  m_camera_distace;       // �J�����̋���
    static const float  m_camera_v_rotate;      // �J�����̐�����]

    STATE               m_State;                // ���ID
    aqua::CCamera       m_Camera;               // �J����
    CFloor*             m_Floor;                // ��
    CPlayer*            m_Player;               // �v���C���[
    CEnemyManager*      m_EnemyManager;         // �G�Ǘ��N���X
    CSoundManager*      m_SoundManager;         // �T�E���h�Ǘ��N���X
private:
    /*
     *  @brief      �Q�[����
     */
    void            GamePlay(void);

    /*
     *  @brief      �Q�[���I��
     */
    void            GameFinish(void);

    /*
     *  @brief      �z���C�g�A�E�g
     */
    void            WhiteOut(void);

    static const float  m_white_out_time;       // �z���C�g�A�E�g�ɂ����鎞��

    bool                m_GameClear;            // �Q�[���N���A�t���O
    aqua::CTimer        m_WhiteOutTimer;        // �z���C�g�A�E�g�p�^�C�}�[
    aqua::CSprite       m_WhiteOutSprite;       // �z���C�g�A�E�g�p�X�v���C�g
};
