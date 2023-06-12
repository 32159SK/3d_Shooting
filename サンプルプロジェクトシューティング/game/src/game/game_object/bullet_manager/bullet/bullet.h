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
#include "../../game_object.h"
#include "../../unit/unit.h"

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
    virtual void    Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri,aqua::CVector3 pop_pos,aqua::CVector3 front,IUnit* user);

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

    /*
     *  @brief      弾の座標取得
     */
    aqua::CVector3  GetPosition(void) { return m_Position; }

    /*
     *  @brief      弾の進行座標取得
     */
    aqua::CVector3  GetDestination(void) { return m_Position + m_Velocity * 1.5f; }

    /*
     *  @brief      ヒット処理
     */
    void            Hit(void);


    /*
     *  @brief      ステージオブジェクトヒット処理
     */
    virtual void    StageObjectHit(aqua::CCubePrimitive::COLL_DIRE c_dire);


protected:


    int                     m_Damage;       // ダメージ量

    float                   m_Radius;       // 半径

    float                   m_Range;        // 射程距離

        //! 水平回転角度
    float                   m_Rotate;

    aqua::CVector3          m_Dir;

    aqua::CVector3          m_Velocity;     // 弾の速度

    aqua::CVector3          m_StartPos;

    float                   m_Speed;        // 弾の速さ

    UNIT_TYPE               m_Attri;        // 属性

    aqua::CVector3          m_Position;     // 座標

    aqua::CColor            m_Color;        // 色

    aqua::CSpherePrimitive  m_Sphere;       // 

    IUnit*                  m_Unit;
};