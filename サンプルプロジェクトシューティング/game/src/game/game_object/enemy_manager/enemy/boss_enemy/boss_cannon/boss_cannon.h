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
    void    SetPosition(aqua::CVector3 pos) { m_Position = pos; }

    /*
     *  @brief      弾種設定
     */
    void    SetBulletType(BULLET_TYPE bullet_type) { m_ShotBullet = bullet_type; }

private:

    void            Move(void)override;

    aqua::CModel    m_Model;

    CBossEnemy*     m_BossEnemy;
};