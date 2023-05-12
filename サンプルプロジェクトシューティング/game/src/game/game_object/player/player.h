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
    void            Update(void)override;

    /*
     *  @brief      描画
     */
    void            Draw(void) override;

    void            Finalize(void)override;

    /*
     *  @brief      被弾確認
     */
    bool            CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)override;

    /*
     *  @brief      少し前の座標取得
     */
    aqua::CVector3  GetAgoPos(void) { return m_AgoPosition; }

private:

    /*
     *  @brief      射撃
     */
    void            Shot(void)override;

    /*
     *  @brief      移動処理
     */
    void            Move(void)override;

    void            Damage(int damage)override;

    /*
     *  @brief      死亡
     */
    void            Dead(void)override;

    static const float m_chage_shotCT;

    bool            m_Invincible;

    aqua::CLabel    m_DrawBT;

    aqua::CTimer    m_ChageCT;

    aqua::CTimer    m_InvincibleTimer;

    CEnemyManager*  m_EnemyManager;

    aqua::CVector3 m_AgoPosition;
};