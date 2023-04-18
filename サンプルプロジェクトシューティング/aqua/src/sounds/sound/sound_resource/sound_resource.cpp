
/*!
 *  @file       sound_resource.cpp
 *  @brief      サウンドリソース
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include <DxLib.h>
#include "sound_resource.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"

const int aqua::core::CSoundResource::m_max_load_buffer = 10;

/*
 *  コンストラクタ
 */
aqua::core::CSoundResource::
CSoundResource( void )
    : IResourceObject( aqua::core::RESOURCE_TYPE::LOAD_SOUND )
    , m_DefaultFrequency( 0 )
    , m_SoftSoundHandle( 0 )
{
}

/*
 *  読み込み
 */
void
aqua::core::CSoundResource::
Load( const std::string& file_name, int buffer_count )
{
    if( m_Enabel ) return;

    // ソフトウェアサウンドの生成
    m_SoftSoundHandle = LoadSoftSound(file_name.c_str());

    AQUA_DX_ASSERT( m_SoftSoundHandle, file_name + "の読み込みに失敗しました。" );

    // サウンドのリソースハンドル生成
    m_ResourceHandle = LoadSoundMemFromSoftSound( m_SoftSoundHandle );

    AQUA_DX_ASSERT( m_ResourceHandle, file_name + "の生成に失敗しました。" );

    // 初期の周波数取得
    m_DefaultFrequency = GetFrequencySoundMem( m_ResourceHandle );

    // ファイルパスを保存
    m_ResourceName = file_name;

    // 読み込み済み
    m_Enabel = true;
}

/*
 *  解放
 */
void
aqua::core::CSoundResource::
Unload( void )
{
    DeleteSoftSound( m_SoftSoundHandle );

    DeleteSoundMem( m_ResourceHandle );

    m_ResourceHandle = AQUA_UNUSED_HANDLE;

    m_ReferenceCount = 0;

    m_ResourceName.clear( );

    m_ResourceType = RESOURCE_TYPE::DUMMY;

    m_DefaultFrequency = 0;

    m_Enabel = false;
}

/*
 *  現在の再生時間を取得
 */
float
aqua::core::CSoundResource::
GetCurrentPlayTime( void )
{
    if( m_ResourceHandle == AQUA_UNUSED_HANDLE )
        return 0.0f;

    return (float)GetSoundCurrentTime( m_ResourceHandle ) / 1000.0f;
}

/*
 *  総再生時間を取得
 */
float
aqua::core::CSoundResource::
GetTotalTime( void )
{
    if( m_ResourceHandle == AQUA_UNUSED_HANDLE )
        return 0.0f;

    return (float)GetSoundTotalTime( m_ResourceHandle ) / 1000.0f;
}

/*
 *  周波数を取得
 */
int
aqua::core::CSoundResource::
GetFrequency( void )
{
    if( m_ResourceHandle == AQUA_UNUSED_HANDLE ) return 0;

    return GetFrequencySoundMem( m_ResourceHandle );
}

/*
 *  初期の周波数を取得
 */
int
aqua::core::CSoundResource::
GetDefaultFrequency( void )
{
    return m_DefaultFrequency;
}

/*
 *  初期の周波数を取得
 */
void
aqua::core::CSoundResource::
SetFrequency( int frequency )
{
    if( m_ResourceHandle == AQUA_UNUSED_HANDLE ) return;

    SetFrequencySoundMem( frequency, m_ResourceHandle );
}

/*
 *  初期の周波数を取得
 */
int
aqua::core::CSoundResource::
GetSoftSoundHandle( void )
{
    return m_SoftSoundHandle;
}
