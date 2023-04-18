
/*!
 *  @file       mouse.cpp
 *  @brief      �}�E�X���͊Ǘ�
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
 *  ������
 */
aqua::core::CMouse&
aqua::core::CMouse::
GetInstance( void )
{
    static CMouse instance;

    return instance;
}

/*
 *  ������
 */
void
aqua::core::CMouse::
Initialize( void )
{
    m_MouseState        = 0;
    m_PrevMouseState    = 0;
}

/*
 *  �X�V
 */
void
aqua::core::CMouse::
Update( void )
{
    // �O�̃t���[���̓��͏�Ԃ�ۑ�
    m_PrevMouseState = m_MouseState;

    m_PrevCursorPos = m_CursorPos;

    // �}�E�X�̓��͏��擾
    m_MouseState = GetMouseInput( );

    m_CursorPos = GetCursorPos( );
}

/*
 *  �{�^������
 */
bool
aqua::core::CMouse::
Button( aqua::mouse::BUTTON_ID key )
{
    return ( m_MouseState & static_cast<int>(key) );
}

/*
 *  �g���K�[����
 */
bool
aqua::core::CMouse::
Trigger( aqua::mouse::BUTTON_ID key )
{
    return ( m_MouseState & static_cast<int>(key)) && !( m_PrevMouseState & static_cast<int>(key));
}

/*
 *  �����[�X����
 */
bool
aqua::core::CMouse::
Released( aqua::mouse::BUTTON_ID key )
{
    return !( m_MouseState & static_cast<int>(key)) && ( m_PrevMouseState & static_cast<int>(key));
}

/*
 *  �}�E�X�J�[�\���̈ʒu�擾
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
 *  �}�E�X�J�[�\���̈ړ��ʎ擾
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
 *  �}�E�X�z�C�[���l�擾
 */
int
aqua::core::CMouse::
GetWheel( void )
{
    return GetMouseWheelRotVol( );
}

/*
 *  �R���X�g���N�^
 */
aqua::core::CMouse::
CMouse( void )
    : m_MouseState( 0 )
    , m_PrevMouseState( 0 )
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
aqua::core::CMouse::
CMouse( const aqua::core::CMouse& rhs )
    : m_MouseState(0)
    , m_PrevMouseState(0)
{
    (void)rhs;
}

/*
 *  ������Z�q
 */
aqua::core::CMouse&
aqua::core::CMouse::
operator=( const CMouse& rhs )
{
    (void)rhs;

    return *this;
}
