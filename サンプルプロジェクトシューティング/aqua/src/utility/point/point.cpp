
/*!
 *  @file       point.cpp
 *  @brief      �_�N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "point.h"
#include "..\..\debug\debug.h"

const aqua::CPoint aqua::CPoint::ZERO   = aqua::CPoint( 0, 0 );

/*
 *  �R���X�g���N�^
 */
aqua::CPoint::
CPoint( void )
    : x( 0 )
    , y( 0 )
{
}

/*
 *  �R���X�g���N�^
 */
aqua::CPoint::
CPoint( const CPoint& point )
    : x( point.x )
    , y( point.y )
{
}

/*
 *  �R���X�g���N�^
 */
aqua::CPoint::
CPoint( int x, int y )
    : x( x )
    , y( y )
{
}

/*
 *  �f�o�b�O���O�ɏo�͂���
 */
void
aqua::CPoint::
DebugLog( void )
{
    AQUA_DEBUG_LOG( "CPoint(x:" + std::to_string( x ) + ", y:" + std::to_string( y ) + ")" );
}
