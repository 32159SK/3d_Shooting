
/*!
 *  @file       aqua.cpp
 *  @brief      AQUA Game Library
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "aqua.h"

/*
 *  ���C�u�����Z�b�g�A�b�v
 */
void
aqua::
Setup( HINSTANCE instance_handle, aqua::IGameObject* game )
{
    // ���������[�N���m
    AQUA_CHECK_MEMORY_LEAK;

    // �Q�[���t���[�����[�N�擾
    aqua::core::CFramework& framework = aqua::core::CFramework::GetInstance( );

    // �Q�[���t���[�����[�N������
    framework.Initialize( instance_handle, game );

    // �Q�[���t���[�����[�N�X�V
    framework.Update( );

    // �Q�[���t���[�����[�N���
    framework.Finalize( );
}

/*
 *  �C���X�^���X�n���h���擾
 */
HINSTANCE
aqua::
GetInstanceHandle( void )
{
    return aqua::core::CFramework::GetInstance( ).GetInstanceHandle( );
}

/*
 *  �E�B���h�E�n���h���擾
 */
HWND
aqua::
GetWindowHandle( void )
{
    return aqua::core::CFramework::GetInstance( ).GetWindowHandle( );
}

/*
 *  �E�B���h�E�̉����擾
 */
unsigned int
aqua::
GetWindowWidth( void )
{
    return aqua::core::CFramework::GetInstance( ).GetWindowWidth( );
}

/*
 *  �E�B���h�E�̏c���擾
 */
unsigned int
aqua::
GetWindowHeight( void )
{
    return aqua::core::CFramework::GetInstance( ).GetWindowHeight( );
}

/*
 *  �f���^�^�C���擾
 */
float
aqua::
GetDeltaTime( void )
{
    return aqua::core::CFramework::GetInstance( ).GetDeltaTime( );
}

/*
 *  �f���^�^�C��(�{���Ȃ�)�擾
 */
float
aqua::
GetUnscaledDeltaTime( void )
{
    return aqua::core::CFramework::GetInstance( ).GetUnscaledDeltaTime( );
}

/*
 *  �f���^�^�C���{���擾
 */
float
aqua::
GetDeltaTimeScale( void )
{
    return aqua::core::CFramework::GetInstance( ).GetDeltaTimeScale( );
}

/*
 *  �f���^�^�C���{���ݒ�
 */
void
aqua::
SetDeltaTimeScale( float scale )
{
    aqua::core::CFramework::GetInstance( ).SetDeltaTimeScale( scale );
}

/*
 *  �t���[�����[�g�ݒ�
 */
void
aqua::
SetFrameRate( int frame_rate )
{
    aqua::core::CFramework::GetInstance( ).SetFrameRate( frame_rate );
}

/*
 *  �Q�[���I�u�W�F�N�g�̌���
 */
aqua::IGameObject*
aqua::
FindGameObject( const std::string& name )
{
    return aqua::core::CFramework::GetInstance( ).FindGameObject( name );
}

/*
 *  �Q�[���I�u�W�F�N�g�̌���
 */
aqua::IGameObject*
aqua::
FindGameObject( aqua::FIND_METHOD func )
{
    return aqua::core::CFramework::GetInstance( ).FindGameObject( func );
}

/*
 *  ��ʂ̃N���A
 */
void
aqua::
Clear( unsigned int color )
{
    // ��ʂ̔w�i�F��ݒ�
    SetBackgroundColor( ( ( color & 0x00ff0000 ) >> 16 ), ( ( color & 0x0000ff00 ) >> 8 ), ( color & 0x000000ff ) );

    // ��ʂ̃N���A
    ClearDrawScreen( );
}
