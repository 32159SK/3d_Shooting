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

class CBeam : public aqua::IGameObject
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     *  @param[in]  object_name     オブジェクト名
     */
    CBeam(aqua::IGameObject* parent, const std::string& object_name);

    /*
     *  @brief      デストラクタ
     */
    virtual ~CBeam(void) = default;

    /*
     *  @brief      初期化
     */
    void            Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 dir, IUnit* user, CEffectManager* em);

    /*
     *  @brief      描画
     */
    void            Draw(void)override;

    /*
     *  @brief      更新
     */
    void            Update(void)override;

    /*
     *  @brief      更新
     */
    void            Finalize(void)override;


    /*
     *  @brief      属性取得
     */
    UNIT_TYPE       GetAttri(void) { return m_Attri; }

    /*
     *  @brief      ダメージ取得
     */
    int             GetDamage(void) { return m_Damage; }

private:
    void            Destroy(void);

    static const float      m_max_range;    // 射程距離

    int                     m_Damage;       // ダメージ量

    float                   m_Rotate;       //! 水平回転角度

    float                   m_Radius;       //! 半径

    aqua::CVector3          m_Dir;

    aqua::CVector3          m_StartPos;

    aqua::CVector3          m_EndPos;

    UNIT_TYPE               m_Attri;        // 属性

    aqua::CCapsulePrimitive m_Cupsule;      // 

    CEffectManager*         m_EffectManager;

    IUnit*                  m_Unit;
};