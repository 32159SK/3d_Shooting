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

#include"unit_type.h"

class IUnit : public aqua::IGameObject
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     *  @param[in]  object_name     オブジェクト名
     */
    IUnit(aqua::IGameObject* parent, const std::string& object_name);

    /*
     *  @brief      デストラクタ
     */
    virtual ~IUnit(void) = default;

    /*
     *  @brief      初期化
     */
    virtual void    Initialize(void) override;

    /*
     *  @brief      描画
     */
    virtual void    Draw(void)override;

    /*
     *  @brief      更新
     */
    virtual void    Update(void)override;

    /*
     *  @brief      被弾判定
     */
    virtual bool    CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive shot);

protected:

    /*
     *  @brief      射撃
     */
    virtual void    Shot(void);

    /*
     *  @brief      移動処理
     */
    virtual void    Move(void);

    /*
     *  @brief      ダメージ
     */
    void            Damage(void);

     /*
      *  @brief      死亡
      */
    virtual void    Dead(void);

    static const int     m_max_life;     // ライフ上限

    int                  m_Life;         // ライフ

    bool                 m_DeadFlag;     // 死亡フラグ

    float                m_Width;        // 幅

    float                m_Height;       // 高さ

    float                m_Depth;        // 奥行

    UNIT_TYPE            m_UnitType;     // ユニット属性

    aqua::CVector3       m_Position;     // 座標

    aqua::CColor         m_Color;        // 色

    aqua::CCubePrimitive m_Cube;        // 自機
};