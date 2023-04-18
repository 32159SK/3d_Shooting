
/*!
 *  @file       line_primitive_3d.h
 *  @brief      3D線分描画クラス
 *  @author     Toshihito Ohashi
 *  @date       2022/03/29
 *  @version    7.17
 *
 *  Copyright (c) 2021-2022, Toshihito Ohahsi. All rights reserved.
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
     *  @class      CLinePrimitive3D
     *
     *  @brief      線分描画クラス
     *
     *  @author     Toshihito Ohashi
     *
     *  @date       2022/03/29
     *
     *  @version    7.17
     */
    class CLinePrimitive3D
        : public aqua::core::IDrawObject, public CCollision
    {
    public:
        //! 位置A
        aqua::CVector3      pointA;
        //! 位置B
        aqua::CVector3      pointB;
        //! 色
        aqua::CColor        color;
        //! アルファブレンドモード
        aqua::ALPHABLEND    blend_mode;

        /*!
         *  @brief      コンストラクタ
         */
        CLinePrimitive3D(void);

        /*!
         *  @brief      デストラクタ
         */
        ~CLinePrimitive3D(void) = default;

        /*!
         *  @brief      初期化
         *
         *  @param[in]  pointA          位置A
         *  @param[in]  pointB          位置B
         *  @param[in]  color           色
         *  @param[in]  thickness       縁の太さ
         *  @param[in]  blend_mode      アルファブレンド
         */
        void    Setup(const aqua::CVector3& pointA_, const aqua::CVector3& pointB_, const aqua::CColor& color_ = 0xffffffff, aqua::ALPHABLEND blend_mode_ = aqua::ALPHABLEND::ALPHA);

        /*!
         *  @brief      描画
         */
        void    Draw(void);

        /*!
         *  @brief      衝突判定
         *  @param[in]  pointA          始点
         *  @param[in]  pointB          終点
         */
        bool    CheckCollision(CVector3& pointA, CVector3& pointB)override;
    };
}
