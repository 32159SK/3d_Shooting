/*
 *  @file       unit.h
 *  @brief      ユニット処理
 *  @author     Kazuto Shimazaki
 *  @date       2023/06/20
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../../enemy.h"
#include "../../../../bullet_manager/beam/beam.h"

class CBossEnemy;

class CBossCannon : public CEnemy
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     *  @param[in]  object_name     オブジェクト名
     */
    CBossCannon(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    virtual ~CBossCannon(void) = default;

    /*
     *  @brief      初期化
     */
    void    Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)override;
    /*
     *  @brief      更新
     */
    void    Update(void)override;

    /*
     *  @brief      座標設定
     */
    void    SetPosition(aqua::CVector3 pos);

    /*
     *  @brief      弾種設定
     */
    void    SetBulletType(BULLET_TYPE bullet_type) { m_ShotBullet = bullet_type; }

    /*
     *  @brief      オールレンジ攻撃の設定
     */
    void    SetAllRange(float angle);

    /*
     *  @brief      射撃
     */
    void    Shot(void)override;

    /*
     *  @brief      番号のセッター
     */
    void    SetCannonNumber(int number) { m_CannonNumber = number; }

    /*
     *  @brief      ボスのポインタのセッター
     */
    void    SetBossEnemy(CBossEnemy* boss) { m_BossEnemy = boss; }

    /*
     *  @brief      終了フラグ取得
     */
    bool    GetFinish(void) { return m_AllRangeFinish; }

    /*
     *  @brief      死亡
     */
    void    Dead(void)override;
private:
    /*
     *  @brief      行動処理
     */
    void    Move(void)override;

    /*
     *  @brief      基本の動き
     */
    void    Default(void);

    /*
     *  @brief      イージングでの移動
     */
    void    EasingMove(void);

    /*
     *  @brief      攻撃座標への移動
     */
    void    AllRangeMove(void);

    /*
     *  @brief      ビームの照射
     */
    void    Irradiation(void);

    /*
     *  @brief      基本座標へ戻る
     */
    void    ReturnPosition(void);


    static const float m_move_time;             // 移動にかける時間

    static const float m_player_distance;       // プレイヤーとの距離

    static const int   m_position_pattern;      // 座標の角度パターン

    // オールレンジ攻撃の状態
    enum ALLRANGE_STATE
    {
        DEFAULT,    // 基本
        MOVE,       // 移動(攻撃座標へ向かう)
        IRRADIATION,// 照射
        RETURN      // 戻る
    };

    int             m_CannonNumber;             // 砲の管理番号

    float           m_ShotAngle;                // 射撃(オールレンジ)時の角度

    bool            m_AllRangeAttacking;        // オールレンジ攻撃中

    bool            m_ReturnFlag;               // 元の場所に戻るかのフラグ

    bool            m_AllRangeFinish;           // オールレンジ攻撃の終了

    ALLRANGE_STATE  m_AllRangeState;            // オールレンジ攻撃の状態

    aqua::CVector3  m_StartPos;

    aqua::CVector3  m_EndPos;

    aqua::CTimer    m_MoveTimer;

    CBossEnemy*     m_BossEnemy;

    CBeam*          m_Beam;

    CLockOnMarker*  m_LockOnMarker;
};