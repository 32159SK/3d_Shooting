/*
 *  @file       unit.h
 *  @brief      ���j�b�g����
 *  @author     Kazuto Shimazaki
 *  @date       2023/06/23
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../enemy.h"

class CEnemyManager;
class CBossCannon;

class CBossEnemy : public CEnemy
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    CBossEnemy(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual ~CBossEnemy(void) = default;

    /*
     *  @brief      ������
     */
    void    Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)override;
    /*
     *  @brief      �X�V
     */
    void    Update(void)override;

    /*
     *  @brief      �C�̍��W�Z�b�g
     */
    void    SetCannonPosition(float rotate);

    /*
     *  @brief      �C�̃��Z�b�g
     */
    void    ResetCannon(int number) { m_Cannon[number] = nullptr; }

    /*
     *  @brief      �C�̃��Z�b�g
     */
    bool    GetMoveFlag(void) { return m_MoveFlag; }

    /*
     *  @brief      ���݃��C�t�̎擾
     */
    int     GetLife(void)override { return m_PhaseLife[m_Phase]; }

    /*
     *  @brief      �ő僉�C�t�̎擾
     */
    int     GetMaxLife(void)override { return m_PhaseMaxLife[m_Phase]; }
private:
    /*
     *  @brief      �ˌ�
     */
    void            Shot(void)override;

    /*
     *  @brief      �s��
     */
    void            Move(void)override;

    /*
     *  @brief      �_���[�W
     */
    void            Damage(int damage)override;

    /*
     *  @brief      ��
     */
    void            Dead(void)override;

    /*
     *  @brief      ���`��
     */
    void            FirstPhase(void);
    /*
     *  @brief      ���`��
     */
    void            SecondPhase(void);

    /*
     *  @brief      �`�ԕω�
     */
    void            PhaseChange(void);

    /*
     *  @brief      �C�̏���
     */
    void            CannonSetUp(void);

    /*
     *  @brief      �I�[�������W�U��(�˃K�Z�_���Ƃ��̃t�@�Z�l���̃C���[�W)
     */
    void            AllRangeAttack(void);


    enum BOSS_PHASE
    {
        FIRST,
        SECOND,
        DEAD
    };

    static const std::string m_model_file_path; // ���f���t�@�C���p�X

    static const aqua::CVector3 m_base_cannon_pos[8];// �C���{���W

    static const float   m_all_range_ct;        // �I�[�������W�U����CT

    static const float   m_dead_time;           // ���S����

    static const int     m_cannon_count[2];     // �C�̌�

    static const int     m_position_pattern;    // ���W�̊p�x�p�^�[��

    static const int     m_max_summon;          // �ő叢����

    static const float   m_rotate_speed;        // ��]���x

    int             m_PhaseLife[2];             // �`�Ԃ��Ƃ̃��C�t

    int             m_PhaseMaxLife[2];          // �`�Ԃ��Ƃ̍ő僉�C�t

    int             m_SummonCount;              // �����̃J�E���^�[

    bool            m_AllRangeAttacking;        // �I�[�������W�U����

    BOSS_PHASE      m_Phase;                    // ���݂̌`��

    aqua::CVector3  m_CannonPos[8];             // �C����W

    aqua::CTimer    m_AllRangeCT;               // �I�[�������WCT�v���^�C�}�[

    aqua::CTimer    m_DeadTimer;                // ���S�^�C�}�[

    CBossCannon*    m_Cannon[8];                // �C�G�l�~�[�̃|�C���^

    CEnemyManager*  m_EnemyManager;             // �G�Ǘ��N���X(�e�N���X)

    CGameMain*      m_GameMain;                 // �Q�[�����C���V�[���̃|�C���^
};