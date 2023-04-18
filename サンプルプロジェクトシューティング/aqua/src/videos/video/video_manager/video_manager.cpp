
/*!
 *  @file       video_manager.cpp
 *  @brief      ビデオ管理クラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "video_manager.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"
#include "..\..\video\video_resource\video_resource.h"

/*
 *  インスタンスの取得
 */
aqua::core::CVideoManager&
aqua::core::CVideoManager::
GetInstance( void )
{
    static CVideoManager instance;

    return instance;
}

/*
 *  ビデオクラスの読み込み
 */
aqua::core::CVideoResource*
aqua::core::CVideoManager::
Load( const std::string& file_name )
{
    // ビデオ検索
    CVideoResource* video = Find( file_name );

    // ビデオが見つからなかった
    if( !video )
    {
        // 新しくビデオ生成
        video = AQUA_NEW CVideoResource( );

        // 読み込み
        video->Load( file_name );

        // ビデオリストに追加
        m_VideoResourceList.push_back( video );
    }
    
    // 参照カウンタ加算
    video->AddReference( );

    return video;
}

/*
 *  ビデオクラスの解放
 */
void
aqua::core::CVideoManager::
Unload( core::CVideoResource* video )
{
    if( !video ) return;

    if( m_VideoResourceList.empty( ) ) return;

    // 参照カウンタ減算
    // 参照がなくなったら解放
    if( video->RemoveReference( ) > 0 ) return;

    VIDEO_RESOURCE_LIST::iterator it  = m_VideoResourceList.begin( );
    VIDEO_RESOURCE_LIST::iterator end = m_VideoResourceList.end( );

    while( it != end )
    {
        if( (*it)->GetResourceName( ) == video->GetResourceName( ) )
        {
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );

            m_VideoResourceList.erase( it );

            break;
        }

        ++it;
    }
}

/*
 *  ビデオクラスの検索
 */
aqua::core::CVideoResource*
aqua::core::CVideoManager::
Find( const std::string& file_name )
{
    if( m_VideoResourceList.empty( ) ) return nullptr;

    VIDEO_RESOURCE_LIST::iterator it  = m_VideoResourceList.begin( );
    VIDEO_RESOURCE_LIST::iterator end = m_VideoResourceList.end( );

    // ファイル名が一致したビデオクラスを返す
    while( it != end )
    {
        if( ( *it )->GetResourceName( ) == file_name )
            return ( *it );

        ++it;
    }

    return nullptr;
}

/*
 *  ビデオリストのクリア
 */
void
aqua::core::CVideoManager::
Clear( void )
{
    if( m_VideoResourceList.empty( ) ) return;

    VIDEO_RESOURCE_LIST::iterator it  = m_VideoResourceList.begin( );
    VIDEO_RESOURCE_LIST::iterator end = m_VideoResourceList.end( );

    while( it != end )
    {
        if( (*it) )
        {
            // ビデオ解放
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );
        }

        ++it;
    }

    // ビデオリスト解放
    m_VideoResourceList.clear( );
}

/*
 *  コンストラクタ
 */
aqua::core::CVideoManager::
CVideoManager( void )
{
    m_VideoResourceList.clear( );
}

/*
 *  コピーコンストラクタ
 */
aqua::core::CVideoManager::
CVideoManager( const aqua::core::CVideoManager& rhs )
{
    (void)rhs;
}

/*
 *  代入演算子
 */
aqua::core::CVideoManager&
aqua::core::CVideoManager::
operator=( const aqua::core::CVideoManager& rhs )
{
    (void)rhs;

    return *this;
}
