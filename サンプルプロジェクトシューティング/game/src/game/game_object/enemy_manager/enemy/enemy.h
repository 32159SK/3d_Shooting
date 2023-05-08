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
#include "../../unit/unit.h"
//#include "../../bullet_manager/bullet_manager.h"

class CPlayer;

class CEnemy : public IUnit
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    CEnemy(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual ~CEnemy(void) = default;

    /*
     *  @brief      ������
     */
    void    Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color,CBulletManager* bm)override;

    /*
     *  @brief      �X�V
     */
    virtual void    Update(void)override;

    void            SetPlayer(CPlayer* player) { m_Player = player; }

private:

    void            Shot(void)override;

    void            Move(void)override;

    /*
     *  @brief      ���S
     */
    void            Dead(void)override;

    float           m_Angle;
    CPlayer*        m_Player;
};