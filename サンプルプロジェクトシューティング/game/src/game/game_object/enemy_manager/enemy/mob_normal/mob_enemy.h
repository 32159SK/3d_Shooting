/*
 *  @file       unit.h
 *  @brief      ���j�b�g����
 *  @author     Kazuto Shimazaki
 *  @date       2022/06/20
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../enemy.h"
 //#include "../../bullet_manager/bullet_manager.h"

class CPlayer;

class CMobEnemy : public CEnemy
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    CMobEnemy(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    ~CMobEnemy(void) = default;

    /*
     *  @brief      ������
     */
    void    Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m, CBulletManager* bm)override;

    /*
     *  @brief      �X�V
     */
    void    Update(void)override;

    void            SetPlayer(CPlayer* player) { m_Player = player; }

private:

    void    Shot(void)override;

    void    Move(void)override;

    /*
     *  @brief      ���S
     */
    void    Dead(void)override;

    /*
     *  @brief      �ǐ�
     */
    void    Follow(void);

    void    NotFollow(void);

    /*
     *  @brief      �ǐՊm�F
     */
    bool    FollowCheck(void);

    static const float   m_follow_range;        // �ǐՊ��m�͈�

    static const float   m_lose_sight_time;     // �������܂ł̎���

    bool                 m_Follow;              // �ǐՃt���O

    aqua::CVector3       m_Dir;                 // ��ǐՎ��̌���

    aqua::CTimer         m_LoseSightTimer;      // �������܂ł̃^�C�}�[
};