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
    void    Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m, CBulletManager* bm)override;

    /*
     *  @brief      �X�V
     */
    virtual void    Update(void)override;


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