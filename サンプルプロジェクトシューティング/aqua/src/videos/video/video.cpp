
/*!
 *  @file       video.cpp
 *  @brief      ビデオ管理
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "video.h"
#include "video_manager\video_manager.h"
#include "..\..\utility\memory\memory.h"

/*
 *  コンストラクタ
 */
aqua::CVideo::
CVideo( void )
    : m_VideoResource( nullptr )
{
}

/*
 *  コピーコンストラクタ
 */
aqua::CVideo::
CVideo( const aqua::CVideo& video )
{
    if( m_VideoResource )
        m_VideoResource->RemoveReference( );

    m_VideoResource = video.m_VideoResource;

    // 参照カウンタ加算
    m_VideoResource->AddReference( );
}

/*
 *  ビデオの読み込み
 */
void
aqua::CVideo::
Load( const std::string& file_name )
{
    // ビデオリソース退避
    core::CVideoResource* video = m_VideoResource;

    // ビデオマネージャからビデオをロード
    m_VideoResource = core::CVideoManager::GetInstance( ).Load( file_name );

    if( video )
    {
        int count = video->RemoveReference( );

        // 前のビデオの参照カウンタがなくなったら解放
        if( count <= 0 )
            core::CVideoManager::GetInstance( ).Unload( video );
    }
}

/*
 *  ビデオの解放
 */
void
aqua::CVideo::
Unload( void )
{
    // ビデオ解放
    if( m_VideoResource )
        core::CVideoManager::GetInstance( ).Unload( m_VideoResource );

    m_VideoResource = nullptr;
}

/*
 *  代入演算子のオーバーロード
 */
aqua::CVideo&
aqua::CVideo::
operator=( const aqua::CVideo& video )
{
    // ビデオを持っていたら参照を減算
    if( m_VideoResource )
        m_VideoResource->RemoveReference( );

    m_VideoResource = video.m_VideoResource;

    // 参照カウンタ加算
    m_VideoResource->AddReference( );

    return *this;
}
