
/*!
 *  @file       line_primitive_3d.cpp
 *  @brief      3D線分描画クラス
 *  @author     Toshihito Ohashi
 *  @date       2022/03/29
 *  @version    7.17
 *
 *  Copyright (c) 2021-2022, Toshihto Ohahsi. All rights reserved.
 */

#include "3d_line_primitive.h"
#include "..\..\..\debug\debug.h"

 /*
  *  コンストラクタ
  */
aqua::CLinePrimitive3D::
CLinePrimitive3D(void)
    : pointA(CVector3::ZERO)
    , pointB(CVector3::ZERO)
    , color(aqua::CColor::WHITE)
    , blend_mode(aqua::ALPHABLEND::ALPHA)
{
}

/*
 *  初期化
 */
void
aqua::CLinePrimitive3D::
Setup(const aqua::CVector3& pointA_, const aqua::CVector3& pointB_, const aqua::CColor& color_, aqua::ALPHABLEND blend_mode_)
{
    pointA = pointA_;
    pointB = pointB_;
    color = color_;
    blend_mode = blend_mode_;
}

/*
 *  描画
 */
void
aqua::CLinePrimitive3D::
Draw(void)
{
    // 非表示の時は描画しない
    if (!visible) return;

    // アルファブレンド設定
    SetDrawBlendMode((int)blend_mode, color.alpha);

    // 描画
    DrawLine3D(pointA, pointB, color.GetColor());

    // アルファブレンドモードをデフォルトに戻す
    SetDrawBlendMode((int)aqua::ALPHABLEND::ALPHA, aqua::CColor::MAX_COLOR);
}

bool aqua::CLinePrimitive3D::CheckCollision(CVector3& pointA, CVector3& pointB)
{
    return false;
}
