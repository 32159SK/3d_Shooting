
/*!
 *  @file       mouse.cpp
 *  @brief      マウス入力管理
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "mouse.h"
#include "..\..\debug\debug.h"
#include "..\..\utility\memory\memory.h"

/*
 *  初期化
 */
aqua::core::CMouse&
aqua::core::CMouse::
GetInstance( void )
{
    static CMouse instance;

    return instance;
}

/*
 *  初期化
 */
void
aqua::core::CMouse::
Initialize( void )
{
    m_MouseState        = 0;
    m_PrevMouseState    = 0;
}

/*
 *  更新
 */
void
aqua::core::CMouse::
Update( void )
{
    // 前のフレームの入力状態を保存
    m_PrevMouseState = m_MouseState;

    m_PrevCursorPos = m_CursorPos;

    // マウスの入力情報取得
    m_MouseState = GetMouseInput( );

    m_CursorPos = GetCursorPos( );
}

/*
 *  ボタン判定
 */
bool
aqua::core::CMouse::
Button( aqua::mouse::BUTTON_ID key )
{
    return ( m_MouseState & static_cast<int>(key) );
}

/*
 *  トリガー判定
 */
bool
aqua::core::CMouse::
Trigger( aqua::mouse::BUTTON_ID key )
{
    return ( m_MouseState & static_cast<int>(key)) && !( m_PrevMouseState & static_cast<int>(key));
}

/*
 *  リリース判定
 */
bool
aqua::core::CMouse::
Released( aqua::mouse::BUTTON_ID key )
{
    return !( m_MouseState & static_cast<int>(key)) && ( m_PrevMouseState & static_cast<int>(key));
}

/*
 *  マウスカーソルの位置取得
 */
aqua::CPoint
aqua::core::CMouse::
GetCursorPos( void )
{
    CPoint t;

    GetMousePoint( &t.x, &t.y );

    return t;
}

/*
 *  マウスカーソルの移動量取得
 */
aqua::CPoint
aqua::core::CMouse::
GetCursorMovement( void )
{
    CPoint t = GetCursorPos( );

    t.x = m_CursorPos.x - m_PrevCursorPos.x;
    t.y = m_CursorPos.y - m_PrevCursorPos.y;

    return t;
}

/*
 *  マウスホイール値取得
 */
int
aqua::core::CMouse::
GetWheel( void )
{
    return GetMouseWheelRotVol( );
}

/*
 *  コンストラクタ
 */
aqua::core::CMouse::
CMouse( void )
    : m_MouseState( 0 )
    , m_PrevMouseState( 0 )
{
}

/*
 *  コピーコンストラクタ
 */
aqua::core::CMouse::
CMouse( const aqua::core::CMouse& rhs )
    : m_MouseState(0)
    , m_PrevMouseState(0)
{
    (void)rhs;
}

/*
 *  代入演算子
 */
aqua::core::CMouse&
aqua::core::CMouse::
operator=( const CMouse& rhs )
{
    (void)rhs;

    return *this;
}
