#pragma once
/*
 *  @file       title_scene.h
 *  @brief      タイトルシーン
 *  @author     
 *  @date       
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "..\scene.h"

 /*
  *  @class      CResultScene
  *
  *  @brief      タイトルシーンクラス
  *
  *  @version    1.0
  */
class CResultScene
    : public IScene
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親のオブジェクト
     */
    CResultScene(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    ~CResultScene(void) = default;

    /*
     *  @brief      初期化
     */
    void        Initialize(void) override;

    /*
     *  @brief      更新
     */
    void        Update(void) override;

    /*
     *  @brief      描画
     */
    void        Draw(void) override;

    /*
     *  @brief      解放
     */
    void        Finalize(void) override;

    /*
     *  @brief      シーン「操作可能」
     */
    void        Operation(void);


private:
    aqua::CSprite   m_BackgroundSprite;
    aqua::CSprite   m_ResultSprite[2];
};
