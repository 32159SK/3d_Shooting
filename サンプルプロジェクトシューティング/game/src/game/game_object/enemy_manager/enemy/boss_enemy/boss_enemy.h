/*
 *  @file       unit.h
 *  @brief      ユニット処理
 *  @author     Kazuto Shimazaki
 *  @date       2023/06/23
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../enemy.h"

class CEnemyManager;
class CBossCannon;

class CBossEnemy : public CEnemy
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     *  @param[in]  object_name     オブジェクト名
     */
    CBossEnemy(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    virtual ~CBossEnemy(void) = default;

    /*
     *  @brief      初期化
     */
    void    Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)override;
    /*
     *  @brief      更新
     */
    void    Update(void)override;

    /*
     *  @brief      砲の座標セット
     */
    void    SetCannonPosition(float rotate);

    /*
     *  @brief      砲のリセット
     */
    void    ResetCannon(int number) { m_Cannon[number] = nullptr; }

    /*
     *  @brief      砲のリセット
     */
    bool    GetMoveFlag(void) { return m_MoveFlag; }

    /*
     *  @brief      現在ライフの取得
     */
    int     GetLife(void)override { return m_PhaseLife[m_Phase]; }

    /*
     *  @brief      最大ライフの取得
     */
    int     GetMaxLife(void)override { return m_PhaseMaxLife[m_Phase]; }
private:
    /*
     *  @brief      射撃
     */
    void            Shot(void)override;

    /*
     *  @brief      行動
     */
    void            Move(void)override;

    /*
     *  @brief      ダメージ
     */
    void            Damage(int damage)override;

    /*
     *  @brief      死
     */
    void            Dead(void)override;

    /*
     *  @brief      第一形態
     */
    void            FirstPhase(void);
    /*
     *  @brief      第二形態
     */
    void            SecondPhase(void);

    /*
     *  @brief      形態変化
     */
    void            PhaseChange(void);

    /*
     *  @brief      砲の準備
     */
    void            CannonSetUp(void);

    /*
     *  @brief      オールレンジ攻撃(νガ〇ダムとかのファ〇ネルのイメージ)
     */
    void            AllRangeAttack(void);


    enum BOSS_PHASE
    {
        FIRST,
        SECOND,
        DEAD
    };

    static const std::string m_model_file_path; // モデルファイルパス

    static const aqua::CVector3 m_base_cannon_pos[8];// 砲門基本座標

    static const float   m_all_range_ct;        // オールレンジ攻撃のCT

    static const float   m_dead_time;           // 死亡時間

    static const int     m_cannon_count[2];     // 砲の個数

    static const int     m_position_pattern;    // 座標の角度パターン

    static const int     m_max_summon;          // 最大召喚数

    static const float   m_rotate_speed;        // 回転速度

    int             m_PhaseLife[2];             // 形態ごとのライフ

    int             m_PhaseMaxLife[2];          // 形態ごとの最大ライフ

    int             m_SummonCount;              // 召喚のカウンター

    bool            m_AllRangeAttacking;        // オールレンジ攻撃中

    BOSS_PHASE      m_Phase;                    // 現在の形態

    aqua::CVector3  m_CannonPos[8];             // 砲門座標

    aqua::CTimer    m_AllRangeCT;               // オールレンジCT計測タイマー

    aqua::CTimer    m_DeadTimer;                // 死亡タイマー

    CBossCannon*    m_Cannon[8];                // 砲エネミーのポインタ

    CEnemyManager*  m_EnemyManager;             // 敵管理クラス(親クラス)

    CGameMain*      m_GameMain;                 // ゲームメインシーンのポインタ
};