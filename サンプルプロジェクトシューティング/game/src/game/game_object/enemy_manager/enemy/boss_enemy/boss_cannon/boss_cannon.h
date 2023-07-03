/*
 *  @file       unit.h
 *  @brief      ���j�b�g����
 *  @author     Kazuto Shimazaki
 *  @date       2023/06/20
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../../enemy.h"

class CBossEnemy;

class CBossCannon : public CEnemy
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    CBossCannon(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual ~CBossCannon(void) = default;

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
     *  @brief      ���W�ݒ�
     */
    void    SetPosition(aqua::CVector3 pos);

    /*
     *  @brief      �e��ݒ�
     */
    void    SetBulletType(BULLET_TYPE bullet_type) { m_ShotBullet = bullet_type; }

    /*
     *  @brief      �I�[�������W�U���̐ݒ�
     */
    void    SetAllRange(void);

    /*
     *  @brief      �ˌ�
     */
    void    Shot(void)override;

    /*
     *  @brief      �I���t���O�擾
     */
    bool    GetFinish(void) { return m_AllRangeFinish; }
private:

    void    Move(void)override;

    void    EasingMove(void);

    void    AllRangeAttack(void);

    void    ReturnPosition(void);

    static const float m_move_time;

    static const float m_player_distance;

    static const int   m_position_pattern;

    enum ALLRANGE_STATE
    {


    };

    float           m_ShotAngle;

    bool            m_AllRangeAttacking;        // �I�[�������W�U����

    bool            m_ReturnFlag;               // ���̏ꏊ�ɖ߂邩�̃t���O

    bool            m_AllRangeFinish;           // �I�[�������W�U���̏I��

    aqua::CVector3  m_StartPos;

    aqua::CVector3  m_EndPos;

    aqua::CModel    m_Model;

    aqua::CTimer    m_MoveTimer;

    CBossEnemy*     m_BossEnemy;
};