#pragma once
/*
 *  @file       title_scene.h
 *  @brief      タイトルシーン
 *  @author     Miyu Hujita
 *  @date       2021/07/01
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "..\scene.h"
#include "../../../game_object.h"

 /*
  *  @class      CTitleScene
  *
  *  @brief      タイトルシーンクラス
  *
  *  @version    1.0
  */
class CTitleScene
    : public IScene
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親のオブジェクト
     */
    CTitleScene(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    ~CTitleScene(void) = default;

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
    aqua::CSprite       m_BackgroundSprite;     //! 背景用スプライト
    aqua::CSprite       m_TitleSprite;          //! タイトル用スプライト
    aqua::CSprite       m_StartSprite;          //! タイトル用スプライト
    //aqua::CLabel        m_LicenseLabel;

    /*
     *  @brief      操作時の文字の規定位置
     *  @param[in]  [0] = タイトルスプライト
     *  @param[in]  [1] = 「スタート」のボタン
     */
    static const        aqua::CVector2 m_basis_position[2];

    aqua::CSprite       m_Sprite;  // スプライト

    CSoundManager*      m_SoundManager;
};
