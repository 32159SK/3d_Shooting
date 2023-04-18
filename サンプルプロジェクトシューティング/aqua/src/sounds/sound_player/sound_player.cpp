
/*!
 *  @file       sound_player.cpp
 *  @brief      サウンドプレイヤー
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include <DxLib.h>
#include "sound_player.h"
#include "..\sound\sound_manager\sound_manager.h"
#include "..\..\utility\memory\memory.h"

const int   aqua::CSoundPlayer::m_max_volume    =  255;
const int   aqua::CSoundPlayer::m_min_volume    =    0;

/*
 *  コンストラクタ
 */
aqua::CSoundPlayer::
CSoundPlayer( void )
    : m_LoopFlag( false )
{
}

/*
 *  再生用バッファ作成
 */
void
aqua::CSoundPlayer::
Create( const std::string& file_name, bool loop, int buffer_count )
{
    m_LoopFlag = loop;

    // ループ再生ならバッファは1つだけ生成する
    if( m_LoopFlag ) buffer_count = 1;

    m_Sound.Load( file_name, buffer_count );

    //SetFrequencySoundMem(44100 * 2, m_Sound.GetResourceHandle());
}

/*
 *  再生用バッファ作成
 */
void
aqua::CSoundPlayer::
Create( const aqua::CSound& sound )
{
    m_Sound = sound;
}

/*
 *  解放
 */
void
aqua::CSoundPlayer::
Delete( void )
{
    m_Sound.Unload( );
}

/*
 *  再生
 */
void
aqua::CSoundPlayer::
Play( void )
{
    if( m_Sound.IsEnable( ) )
        PlaySoundMem( m_Sound.GetResourceHandle( ), ( m_LoopFlag ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK ) );
}

/*
 *  停止
 */
void
aqua::CSoundPlayer::
Stop( void )
{
    if( m_Sound.IsEnable( ) )
        StopSoundMem( m_Sound.GetResourceHandle( ) );
}

/*
 *  頭出しして再生
 */
void
aqua::CSoundPlayer::
ReStart( void )
{
    Stop( );
    Play( );
}

/*
 *  現在の再生時間を取得
 */
float
aqua::CSoundPlayer::
GetCurrentPlayTime( void )
{
    return m_Sound.GetCurrentPlayTime( );
}

/*
 *  総再生時間を取得
 */
float
aqua::CSoundPlayer::
GetTotalTime( void )
{
    return m_Sound.GetTotalTime( );
}

/*
 *  再生中か調べる
 */
bool
aqua::CSoundPlayer::
IsPlaying()
{
    return CheckSoundMem(m_Sound.GetResourceHandle());
}

/*
 *  ボリューム設定
 */
void
aqua::CSoundPlayer::
SetVolume( int volume )
{
    // 最小チェック
    if( volume < m_min_volume )
        volume = m_min_volume;

    // 最大チェック
    if( volume > m_max_volume )
        volume = m_max_volume;

    ChangeVolumeSoundMem( volume, m_Sound.GetResourceHandle( ) );
}

/*
 *  リソースハンドル取得
 */
int
aqua::CSoundPlayer::
GetResourceHandle( void ) const
{
    return m_Sound.GetResourceHandle( );
}

/*
 *  ソフトウェアサウンドハンドル取得
 */
int
aqua::CSoundPlayer::
GetSoftSoundHandle( void ) const
{
    return m_Sound.GetSoftSoundHandle( );
}
