/*
 *  @file       penetrate_bullet.h
 *  @brief      貫通弾
 *  @author     Kazuto Shimazaki
 *  @date       2022/06/20
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../bullet.h"


class CPenetrateBullet : public IBullet
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     *  @param[in]  object_name     オブジェクト名
     */
    CPenetrateBullet(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    virtual ~CPenetrateBullet(void) = default;

    /*
     *  @brief      初期化
     *
     *  @param[in]  bullet_info      発射する弾情報
     *  @param[in]  attri            所属
     *  @param[in]  pop_pos          発射座標
     *  @param[in]  dir              向き
     *  @param[in]  user             使用者
     *  @param[in]  em               エフェクト管理クラスのポインタ(撃つ度探査させたら重くなる)
     */
    void    Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user, CEffectManager* em)override;


    /*
     *  @brief      ステージオブジェクトヒット処理
     */
    void    StageObjectHit(aqua::CCubePrimitive::COLL_DIRE c_dire)override { return; }  // オブジェクトをすり抜けるようにするため何もしない
};