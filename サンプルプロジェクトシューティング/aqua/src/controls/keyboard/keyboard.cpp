
/*!
 *  @file       keyboard.cpp
 *  @brief      キーボード入力管理
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "keyboard.h"
#include "..\..\debug\debug.h"
#include "..\..\utility\memory\memory.h"

const unsigned int  aqua::core::CKeyboard::m_max_input_key = 256;

/*
 *  初期化
 */
aqua::core::CKeyboard&
aqua::core::CKeyboard::
GetInstance( void )
{
    static CKeyboard instance;

    return instance;
}

/*
 *  初期化
 */
void
aqua::core::CKeyboard::
Initialize( void )
{
    // キーステート生成
    if( !m_KeyState )
        m_KeyState = AQUA_NEW char[m_max_input_key];

    ZeroMemory( m_KeyState, m_max_input_key );

    // 前のキーステート生成
    if( !m_PrevKeyState )
        m_PrevKeyState = AQUA_NEW char[m_max_input_key];

    ZeroMemory( m_PrevKeyState, m_max_input_key );
}

/*
 *  更新
 */
void
aqua::core::CKeyboard::
Update( void )
{
    // 前のフレームのキー状態を保存
    memcpy( m_PrevKeyState, m_KeyState, m_max_input_key );

    // 入力状態の取得
    GetHitKeyStateAll( m_KeyState );
}

/*
 *  解放
 */
void
aqua::core::CKeyboard::
Finalize( void )
{
    AQUA_SAFE_DELETE_ARRAY( m_PrevKeyState );
    AQUA_SAFE_DELETE_ARRAY( m_KeyState );
}

/*
 *  ボタン判定
 */
bool
aqua::core::CKeyboard::
Button( aqua::keyboard::KEY_ID key )
{
    return m_KeyState[static_cast<int>(key)];
}

/*
 *  トリガー判定
 */
bool
aqua::core::CKeyboard::
Trigger( aqua::keyboard::KEY_ID key )
{
    return ( m_KeyState[static_cast<int>(key)] && !m_PrevKeyState[static_cast<int>(key)] );
}

/*
 *  リリース判定
 */
bool
aqua::core::CKeyboard::
Released( aqua::keyboard::KEY_ID key )
{
    return ( !m_KeyState[static_cast<int>(key)] && m_PrevKeyState[static_cast<int>(key)] );
}

/*
 *  コンストラクタ
 */
aqua::core::CKeyboard::
CKeyboard( void )
    : m_KeyState( nullptr )
    , m_PrevKeyState( nullptr )
{
}

/*
 *  コピーコンストラクタ
 */
aqua::core::CKeyboard::
CKeyboard( const aqua::core::CKeyboard& rhs )
    : m_KeyState(nullptr)
    , m_PrevKeyState(nullptr)
{
    (void)rhs;
}

/*
 *  代入演算子
 */
aqua::core::CKeyboard&
aqua::core::CKeyboard::
operator=( const CKeyboard& rhs )
{
    (void)rhs;

    return *this;
}
