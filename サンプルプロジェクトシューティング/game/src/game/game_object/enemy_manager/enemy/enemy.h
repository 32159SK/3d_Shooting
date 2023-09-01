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
#include "../../unit/unit.h"

class CPlayer;

class CEnemy : public IUnit
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     *  @param[in]  object_name     オブジェクト名
     */
    CEnemy(aqua::IGameObject* parent, const std::string& object_name);

    /*
     *  @brief      デストラクタ
     */
    virtual ~CEnemy(void) = default;

    /*
     *  @brief      初期化
     */
    virtual void    Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m,CBulletManager* bm);

    /*
     *  @brief      更新
     */
    virtual void    Update(void)override;

    /*
     *  @brief      描画
     */
    virtual void    Draw(void)override;

    /*
     *  @brief      解放
     */
    virtual void    Finalize(void)override;

    /*
     *  @brief      プレイヤーのセッター
     */
    void            SetPlayer(CPlayer* player) { m_Player = player; }

protected:
    /*
     *  @brief      射撃
     */
    virtual void    Shot(void)override;
    /*
     *  @brief      移動
     */
    virtual void    Move(void)override;


    /*
     *  @brief      死亡
     */
    void            Dead(void)override;

    // 周囲の向き
    static const aqua::CVector3 m_surroundings[];

    CPlayer*        m_Player;       // プレイヤー
};