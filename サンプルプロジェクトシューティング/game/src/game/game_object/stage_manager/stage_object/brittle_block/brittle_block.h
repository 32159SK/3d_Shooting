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
#include "../normal_block/normal_block.h"

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


class CBrittleBlock : public IStageObject
{
public:

    /*
     *  @brief      コンストラクタ
     */
    CBrittleBlock(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    ~CBrittleBlock(void) = default;

    /*!
     *  @brief      初期化
     *
     *  @param[in]  id ステージ上のマップチップID
     */
    void        Initialize(const STAGE_OBJECT_ID& id, int x, int z)override;

    /*
     *  @brief      判定確認
     */
    bool        CollisionCheck(aqua::CVector3 position, aqua::CVector3 destination,bool this_bullet)override;


private:
    /*
     *  @brief      破損
     */
    void        Broken(void);

    int             m_Endurance;        // 耐久値

    CEffectManager* m_EfectManager;     // エフェクト管理クラス
    CSoundManager*  m_SoundManager;     // サウンド管理クラス
};