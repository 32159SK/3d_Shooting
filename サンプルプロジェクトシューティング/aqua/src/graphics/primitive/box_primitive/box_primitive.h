
/*!
 *  @file       box_primitive.h
 *  @brief      矩形描画クラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>
#include "..\..\alphablend\alphablend.h"
#include "..\..\draw_object\draw_object.h"
#include "..\..\..\mathematics\mathematics.h"
#include "..\..\color\color.h"
#include "..\..\..\utility\utility.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CBoxPrimitive
     *
     *  @brief      矩形描画クラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CBoxPrimitive
        : public aqua::core::IDrawObject
    {
    public:
        //! 位置
        aqua::CVector2      position;
        //! 幅
        float               width;
        //! 高さ
        float               height;
        //! 色
        aqua::CColor        color;
        //! 中身を塗りつぶす
        bool                fill;
        //! 太さ
        float               thickness;
        //! アルファブレンドモード
        aqua::ALPHABLEND    blend_mode;

        /*!
         *  @brief      コンストラクタ
         */
        CBoxPrimitive( void );

        /*!
         *  @brief      デストラクタ
         */
        ~CBoxPrimitive( void ) = default;

        /*!
         *  @brief      初期化
         *
         *  @param[in]  position    位置(左上)
         *  @param[in]  width       幅
         *  @param[in]  height      高さ
         *  @param[in]  color       色
         *  @param[in]  fill        塗りつぶしフラグ
         *  @param[in]  thickness   縁の太さ
         *  @param[in]  blend_mode  アルファブレンド
         */
        void    Setup(const aqua::CVector2& position_, float width_ = 1.0f, float height_ = 1.0f, const aqua::CColor& color_ = 0xffffffff, bool fill_ = true, float thickness_ = 1.0f, aqua::ALPHABLEND blend_mode_ = aqua::ALPHABLEND::ALPHA);

        /*!
         *  @brief      描画
         */
        void    Draw( void );
    };
}
