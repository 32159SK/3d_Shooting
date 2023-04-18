
/*!
 *  @file       circle_primitive.h
 *  @brief      円描画クラス
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
     *  @class      CCirclePrimitive
     *
     *  @brief      円描画クラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CCirclePrimitive
        : public aqua::core::IDrawObject
    {
    public:
        //! 中心座標
        aqua::CVector2      center;
        //! 半径
        float               radius;
        //! 円を形成する頂点数
        int                 vertex_count;
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
        CCirclePrimitive( void );

        /*!
         *  @brief      デストラクタ
         */
        ~CCirclePrimitive( void ) = default;

        /*!
         *  @brief      初期化
         *
         *  @param[in]  center          位置(左上)
         *  @param[in]  radius          幅
         *  @param[in]  vertex_count    高さ
         *  @param[in]  color           色
         *  @param[in]  fill            塗りつぶしフラグ
         *  @param[in]  thickness       縁の太さ
         *  @param[in]  blend_mode      アルファブレンド
         */
        void    Setup(const aqua::CVector2& center_, float radius_ = 1.0f, int vertex_count_ = 36, const aqua::CColor& color_ = 0xffffffff, bool fill_ = true, float thickness_ = 1.0f, aqua::ALPHABLEND blend_mode_ = aqua::ALPHABLEND::ALPHA);

        /*!
         *  @brief      描画
         */
        void    Draw( void );
    };
}
