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
    void            Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m,CBulletManager* bm)override;

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

    /*
     *  @brief      時止め確認
     */
    bool            GetTimeStop(void) { return m_TimeStop; }

    /*
     *  @brief      敵管理クラスセッター
     */
    void            SetEnemyManager(CEnemyManager* em) { m_EnemyManager = em; }

    bool            GetLockOnFlag(void) { return m_LockON; }

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
     *  @brief      死亡処理
     */
    void            Damage(int damage)override;

    /*
     *  @brief      死亡
     */
    void            Dead(void)override;

    /*
     *  @brief      ロックオン
     */
    void            LockOn(void);

    /*
     *  @brief      ザ・ワールド
     */
    void            TheWorld(void);

    static const float m_chage_shotCT;  // 
    static const float m_ago_pos_time;  // 
    static const float m_the_world_time;// 時を止めていられる時間
    static const float m_the_world_CT;  // 再び時を止められるまでの時間
    static const float m_lock_range;

    bool            m_Invincible;       // 無敵

    bool            m_TimeStop;         // 時止め確認

    bool            m_LockON;           // ロックオン確認

    aqua::CVector3  m_AgoPosition;       //

    aqua::CModel    m_Model;            // 自機のモデル

    aqua::CLabel    m_DrawBT;           // 

    aqua::CTimer    m_ChageCT;          //

    aqua::CTimer    m_AgoPosTimer;      // 

    aqua::CTimer    m_InvincibleTimer;  //

    aqua::CTimer    m_TheWorldTimer;    // 

    aqua::CTimer    m_LockonTimer;      // 連続でm_LockONが切り替わるのを防止

    CEnemyManager*  m_EnemyManager;     //

    CEnemy*         m_Enemy;

    CLockOnMarker*  m_LockOnMarker;
};