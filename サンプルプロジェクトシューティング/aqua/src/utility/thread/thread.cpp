
/*!
 *  @file       thread.cpp
 *  @brief      �X���b�h�Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "thread.h"
#include <process.h>

/*
 *  �R���X�g���N�^
 */
aqua::IThread::
IThread( void )
    : m_ThreadHandle( NULL )
    , m_EventHandle( NULL )
    , m_StopFlag( false )
{
    // �C�x���g����
    m_EventHandle = CreateEvent( NULL, false, false, NULL );
}

/*
 *  �f�X�g���N�^
 */
aqua::IThread::
~IThread( void )
{
    // �X���b�h��~
    StopAndWait( );

    // �n���h�����
    CloseHandle( m_EventHandle );
    CloseHandle( m_ThreadHandle );
}

/*
 *  �X���b�h�J�n
 */
void
aqua::IThread::
Start( void )
{
    // ���ɃX���b�h���N�����Ă���
    if( m_ThreadHandle != NULL || m_StopFlag )
        return;

    // �X���b�h�N��
    m_ThreadHandle = (HANDLE)_beginthreadex( NULL, 0, ThreadCallback, (void*)this, 0, NULL );
}

/*
 *  �X���b�h��~
 */
void
aqua::IThread::
Stop( void )
{
    m_StopFlag = true;

    SetEvent( m_EventHandle );
}

/*
 *  �X���b�h��~�ҋ@
 */
void
aqua::IThread::
StopAndWait( void )
{
    Stop( );

    // ��~����܂őҋ@
    if( m_ThreadHandle != NULL )
        WaitForSingleObject( m_ThreadHandle, INFINITE );
}

/*
 *  �X���b�h�̋N���`�F�b�N
 */
bool
aqua::IThread::
IsRunning( void ) const
{
    return ( WaitForSingleObject( m_ThreadHandle, 0 ) == WAIT_TIMEOUT );
}

/*
 *  �X���b�h�̗L����ԃ`�F�b�N
 */
bool
aqua::IThread::
IsValid( void ) const
{
    if( m_ThreadHandle == NULL || IsRunning( ) )
        return !m_StopFlag;

    return false;
}

/*
 *  ��莞�ԃX���b�h��~
 */
void
aqua::IThread::
Sleep( unsigned int milliseconds )
{
    if( !m_StopFlag )
        WaitForSingleObject( m_EventHandle, milliseconds );
}

/*
 *  �X���b�h�R�[���o�b�N
 */
unsigned int
__stdcall
aqua::IThread::
ThreadCallback( void* p )
{
    IThread* thread = (IThread*)p;

    // �X���b�h�����̎��s
    thread->Run( );

    return 0;
}
