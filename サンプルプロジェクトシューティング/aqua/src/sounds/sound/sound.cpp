
/*!
 *  @file       sound.cpp
 *  @brief      サウンド管理
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "sound.h"
#include "sound_manager\sound_manager.h"
#include "..\..\utility\memory\memory.h"

/*
 *  コンストラクタ
 */
aqua::CSound::
CSound( void )
    : m_SoundResource( nullptr )
{
}

/*
 *  コピーコンストラクタ
 */
aqua::CSound::
CSound( const aqua::CSound& sound )
{
    if( m_SoundResource )
        m_SoundResource->RemoveReference( );

    m_SoundResource = sound.m_SoundResource;

    // 参照カウンタ加算
    m_SoundResource->AddReference( );
}

/*
 *  サウンドの読み込み
 */
void
aqua::CSound::
Load( const std::string& file_name, int buffer_count )
{
    // サウンドリソース退避
    core::CSoundResource* sound = m_SoundResource;

    // サウンドマネージャからサウンドをロード
    m_SoundResource = core::CSoundManager::GetInstance( ).Load( file_name, buffer_count );

    if( sound )
    {
        int count = sound->RemoveReference( );

        // 前のサウンドの参照カウンタがなくなったら解放
        if( count <= 0 )
            core::CSoundManager::GetInstance( ).Unload( sound );
    }
}

/*
 *  サウンドの解放
 */
void
aqua::CSound::
Unload( void )
{
    // サウンド解放
    if( m_SoundResource )
        core::CSoundManager::GetInstance( ).Unload( m_SoundResource );

    m_SoundResource = nullptr;
}

/*
 *  代入演算子のオーバーロード
 */
aqua::CSound&
aqua::CSound::
operator=( const aqua::CSound& sound )
{
    // サウンドを持っていたら参照を減算
    if( m_SoundResource )
        m_SoundResource->RemoveReference( );

    m_SoundResource = sound.m_SoundResource;

    // 参照カウンタ加算
    m_SoundResource->AddReference( );

    return *this;
}
