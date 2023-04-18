
/*!
 *  @file       game.h
 *  @brief      ゲーム管理
 *  @author     Kazuya Maruyama
 *  @date       2021/02/06
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"

/*!
 *  @class      CGame
 *
 *  @brief      ゲームクラス
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2021/02/06
 *
 *  @version    1.0
 */
class CGame
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親オブジェクト
     */
    CGame( aqua::IGameObject* parent );

    /*!
     *  @brief      デストラクタ
     */
    ~CGame( void ) = default;

    /*!
     *  @brief      初期化
     */
    void        Initialize( void ) override;

    /*!
     *  @brief      描画
     */
    void        Draw( void ) override;

private:
    //! 画面クリアカラー
    static const unsigned int   m_clear_color;
};
