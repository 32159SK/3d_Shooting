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
    CEnemy(aqua::IGameObject* parent, const std::string& object_name);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual ~CEnemy(void) = default;

    /*
     *  @brief      ������
     */
    virtual void    Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m,CBulletManager* bm);

    /*
     *  @brief      �X�V
     */
    virtual void    Update(void)override;
    /*
     *  @brief      �X�V
     */
    virtual void    Draw(void)override;
    /*
     *  @brief      �X�V
     */
    virtual void    Finalize(void)override;


    void            SetPlayer(CPlayer* player) { m_Player = player; }

protected:

    virtual void    Shot(void)override;

    virtual void    Move(void)override;


    /*
     *  @brief      ���S
     */
    void            Dead(void)override;

    static const aqua::CVector3 m_surroundings[];

    BULLET_TYPE     m_ShotBullet;
    CPlayer*        m_Player;
};