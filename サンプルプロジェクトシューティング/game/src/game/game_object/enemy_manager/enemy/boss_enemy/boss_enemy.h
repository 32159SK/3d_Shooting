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
     *  @brief      描画
     */
    void    Draw(void)override;

    /*
     *  @brief      解放
     */
    void    Finalize(void)override;


    /*
     *  @brief      被弾判定
     */
    bool    CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)override;

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
     *  @brief      雑魚召喚
     */
    void            SummonEnemy(void);

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

    static const aqua::CVector3 m_base_cannon_pos[4];// 砲門基本座標

    static const float   m_summon_interval;     // 召喚間隔

    static const float   m_all_range_ct;        // 

    static const int     m_cannon_count[2];        // 

    int             m_PhaseLife[3];             // 

    bool            m_AllRangeAttacking;        // オールレンジ攻撃中

    BOSS_PHASE      m_Phase;                    // 現在の形態

    aqua::CModel    m_Model;                    // モデル

    aqua::CVector3  m_CannonPos[4];             // 砲門座標

    aqua::CTimer    m_SummonTimer;              // 召喚タイマー

    aqua::CTimer    m_AllRangeCT;            // 

    aqua::CEffect3D* m_Effect;                  // エフェクト

    CBossCannon*    m_Cannon[4];                // 

    CEnemyManager*  m_EnemyManager;             // 敵管理クラス(親クラス)

};