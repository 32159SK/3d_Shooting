/*
 *  @file       beam.h
 *  @brief      ユニット処理
 *  @author     Kazuto Shimazaki
 *  @date       2023/06/26
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once

#include "aqua.h"
#include "../../game_object.h"

class CBeam : public aqua::IGameObject
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     */
    CBeam(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    ~CBeam(void) = default;

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
     *  @brief      当たり判定用のカプセル取得
     */
    aqua::CCapsulePrimitive GetCapsule(void) { return m_Capsule; }


    /*
     *  @brief      属性取得
     */
    UNIT_TYPE       GetAttri(void) { return m_Attri; }

    /*
     *  @brief      ダメージ取得
     */
    int             GetDamage(void) { return m_Damage; }

    /*
     *  @brief      ダメージフラグの取得
     */
    bool            GetDamageFlag(void) { return m_DamageFlag; }

    /*
     *  @brief      終了フラグの取得
     */
    bool            GetFinishFlag(void) { return m_Finished; }

private:
    /*
     *  @brief      チャージ
     */
    void            Charge(void);

    /*
     *  @brief      発射
     */
    void            Firing(void);

    /*
     *  @brief      消滅
     */
    void            Destroy(void);

    /*
     *  @brief      ビームの状態
     */
    enum class BEAM_STATE
    {
        CHARGE, // 収束
        FIRING, // 発射
        DESTROY // 消滅
    };

    static const float      m_max_range;    // 射程距離

    static const float      m_charge_time;  // 収束時間

    int                     m_Damage;       // ダメージ量

    float                   m_Rotate;       //! 水平回転角度

    float                   m_Radius;       //! 半径

    bool                    m_DamageFlag;   // ダメージ判定

    bool                    m_Finished;     // 終了

    aqua::CVector3          m_Dir;          // 方向

    aqua::CVector3          m_StartPos;     // 始点

    aqua::CVector3          m_EndPos;       // 終点

    UNIT_TYPE               m_Attri;        // 属性

    BEAM_STATE              m_BeamState;    // 現在のビームの状態

    aqua::CCapsulePrimitive m_Capsule;      // 当たり判定用のカプセルクラス

    aqua::CLinePrimitive3D  m_PredictionLine;// 予測線

    aqua::CTimer            m_Timer;        // タイマー
    
    aqua::CEffect3D*        m_Effect;       // エフェクトのポインタ容器

    CEffectManager*         m_EffectManager;// エフェクト管理クラスのポインタ容器

    IUnit*                  m_User;         // 使用者
};