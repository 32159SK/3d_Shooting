
/*!
 *  @file       keyboard.cpp
 *  @brief      �L�[�{�[�h���͊Ǘ�
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
 *  ������
 */
aqua::core::CKeyboard&
aqua::core::CKeyboard::
GetInstance( void )
{
    static CKeyboard instance;

    return instance;
}

/*
 *  ������
 */
void
aqua::core::CKeyboard::
Initialize( void )
{
    // �L�[�X�e�[�g����
    if( !m_KeyState )
        m_KeyState = AQUA_NEW char[m_max_input_key];

    ZeroMemory( m_KeyState, m_max_input_key );

    // �O�̃L�[�X�e�[�g����
    if( !m_PrevKeyState )
        m_PrevKeyState = AQUA_NEW char[m_max_input_key];

    ZeroMemory( m_PrevKeyState, m_max_input_key );
}

/*
 *  �X�V
 */
void
aqua::core::CKeyboard::
Update( void )
{
    // �O�̃t���[���̃L�[��Ԃ�ۑ�
    memcpy( m_PrevKeyState, m_KeyState, m_max_input_key );

    // ���͏�Ԃ̎擾
    GetHitKeyStateAll( m_KeyState );
}

/*
 *  ���
 */
void
aqua::core::CKeyboard::
Finalize( void )
{
    AQUA_SAFE_DELETE_ARRAY( m_PrevKeyState );
    AQUA_SAFE_DELETE_ARRAY( m_KeyState );
}

/*
 *  �{�^������
 */
bool
aqua::core::CKeyboard::
Button( aqua::keyboard::KEY_ID key )
{
    return m_KeyState[static_cast<int>(key)];
}

/*
 *  �g���K�[����
 */
bool
aqua::core::CKeyboard::
Trigger( aqua::keyboard::KEY_ID key )
{
    return ( m_KeyState[static_cast<int>(key)] && !m_PrevKeyState[static_cast<int>(key)] );
}

/*
 *  �����[�X����
 */
bool
aqua::core::CKeyboard::
Released( aqua::keyboard::KEY_ID key )
{
    return ( !m_KeyState[static_cast<int>(key)] && m_PrevKeyState[static_cast<int>(key)] );
}

/*
 *  �R���X�g���N�^
 */
aqua::core::CKeyboard::
CKeyboard( void )
    : m_KeyState( nullptr )
    , m_PrevKeyState( nullptr )
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
aqua::core::CKeyboard::
CKeyboard( const aqua::core::CKeyboard& rhs )
    : m_KeyState(nullptr)
    , m_PrevKeyState(nullptr)
{
    (void)rhs;
}

/*
 *  ������Z�q
 */
aqua::core::CKeyboard&
aqua::core::CKeyboard::
operator=( const CKeyboard& rhs )
{
    (void)rhs;

    return *this;
}
