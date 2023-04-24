
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
     *  @class      CCubePrimitive3D
     *
     *  @brief      線分描画クラス
     *
     *  @author     Kazuto Shimazaki
     *
     *  @date       2023/04/14
     *
     *  @version    7.17
     */
    class CCubePrimitive
        : public aqua::core::IDrawObject, public CCollision
    {
    public:
        //! 中心座標
        aqua::CVector3      position;
        //! 幅
        float               width;
        //! 高さ
        float               height;
        //! 奥行
        float               depth;
        //! 垂直回転角度
        float           m_VRotate;
        //! 水平回転角度
        float           m_HRotate;
        //! 捻り回転角度
        float           m_TRotate;

        //! 色
        aqua::CColor        color;
        //! 反射光色
        aqua::CColor        spc_color;
        //! 塗り潰し
        bool                fill;
        //! 頂点座標情報
        tagVERTEX3D         vertex[8];


        /*!
         *  @brief      コンストラクタ
         */
        CCubePrimitive(void);

        /*!
         *  @brief      デストラクタ
         */
        ~CCubePrimitive(void) = default;
       
        /*!
         *  @brief      初期化
         *
         *  @param[in]  center_pos      中心座標
         *  @param[in]  width_          幅
         *  @param[in]  height_         高さ
         *  @param[in]  depth           奥行
         *  @param[in]  color_          色
         *  @param[in]  spc_color_      反射光色
         *  @param[in]  fill_           塗り潰し
         */
        void    Setup(const aqua::CVector3& center_pos, float width_, float height_, float depth, const aqua::CColor& color_ = 0xffffffff, const aqua::CColor& spc_color_ = 0xffffffff, bool fill_ = true);

        /*!
         *  @brief      変形
         */
        void    Transform(void);

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

        /*!
         *  @brief      衝突判定
         *  @param[in]  center_pos      球の中心
         *  @param[in]  r               半径
         */
        bool    CheckCollision(CVector3& center_pos, float r)override;

    private:
        WORD                index[36];
        static const int    polygon_count;
        static const int    vertex_count;
        static const int    index_count;

    };
}
