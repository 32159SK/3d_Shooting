/*
 *  @file       nomal_bullet.h
 *  @brief      �ʏ�e
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/21
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../bullet.h"


class CNormalBullet : public IBullet
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     */
    CNormalBullet(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual ~CNormalBullet(void) = default;

    /*
     *  @brief      ������
     */
    void    Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user, CEffectManager* em)override;

};