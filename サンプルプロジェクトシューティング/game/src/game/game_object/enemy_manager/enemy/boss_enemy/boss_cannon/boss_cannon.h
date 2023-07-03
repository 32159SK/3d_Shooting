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
     *  @brief      描画
     */
    void    Draw(void)override;

    /*
     *  @brief      解放
     */
    void    Finalize(void)override;

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
    void    SetAllRange(void);

    /*
     *  @brief      射撃
     */
    void    Shot(void)override;

    /*
     *  @brief      終了フラグ取得
     */
    bool    GetFinish(void) { return m_AllRangeFinish; }
private:

    void    Move(void)override;

    void    EasingMove(void);

    void    AllRangeAttack(void);

    void    ReturnPosition(void);

    static const float m_move_time;

    static const float m_player_distance;

    static const int   m_position_pattern;

    enum ALLRANGE_STATE
    {


    };

    float           m_ShotAngle;

    bool            m_AllRangeAttacking;        // オールレンジ攻撃中

    bool            m_ReturnFlag;               // 元の場所に戻るかのフラグ

    bool            m_AllRangeFinish;           // オールレンジ攻撃の終了

    aqua::CVector3  m_StartPos;

    aqua::CVector3  m_EndPos;

    aqua::CModel    m_Model;

    aqua::CTimer    m_MoveTimer;

    CBossEnemy*     m_BossEnemy;
};