/*
 *  @file       unit.h
 *  @brief      ユニット処理
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/14
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "unit_type.h"
#include "../bullet_manager/bullet/bullet_info.h"

class CBulletManager;
class IBullet;

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
    virtual void    Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, CStageManager* st_m, CBulletManager* bm);

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
    virtual bool    CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage);

    /*
     *  @brief      ビーム被弾判定
     */
    virtual bool    CheckHitBeam(UNIT_TYPE type, aqua::CCapsulePrimitive capsule, int damage);

    aqua::CVector3  GetPosition(void) { return m_Position; }

    bool            GetDead(void);

    /*
     *  @brief      平面座標の取得
     */
    aqua::CVector2  GetPosVector2(void) { return aqua::CVector2(m_Position.x, m_Position.z); }

    /*
     *  @brief      回転値の取得
     */
    float           GetRotate(void) { return m_Rotate; }
    /*
     *  @brief      最大ライフの取得
     */
    int             GetMaxLife(void) { return m_MaxLife; }
    /*
     *  @brief      現在ライフの取得
     */
    int             GetLife(void) { return m_Life; }

    /*
     *  @brief      ロックオンフラグの取得
     */
    bool            GetLockOnFlag(void) { return m_LockON; }

    /*
     *  @brief      行動可能フラグのセッター
     */
    virtual void    SetMoveFlag(bool flag) { m_MoveFlag = flag; }


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
    virtual void    Damage(int damage);

     /*
      *  @brief      死亡
      */
    virtual void    Dead(void);

    static const float   m_beam_damage_interval;

    int                  m_MaxLife;

    int                  m_Life;         // ライフ

    bool                 m_DeadFlag;     // 死亡フラグ

    bool                 m_MoveFlag;     // 行動可能フラグ

    bool                 m_LockON;       // ロックオンフラグ

    float                m_Width;        // 幅

    float                m_Height;       // 高さ

    float                m_Depth;        // 奥行

    float                m_Angle;

    float                m_Rotate;       //! 水平回転角度

    UNIT_TYPE            m_UnitType;     // ユニット属性

    BULLET_TYPE          m_ShotBullet;

    aqua::CVector3       m_Position;     // 座標

    aqua::CVector3       m_Velocity;     // 移動速度
    
    float                m_Speed;        // 速さ

    aqua::CColor         m_Color;        // 色

    aqua::CCubePrimitive m_Cube;         // ユニットのコライダー

    aqua::CTimer         m_ShotCT;

    aqua::CTimer         m_BeamInterval;

    CEffectManager*      m_EffectManager;

    CBulletManager*      m_BulletManager;

    CStageManager*       m_StageManager;
};