
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
#include"../../scene/game_main/game_main.h"

class CFloor;
class CPlayer;
class CEnemyManager;

/*
 *  @class      CTutorial
 *
 *  @brief      tutorial�V�[��
 */
class CTutorial
    : public CGameMain
{
public:
    /*
     *  @brief      �R���X�g���N�^
     */
    CTutorial(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    ~CTutorial(void) = default;

    /*
     *  @brief      ������
     */
    void            Initialize(void)override;

    /*
     *  @brief      �X�V
     */
    void            Update(void)override;

    /*
     *  @brief      �`��
     */
    void            Draw(void)override;

    /*
     *  @brief      ���
     */
    void            Finalize(void)override;

    /*
     *  @brief      �J�����擾(�O������J�����Ɋ����邽�߂̃Q�b�^�[)
     */
    aqua::CCamera* GetCamera(void) { return &m_Camera; }


private:
    /*
     *  @brief      �`���[�g���A���J�n
     */
    void            TutorialStart(void);

    /*
     *  @brief      �`���[�g���A����
     */
    void            TutorialPlay(void);

    /*
     *  @brief      �`���[�g���A���I��
     */
    void            TutorialFinish(void);

    /*
     *  @brief      �ړ��`���[�g���A��
     */
    void            TutorialMove(void);

    /*
     *  @brief      �}�E�X�`���[�g���A��
     */
    void            TutorialMouse(void);

    /*
     *  @brief      ���b�N�I���`���[�g���A��
     */
    void            TutorialLockOn(void);

    /*
     *  @brief      �ˌ��`���[�g���A��
     */
    void            TutorialShot(void);

    /*
     *  @brief      �r�[���`���[�g���A��
     */
    void            TutorialBeam(void);

    /*!
     *  @brief      �`���[�g���A���e�L�X�g�ǂݍ���
     */
    void            TextDataLoad(void);

    /*!
     *  @brief      �`���[�g���A�����b�Z�[�W�Z�b�g�A�b�v
     */
    bool            MessageSetUp(void);

    // ���
    enum class STATE
    {
        START,      // �J�n
        PLAY,       // �v���C
        END         // �I��
    };

    // �`���[�g���A���i�K
    enum class TUTORIAL_PHASE
    {
        MOVE,       // �ړ�
        MOUSE,      // �}�E�X����
        SHOT,       // �ˌ�
        LOCKON,     // ���b�N�I��
        BEAM        // �r�[��
    };

    static const int            m_max_text_count;       // �`���[�g���A���e�L�X�g�̑���
    static const int            m_lock_on_text_num;     // ���b�N�I���e�L�X�g�̔ԍ�
    static const float          m_tutorial_move_length; // �`���[�g���A�����ړ�����
    static const float          m_mouse_move_time;      // �}�E�X�̑��쎞��
    static const float          m_shot_time;            // �ˌ����쎞��
    static const std::string    m_tutorial_path;        // �`���[�g���A���e�L�X�g�f�[�^�̃p�X

    int                         m_TextDrawCount;        // �e�L�X�g�̕`��񐔃J�E���g
    float                       m_MoveLength;           // �ړ�����
    bool                        m_EnemyPop;             // �G�o���m�F�t���O
    bool                        m_ShotFlag;             // �ˌ�����m�F
    bool                        m_NotBeamFiring;        // �r�[���Ǝ˒��m�F�t���O

    STATE                       m_State;                // ���
    TUTORIAL_PHASE              m_Phase;                // �i�K
    aqua::CVector3              m_PlayerPos;            // �v���C���[���W
    aqua::CPoint                m_MousePos;             // �}�E�X���W
    aqua::CTimer                m_TutorialTimer;        // �`���[�g���A���m�F�p�^�C�}�[
    std::vector<std::string>    m_TutorialText;         // �`���[�g���A���e�L�X�g�̃��X�g

    CEnemy* m_TutorialEnemy;                            // �`���[�g���A���p�G
    CTutorialMessage*           m_TutorialMessage;      // �`���[�g���A���e�L�X�g�`��N���X
};
