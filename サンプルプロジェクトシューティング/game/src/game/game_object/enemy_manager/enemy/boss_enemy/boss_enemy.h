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
    void    Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m, CBulletManager* bm)override;

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
     *  @brief      �G������
     */
    void            SummonEnemy(void);


    enum BOSS_PHASE
    {
        FIRST,
        SECOND,
        DEAD
    };

    int             m_PhaseLife[3];

    static const std::string m_model_file_path;

    static const float   m_summon_interval;     // �����Ԋu

    BOSS_PHASE      m_Phase;                    // 

    float           m_FortRotate[3];            // �C��p�x

    aqua::CModel    m_Model;                    // ���f��

    aqua::CVector3  m_FortPos[3];               // �C����W

    aqua::CTimer    m_SummonTimer;              // �����^�C�}�[

    aqua::CTimer    m_DeadTimer;                // �����^�C�}�[

    CEnemyManager*  m_EnemyManager;             // �G�Ǘ��N���X(�e�N���X)
};