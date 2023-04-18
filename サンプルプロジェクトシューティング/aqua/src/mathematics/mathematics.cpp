
/*!
 *  @file       mathematics.cpp
 *  @brief      AQUA Game Library
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "mathematics.h"

/*
 *  �p�x�����W�A���ɕϊ�
 */
float
aqua::
DegToRad( float degree )
{
    return ( degree * aqua::PI / 180.0f );
}

/*
 *  ���W�A�����p�x�ɕϊ�
 */
float
aqua::
RadToDeg( float radian )
{
    return ( radian * 180.0f / aqua::PI );
}

/*
 *  ���������߂�
 */
int
aqua::
Rand( int max, int min )
{
    return ( rand( ) % ( ( max + 1 ) - min ) ) + min;
}
