
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
     *  @class      CCapsulePrimitive
     *
     *  @brief      球形描画クラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CCapsulePrimitive
        : public aqua::core::IDrawObject, public CCollision
    {
    public:
        //! 二点中の一点の位置A
        aqua::CVector3      Apos;
        //! 二点中の一点の位置B
        aqua::CVector3      Bpos;
        //! ポリゴンの細かさ
        int                 div_num;
        //! 半径
        float               radius;
        //! Aを中心とした垂直回転角度
        float               m_VRotate;
        //! Aを中心とした水平回転角度
        float               m_HRotate;
        //! Aを中心とした捻り回転角度
        float               m_TRotate;
        //! 色
        aqua::CColor        color;
        //! 反射光色
        aqua::CColor        spc_color;

        //! 中身を塗りつぶす
        bool                fill;

        /*!
         *  @brief      コンストラクタ
         */
        CCapsulePrimitive(void);

        /*!
         *  @brief      デストラクタ
         */
        ~CCapsulePrimitive(void) = default;

        /*!
         *  @brief      初期化
         *
         *  @param[in]  A_pos       二点中の一点の位置A
         *  @param[in]  B_pos       二点中の一点の位置A
         *  @param[in]  r           半径
         *  @param[in]  divnum      ポリゴンの細かさ
         *  @param[in]  color       色
         *  @param[in]  spc_color   反射光色
         *  @param[in]  fill        塗り潰しフラグ
         */
        void    Setup(const aqua::CVector3& A_pos,const aqua::CVector3& B_pos, float r, int divnum = 10, const aqua::CColor& color_ = aqua::CColor::CYAN, const aqua::CColor& spc_color_ = aqua::CColor::WHITE, bool fill_ = true);

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
