/*
 *  @file       unit.h
 *  @brief      ユニット処理
 *  @author     Kazuto Shimazaki
 *  @date       2022/06/20
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../unit/unit.h"

class CEnemyManager;

class CPlayer : public IUnit
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     *  @param[in]  object_name     オブジェクト名
     */
    CPlayer(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    virtual         ~CPlayer(void) = default;

    /*
     *  @brief      初期化
     */
    void            Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color,CBulletManager* bm)override;

    /*
     *  @brief      更新
     */
    virtual void    Update(void)override;

    void Draw(void) override;

    /*
     *  @brief      更新
     */
    bool            CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)override;

private:

    /*
     *  @brief      射撃
     */
    void            Shot(void)override;

    /*
     *  @brief      移動処理
     */
    void            Move(void)override;

    /*
     *  @brief      死亡
     */
    void            Dead(void)override;

    CEnemyManager*  m_EnemyManager;
};