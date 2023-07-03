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
     *  @brief      �`��
     */
    void    Draw(void)override;

    /*
     *  @brief      ���
     */
    void    Finalize(void)override;


    /*
     *  @brief      ��e����
     */
    bool    CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)override;

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
     *  @brief      �G������
     */
    void            SummonEnemy(void);

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

    static const aqua::CVector3 m_base_cannon_pos[4];// �C���{���W

    static const float   m_summon_interval;     // �����Ԋu

    static const float   m_all_range_ct;        // 

    static const int     m_cannon_count[2];        // 

    int             m_PhaseLife[3];             // 

    bool            m_AllRangeAttacking;        // �I�[�������W�U����

    BOSS_PHASE      m_Phase;                    // ���݂̌`��

    aqua::CModel    m_Model;                    // ���f��

    aqua::CVector3  m_CannonPos[4];             // �C����W

    aqua::CTimer    m_SummonTimer;              // �����^�C�}�[

    aqua::CTimer    m_AllRangeCT;            // 

    aqua::CEffect3D* m_Effect;                  // �G�t�F�N�g

    CBossCannon*    m_Cannon[4];                // 

    CEnemyManager*  m_EnemyManager;             // �G�Ǘ��N���X(�e�N���X)

};