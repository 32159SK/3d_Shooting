
/*!
 *  @file       mathematics.h
 *  @brief      数学
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <cmath>
#include "vector\vector.h"
#include "matrix/matrix.h"
#include "collision/collision.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @brief      円周率
     */
    static const float PI = 3.141592653589793f;

    /*!
     *  @brief      角度をラジアンに変換
     *
     *  @param[in]  degree  角度
     */
    float       DegToRad( float degree );

    /*!
     *  @brief      ラジアンを角度に変換
     *
     *  @param[in]  radian  ラジアン
     */
    float       RadToDeg( float radian );

    /*!
     *  @brief      乱数を求める(正の整数)
     *
     *  @param[in]  max     最大値
     *  @param[in]  min     最小値
     *
     *  @return     最小値から最大値までの範囲で求められた乱数値
     */
    int         Rand(int max, int min = 0 );
}
