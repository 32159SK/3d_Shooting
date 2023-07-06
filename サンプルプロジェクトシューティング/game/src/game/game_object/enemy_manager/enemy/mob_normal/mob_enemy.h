/*
 *  @file       unit.h
 *  @brief      ���j�b�g����
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/20
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../enemy.h"

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

    void    SetPlayer(CPlayer* player) { m_Player = player; }

private:

    void    Shot(void)override;

    void    Move(void)override;

    /*
     *  @brief      �ǐ�
     */
    void    Follow(void);
    /*
     *  @brief      ��ǐ�
     */
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