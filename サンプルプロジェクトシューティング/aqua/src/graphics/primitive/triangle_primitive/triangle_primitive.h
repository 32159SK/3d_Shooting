
/*!
 *  @file       triangle_primitive.h
 *  @brief      三角形描画クラス
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
     *  @class      CTrianglePrimitive
     *
     *  @brief      三角形描画クラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CTrianglePrimitive
        : public aqua::core::IDrawObject
    {
    public:
        //! 位置A
        aqua::CVector2      pointA;
        //! 位置B
        aqua::CVector2      pointB;
        //! 位置C
        aqua::CVector2      pointC;
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
        CTrianglePrimitive( void );

        /*!
         *  @brief      デストラクタ
         */
        ~CTrianglePrimitive( void ) = default;

        /*!
         *  @brief      初期化
         *
         *  @param[in]  pointA          位置A
         *  @param[in]  pointB          位置B
         *  @param[in]  pointC          位置C
         *  @param[in]  color           色
         *  @param[in]  thickness       縁の太さ
         *  @param[in]  blend_mode      アルファブレンド
         */
        void    Setup(const aqua::CVector2& pointA_, const aqua::CVector2& pointB_, const aqua::CVector2& pointC_, const aqua::CColor& color_ = 0xffffffff, bool fill_ = true, float thickness_ = 1.0f, aqua::ALPHABLEND blend_mode_ = aqua::ALPHABLEND::ALPHA);

        /*!
         *  @brief      描画
         */
        void    Draw( void );
    };
}
