
/*!
 *  @file       rect.cpp
 *  @brief      矩形クラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "rect.h"
#include "..\..\debug\debug.h"
#include <cmath>

const aqua::CRect aqua::CRect::ZERO   = aqua::CRect( 0, 0, 0, 0 );

/*
 *  コンストラクタ
 */
aqua::CRect::
CRect( void )
{
    left = top = right = bottom = 0;
}

/*
 *  コンストラクタ
 */
aqua::CRect::
CRect( const CRect& rect )
{
    left    = rect.left;
    top     = rect.top;
    right   = rect.right;
    bottom  = rect.bottom;
}

/*
 *  コンストラクタ
 */
aqua::CRect::
CRect( int left, int top, int right, int bottom )
{
    this->left    = left;
    this->top     = top;
    this->right   = right;
    this->bottom  = bottom;
}

/*
 *  矩形の幅を取得
 */
int
aqua::CRect::
GetWidth( void ) const
{
    return abs( right - left );
}

/*
 *  矩形の高さを取得
 */
int
aqua::CRect::
GetHeight( void ) const
{
    return abs( bottom - top );
}

/*
 *  デバッグログに出力する
 */
void
aqua::CRect::
DebugLog( void )
{
    AQUA_DEBUG_LOG( "CRect(left:" + std::to_string( left ) + ", right:" + std::to_string( right ) + ", top:" + std::to_string( top ) + ", bottom:" + std::to_string( bottom ) + ")" );
}
