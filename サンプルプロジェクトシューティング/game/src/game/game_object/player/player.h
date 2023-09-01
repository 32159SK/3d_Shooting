/*
 *  @file       unit.h
 *  @brief      ユニット処理
 *  @author     Kazuto Shimazaki
 *  @date       2023/05/20
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../unit/unit.h"

class CEnemyManager;
class CEnemy;
class CLockOnMarker;

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
    void            Initialize(aqua::CVector3 pop_pos, CStageManager* st_m, CBulletManager* bm);

    /*
     *  @brief      更新
     */
    void            Update(void)override;

    /*
     *  @brief      描画
     */
    void            Draw(void) override;

    /*
     *  @brief      解放
     */
    void            Finalize(void)override;

    /*
     *  @brief      被弾確認
     */
    bool            CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)override;

    /*
     *  @brief      被弾確認
     */
    bool            CheckHitBeam(UNIT_TYPE type, aqua::CCapsulePrimitive capsule, int damage)override;

    /*
     *  @brief      少し前の座標取得
     */
    aqua::CVector3  GetAgoPos(void) { return m_AgoPosition; }


    /*
     *  @brief      敵管理クラスセッター
     */
    void            SetEnemyManager(CEnemyManager* em) { m_EnemyManager = em; }

    /*
     *  @brief      座標のセッター
     */
    void            SetPosition(aqua::CVector3 pos) { m_Position = pos; }

    /*
     *  @brief      回復
     */
    void            LifeHeal(int heal_value);
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

    /*
     *  @brief      操作
     */
    void            Operation(void);

    /*
     *  @brief      マウス追従による回転
     */
    void            MouseTrack(void);

    /*
     *  @brief      ロックオン
     */
    void            LockOn(void);

    static const float m_change_shotCT;  // 弾種切り替え間隔

    static const float m_shot_ct;       // 射撃間隔
    
    static const float m_ago_pos_time;  // 座標を取る間隔

    static const float m_invincible_time;// 無敵時間

    static const float m_flash_time;// 点滅切り替え時間

    static const float m_lock_range;    // ロックオン範囲

    static const float m_width;         // 幅定数

    static const float m_height;        // 高さ定数

    static const float m_depth;         // 奥行定数

    static const float m_speed;         // 移動速度定数


    static const float m_font_size;     // フォントサイズ

    static const int   m_max_life;      // ライフの最大値

    bool            m_Invincible;       // 無敵

    aqua::CVector3  m_AgoPosition;      // 追尾座標

    aqua::CSprite   m_BulletIcon[4];    // 弾種アイコン

    aqua::CTimer    m_ChangeCT;         // 弾種切り替えタイマー

    aqua::CTimer    m_AgoPosTimer;      // 追尾座標を取る間隔用のタイマー

    aqua::CTimer    m_InvincibleTimer;  // 無敵時間タイマー

    aqua::CTimer    m_LockonTimer;      // 連続でm_LockONが切り替わるのを防止

    aqua::CTimer    m_FlashTimer;       // フラッシュタイマー

    CFloor*         m_Floor;            // 床のポインタ

    CEnemyManager*  m_EnemyManager;     // 敵管理クラス

    CEnemy*         m_LockOnEnemy;      // ロックオン中の敵

    CLockOnMarker*  m_LockOnMarker;     // ロックオンマーカークラスのポインタ
};