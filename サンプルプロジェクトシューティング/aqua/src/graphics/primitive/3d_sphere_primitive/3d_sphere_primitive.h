
/*!
 *  @file       3d_sphere_primitive.h
 *  @brief      球形描画クラス
 *  @author     Kazuya Maruyama
 *  @date       2023/04/13
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>
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
     *  @class      CSpherePrimitive
     *
     *  @brief      球形描画クラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CSpherePrimitive
        : public aqua::core::IDrawObject, public CCollision
    {
    public:
        //! 位置
        aqua::CVector3      position;
        //! ポリゴンの細かさ
        int                 div_num;
        //! 半径
        float               radius;
        //! 色
        aqua::CColor        color;
        //! 反射光色
        aqua::CColor        spc_color;

        //! 中身を塗りつぶす
        bool                fill;

        /*!
         *  @brief      コンストラクタ
         */
        CSpherePrimitive(void);

        /*!
         *  @brief      デストラクタ
         */
        ~CSpherePrimitive(void) = default;

        /*!
         *  @brief      初期化
         *
         *  @param[in]  position    中心座標
         *  @param[in]  r           半径
         *  @param[in]  divnum      ポリゴンの細かさ
         *  @param[in]  color       色
         *  @param[in]  spc_color   反射光色
         *  @param[in]  fill        塗り潰しフラグ
         */
        void    Setup(const aqua::CVector3& position_, float r, int divnum , const aqua::CColor& color_, const aqua::CColor& spc_color_, bool fill_ = true);

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
