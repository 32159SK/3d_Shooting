
/*!
 *  @file       vector2.cpp
 *  @brief      �񎟌��x�N�g��
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "vector2.h"
#include "..\..\..\debug\debug.h"
#include <cmath>

const aqua::CVector2 aqua::CVector2::ZERO = aqua::CVector2( 0.0f, 0.0f );
const aqua::CVector2 aqua::CVector2::ONE  = aqua::CVector2( 1.0f, 1.0f );

/*
 *  �R���X�g���N�^
 */
aqua::CVector2::
CVector2( void )
    : x( 0.0f ), y( 0.0f )
{
}

/*
 *  �R���X�g���N�^
 */
aqua::CVector2::
CVector2( float x, float y )
    : x( x ), y( y )
{
}

/*
 *  �R���X�g���N�^
 */
aqua::CVector2::
CVector2( const aqua::CVector2& v )
    : x( v.x ), y( v.y )
{
}

/*
 *  ���K��
 */
aqua::CVector2
aqua::CVector2::
Normalize( void )
{
    return Normalize( *this );
}

/*
 *  ���K��
 */
aqua::CVector2
aqua::CVector2::
Normalize( const CVector2& v )
{
    aqua::CVector2 t = v;

    float inv = 1.0f / t.Length( );

    t.x *= inv;
    t.y *= inv;

    return t;
}

/*
 *  �x�N�g���̑傫���擾
 */
float
aqua::CVector2::
Length( void )
{
    return Length( *this );
}

/*
 *  �x�N�g���̑傫���擾
 */
float
aqua::CVector2::
Length( const CVector2& v )
{
    return sqrtf( v.x * v.x + v.y * v.y );
}

/*
 *  ����
 */
float
aqua::CVector2::
Dot( const CVector2& vA, const CVector2& vB )
{
    return ( vA.x * vB.x + vA.y * vB.y );
}

/*
 *  �O��
 */
float
aqua::CVector2::
Cross( const CVector2& vA, const CVector2& vB )
{
    return ( vA.x * vB.y ) - ( vA.y * vB.x );
}

/*
 *  �f�o�b�O���O�ɏo�͂���
 */
void
aqua::CVector2::
DebugLog( void )
{
    AQUA_DEBUG_LOG( "CVector2(x:" + std::to_string( x ) + ", y:" + std::to_string( y ) + ")" );
}
