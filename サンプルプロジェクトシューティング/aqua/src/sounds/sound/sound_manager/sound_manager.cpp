
/*!
 *  @file       sound_manager.cpp
 *  @brief      サウンド管理クラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "sound_manager.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"
#include "..\..\sound\sound_resource\sound_resource.h"

/*
 *  インスタンスの取得
 */
aqua::core::CSoundManager&
aqua::core::CSoundManager::
GetInstance( void )
{
    static CSoundManager instance;

    return instance;
}

/*
 *  サウンドクラスの読み込み
 */
aqua::core::CSoundResource*
aqua::core::CSoundManager::
Load( const std::string& file_name, int buffer_count )
{
    // サウンド検索
    CSoundResource* sound = Find( file_name );

    // サウンドが見つからなかった
    if( !sound )
    {
        // 新しくサウンド生成
        sound = AQUA_NEW CSoundResource( );

        // 読み込み
        sound->Load( file_name, buffer_count );

        // サウンドリストに追加
        m_SoundResourceList.push_back( sound );
    }
    
    // 参照カウンタ加算
    sound->AddReference( );

    return sound;
}

/*
 *  サウンドクラスの解放
 */
void
aqua::core::CSoundManager::
Unload( core::CSoundResource* sound )
{
    if( !sound ) return;

    if( m_SoundResourceList.empty( ) ) return;

    // 参照カウンタ減算
    // 参照がなくなったら解放
    if( sound->RemoveReference( ) > 0 ) return;

    SOUND_RESOURCE_LIST::iterator it  = m_SoundResourceList.begin( );
    SOUND_RESOURCE_LIST::iterator end = m_SoundResourceList.end( );

    while( it != end )
    {
        if( (*it)->GetResourceName( ) == sound->GetResourceName( ) )
        {
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );

            m_SoundResourceList.erase( it );

            break;
        }

        ++it;
    }
}

/*
 *  更新
 */
void
aqua::core::CSoundManager::
Update( void )
{
#ifdef AQUA_DEBUG

    if( m_SoundResourceList.empty( ) ) return;

    SOUND_RESOURCE_LIST::iterator it  = m_SoundResourceList.begin( );
    SOUND_RESOURCE_LIST::iterator end = m_SoundResourceList.end( );

    while( it != end )
    {
        float frequency = (float)( (*it)->GetDefaultFrequency( ) );

        frequency *= aqua::core::CVisualDebugger::GetInstance( ).GetDebugDeltaTimeScale( );

        (*it)->SetFrequency( (int)frequency );

        ++it;
    }
#endif
}

/*
 *  サウンドクラスの検索
 */
aqua::core::CSoundResource*
aqua::core::CSoundManager::
Find( const std::string& file_name )
{
    if( m_SoundResourceList.empty( ) ) return nullptr;

    SOUND_RESOURCE_LIST::iterator it  = m_SoundResourceList.begin( );
    SOUND_RESOURCE_LIST::iterator end = m_SoundResourceList.end( );

    // ファイル名が一致したサウンドクラスを返す
    while( it != end )
    {
        if( ( *it )->GetResourceName( ) == file_name )
            return ( *it );

        ++it;
    }

    return nullptr;
}

/*
 *  サウンドリストのクリア
 */
void
aqua::core::CSoundManager::
Clear( void )
{
    if( m_SoundResourceList.empty( ) ) return;

    SOUND_RESOURCE_LIST::iterator it  = m_SoundResourceList.begin( );
    SOUND_RESOURCE_LIST::iterator end = m_SoundResourceList.end( );

    while( it != end )
    {
        if( (*it) )
        {
            // サウンド解放
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );
        }

        ++it;
    }

    // サウンドリスト解放
    m_SoundResourceList.clear( );
}

/*
 *  コンストラクタ
 */
aqua::core::CSoundManager::
CSoundManager( void )
{
    m_SoundResourceList.clear( );
}

/*
 *  コピーコンストラクタ
 */
aqua::core::CSoundManager::
CSoundManager( const aqua::core::CSoundManager& rhs )
{
    (void)rhs;
}

/*
 *  代入演算子
 */
aqua::core::CSoundManager&
aqua::core::CSoundManager::
operator=( const aqua::core::CSoundManager& rhs )
{
    (void)rhs;

    return *this;
}
