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
#include "../enemy.h"

class CAlongWallEnemy : public CEnemy
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     *  @param[in]  object_name     オブジェクト名
     */
    CAlongWallEnemy(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    virtual ~CAlongWallEnemy(void) = default;

    /*
     *  @brief      初期化
     */
    void    Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m, CBulletManager* bm)override;

    /*
     *  @brief      更新
     */
    virtual void    Update(void)override;


private:

    void            Shot(void)override;

    void            Move(void)override;


    // 壁と触れているか
    bool            m_AlongWall;

    // 壁の向き
    enum WALL_DIRE
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    // 触れている壁の向き
    WALL_DIRE       m_WallDire;
};