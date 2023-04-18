
/*!
 *  @file       point.cpp
 *  @brief      点クラス
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
 *  コンストラクタ
 */
aqua::CPoint::
CPoint( void )
    : x( 0 )
    , y( 0 )
{
}

/*
 *  コンストラクタ
 */
aqua::CPoint::
CPoint( const CPoint& point )
    : x( point.x )
    , y( point.y )
{
}

/*
 *  コンストラクタ
 */
aqua::CPoint::
CPoint( int x, int y )
    : x( x )
    , y( y )
{
}

/*
 *  デバッグログに出力する
 */
void
aqua::CPoint::
DebugLog( void )
{
    AQUA_DEBUG_LOG( "CPoint(x:" + std::to_string( x ) + ", y:" + std::to_string( y ) + ")" );
}
