
/*!
 *  @file       alphablend.h
 *  @brief      アルファブレンド
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @brief      アルファブレンドID定義
     */
    enum class ALPHABLEND
    {
        //! ブレンドなし
        NOBELEND    = DX_BLENDMODE_NOBLEND,
        //! 半透明
        ALPHA       = DX_BLENDMODE_ALPHA,
        //! 加算合成
        ADD         = DX_BLENDMODE_ADD,
        //! 減算合成
        SUB         = DX_BLENDMODE_SUB,
        //! 反転合成
        INVSRC      = DX_BLENDMODE_INVSRC,
    };
}
