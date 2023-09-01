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
#include "../../../../bullet_manager/beam/beam.h"

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
    void    SetAllRange(float angle);

    /*
     *  @brief      �ˌ�
     */
    void    Shot(void)override;

    /*
     *  @brief      �ԍ��̃Z�b�^�[
     */
    void    SetCannonNumber(int number) { m_CannonNumber = number; }

    /*
     *  @brief      �{�X�̃|�C���^�̃Z�b�^�[
     */
    void    SetBossEnemy(CBossEnemy* boss) { m_BossEnemy = boss; }

    /*
     *  @brief      �I���t���O�擾
     */
    bool    GetFinish(void) { return m_AllRangeFinish; }

    /*
     *  @brief      ���S
     */
    void    Dead(void)override;
private:
    /*
     *  @brief      �s������
     */
    void    Move(void)override;

    /*
     *  @brief      ��{�̓���
     */
    void    Default(void);

    /*
     *  @brief      �C�[�W���O�ł̈ړ�
     */
    void    EasingMove(void);

    /*
     *  @brief      �U�����W�ւ̈ړ�
     */
    void    AllRangeMove(void);

    /*
     *  @brief      �r�[���̏Ǝ�
     */
    void    Irradiation(void);

    /*
     *  @brief      ��{���W�֖߂�
     */
    void    ReturnPosition(void);


    static const float m_move_time;             // �ړ��ɂ����鎞��

    static const float m_player_distance;       // �v���C���[�Ƃ̋���

    static const int   m_position_pattern;      // ���W�̊p�x�p�^�[��

    // �I�[�������W�U���̏��
    enum ALLRANGE_STATE
    {
        DEFAULT,    // ��{
        MOVE,       // �ړ�(�U�����W�֌�����)
        IRRADIATION,// �Ǝ�
        RETURN      // �߂�
    };

    int             m_CannonNumber;             // �C�̊Ǘ��ԍ�

    float           m_ShotAngle;                // �ˌ�(�I�[�������W)���̊p�x

    bool            m_AllRangeAttacking;        // �I�[�������W�U����

    bool            m_ReturnFlag;               // ���̏ꏊ�ɖ߂邩�̃t���O

    bool            m_AllRangeFinish;           // �I�[�������W�U���̏I��

    ALLRANGE_STATE  m_AllRangeState;            // �I�[�������W�U���̏��

    aqua::CVector3  m_StartPos;

    aqua::CVector3  m_EndPos;

    aqua::CTimer    m_MoveTimer;

    CBossEnemy*     m_BossEnemy;

    CBeam*          m_Beam;

    CLockOnMarker*  m_LockOnMarker;
};