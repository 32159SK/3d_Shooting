
/*!
 *  @file       mathematics.h
 *  @brief      ���w
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
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @brief      �~����
     */
    static const float PI = 3.141592653589793f;

    /*!
     *  @brief      �p�x�����W�A���ɕϊ�
     *
     *  @param[in]  degree  �p�x
     */
    float       DegToRad( float degree );

    /*!
     *  @brief      ���W�A�����p�x�ɕϊ�
     *
     *  @param[in]  radian  ���W�A��
     */
    float       RadToDeg( float radian );

    /*!
     *  @brief      ���������߂�(���̐���)
     *
     *  @param[in]  max     �ő�l
     *  @param[in]  min     �ŏ��l
     *
     *  @return     �ŏ��l����ő�l�܂ł͈̔͂ŋ��߂�ꂽ�����l
     */
    int         Rand(int max, int min = 0 );
}
