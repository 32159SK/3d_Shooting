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
//#include "../../bullet_manager/bullet_manager.h"

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
    CEnemy(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    virtual ~CEnemy(void) = default;

    /*
     *  @brief      初期化
     */
    virtual void    Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m,CBulletManager* bm)override;

    /*
     *  @brief      更新
     */
    virtual void    Update(void)override;

    void            SetPlayer(CPlayer* player) { m_Player = player; }

protected:

    virtual void    Shot(void)override;

    virtual void    Move(void)override;

    /*
     *  @brief      死亡
     */
    void            Dead(void)override;

    static const aqua::CVector3 m_surroundings[];

    float           m_Angle;
    CPlayer*        m_Player;
};