
/*!
 *  @file       graphic_filter.h
 *  @brief      グラフィックフィルター
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
     *  @brief      グラフィックフィルターID定義
     */
    enum class GRAPHIC_FILTER
    {
        //! フィルターなし
        NONE         = -1,
        //MONO         = DX_GRAPH_FILTER_MONO,         //! モノトーンフィルタ
        //! ガウスフィルタ
        GAUSS        = DX_GRAPH_FILTER_GAUSS,
        //DOWN_SCALE   = DX_GRAPH_FILTER_DOWN_SCALE,   //! 縮小フィルタ
        //BRIGHT_CLIP  = DX_GRAPH_FILTER_BRIGHT_CLIP,  //! 明るさクリップフィルタ
        //BRIGHT_SCALE = DX_GRAPH_FILTER_BRIGHT_SCALE, //! 指定の明るさ領域を拡大するフィルタ
        //HSB          = DX_GRAPH_FILTER_HSB,          //! 色相・彩度・明度フィルタ
        //INVERT       = DX_GRAPH_FILTER_INVERT,       //! 階調の反転フィルタ
        //LEVEL        = DX_GRAPH_FILTER_LEVEL,        //! レベル補正フィルタ
        //TWO_COLOR    = DX_GRAPH_FILTER_TWO_COLOR,    //! ２階調化フィルタ
        //GRADIENT_MAP = DX_GRAPH_FILTER_GRADIENT_MAP, //! グラデーションマップフィルタ
   };
}
