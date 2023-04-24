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
#include "../../unit/unit.h"
#include "bullet_type.h"

class IBullet : public aqua::IGameObject
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     *  @param[in]  object_name     オブジェクト名
     */
    IBullet(aqua::IGameObject* parent, const std::string& object_name);

    /*
     *  @brief      デストラクタ
     */
    virtual ~IBullet(void) = default;

    /*
     *  @brief      初期化
     */
    void    Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri,aqua::CVector3 pop_pos,aqua::CVector3 front,IUnit* user);

    /*
     *  @brief      描画
     */
    virtual void    Draw(void)override;

    /*
     *  @brief      更新
     */
    virtual void    Update(void)override;


    /*
     *  @brief      属性取得
     */
    UNIT_TYPE       GetAttri(void) { return m_Attri; }

    /*
     *  @brief      ダメージ取得
     */
    int             GetDamage(void) { return m_Damage; }

    /*
     *  @brief      弾の球取得
     */
    aqua::CSpherePrimitive GetSphere(void) { return m_Sphere; }

    aqua::CVector3  GetPosition(void) { return m_Position; }

    void            Hit(void);

protected:

    int                     m_Damage;       // ダメージ量

    float                   m_Radius;       // 半径

    aqua::CVector3          m_Dir;

    aqua::CVector3          m_Velocity;     // 弾の速度

    float                   m_Speed;        // 弾の速さ

    UNIT_TYPE               m_Attri;        // 属性

    aqua::CVector3          m_Position;     // 座標

    aqua::CColor            m_Color;        // 色

    aqua::CSpherePrimitive  m_Sphere;       // 

    IUnit*                  m_Unit;
};