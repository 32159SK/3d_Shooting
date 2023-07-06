/*
 *  @file       unit.h
 *  @brief      ユニット処理
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/20
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../enemy.h"

class CPlayer;

class CMobEnemy : public CEnemy
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     *  @param[in]  object_name     オブジェクト名
     */
    CMobEnemy(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    ~CMobEnemy(void) = default;

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

    void    SetPlayer(CPlayer* player) { m_Player = player; }

private:

    void    Shot(void)override;

    void    Move(void)override;

    /*
     *  @brief      追跡
     */
    void    Follow(void);
    /*
     *  @brief      非追跡
     */
    void    NotFollow(void);

    /*
     *  @brief      追跡確認
     */
    bool    FollowCheck(void);

    static const float   m_follow_range;        // 追跡感知範囲

    static const float   m_lose_sight_time;     // 見失うまでの時間

    bool                 m_Follow;              // 追跡フラグ

    aqua::CVector3       m_Dir;                 // 非追跡時の向き

    aqua::CTimer         m_LoseSightTimer;      // 見失うまでのタイマー
};