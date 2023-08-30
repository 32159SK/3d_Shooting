/*
 *  @file       unit.h
 *  @brief      ���j�b�g����
 *  @author     Kazuto Shimazaki
 *  @date       2025/05/26
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../enemy.h"

class CAlongWallEnemy : public CEnemy
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    CAlongWallEnemy(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual ~CAlongWallEnemy(void) = default;

    /*
     *  @brief      ������
     */
    void    Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)override;

private:

    void            Shot(void)override;

    void            Move(void)override;


    // �ǂƐG��Ă��邩
    bool            m_AlongWall;

    // �ǂ̌���
    enum WALL_DIRE
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    // �G��Ă���ǂ̌���
    WALL_DIRE       m_WallDire;
};