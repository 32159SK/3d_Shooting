
/*!
 *  @file       thread.cpp
 *  @brief      スレッド管理
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "thread.h"
#include <process.h>

/*
 *  コンストラクタ
 */
aqua::IThread::
IThread( void )
    : m_ThreadHandle( NULL )
    , m_EventHandle( NULL )
    , m_StopFlag( false )
{
    // イベント生成
    m_EventHandle = CreateEvent( NULL, false, false, NULL );
}

/*
 *  デストラクタ
 */
aqua::IThread::
~IThread( void )
{
    // スレッド停止
    StopAndWait( );

    // ハンドル解放
    CloseHandle( m_EventHandle );
    CloseHandle( m_ThreadHandle );
}

/*
 *  スレッド開始
 */
void
aqua::IThread::
Start( void )
{
    // 既にスレッドが起動している
    if( m_ThreadHandle != NULL || m_StopFlag )
        return;

    // スレッド起動
    m_ThreadHandle = (HANDLE)_beginthreadex( NULL, 0, ThreadCallback, (void*)this, 0, NULL );
}

/*
 *  スレッド停止
 */
void
aqua::IThread::
Stop( void )
{
    m_StopFlag = true;

    SetEvent( m_EventHandle );
}

/*
 *  スレッド停止待機
 */
void
aqua::IThread::
StopAndWait( void )
{
    Stop( );

    // 停止するまで待機
    if( m_ThreadHandle != NULL )
        WaitForSingleObject( m_ThreadHandle, INFINITE );
}

/*
 *  スレッドの起動チェック
 */
bool
aqua::IThread::
IsRunning( void ) const
{
    return ( WaitForSingleObject( m_ThreadHandle, 0 ) == WAIT_TIMEOUT );
}

/*
 *  スレッドの有効状態チェック
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
 *  一定時間スレッド停止
 */
void
aqua::IThread::
Sleep( unsigned int milliseconds )
{
    if( !m_StopFlag )
        WaitForSingleObject( m_EventHandle, milliseconds );
}

/*
 *  スレッドコールバック
 */
unsigned int
__stdcall
aqua::IThread::
ThreadCallback( void* p )
{
    IThread* thread = (IThread*)p;

    // スレッド処理の実行
    thread->Run( );

    return 0;
}
