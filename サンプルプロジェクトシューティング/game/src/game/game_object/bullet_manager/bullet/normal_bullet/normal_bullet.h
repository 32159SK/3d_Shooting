/*
 *  @file       nomal_bullet.h
 *  @brief      通常弾
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
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     */
    CNormalBullet(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    virtual ~CNormalBullet(void) = default;

    /*
     *  @brief      初期化
     */
    void    Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user, CEffectManager* em)override;

};