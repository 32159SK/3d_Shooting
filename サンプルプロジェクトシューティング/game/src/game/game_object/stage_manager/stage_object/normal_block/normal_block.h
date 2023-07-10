/*
 *  @file       stage_object.h
 *  @brief      ステージオブジェクト
 *  @author
 *  @date
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "../stage_object.h"

 /*
  *  @class      IStageObject
  *
  *  @brief      ステージオブジェクトクラス
  *
  *  @author     Kazuya Maruyama
  *
  *  @date       2019/11/16
  *
  *  @since      1.0
  */


class CNormalBlock : public IStageObject
{
public:

    /*
     *  @brief      コンストラクタ
     */
    CNormalBlock(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    ~CNormalBlock(void) = default;

    /*!
     *  @brief      初期化
     *
     *  @param[in]  id ステージ上のマップチップID
     */
    void        Initialize(const STAGE_OBJECT_ID& id, int x, int z)override;

    /*
     *  @brief      更新
     */
    void        Update(void)override;

    /*
     *  @brief      描画
     */
    void        Draw(void)override;

    /*
     *  @brief      解放
     */
    void        Finalize(void)override;


    bool        CollisionCheck(aqua::CVector3 position, aqua::CVector3 destination,bool this_bullet)override;



};