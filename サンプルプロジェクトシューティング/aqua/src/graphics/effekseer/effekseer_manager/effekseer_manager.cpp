
/*!
 *  @file       effekseer_manager.cpp
 *  @brief      Effekseer管理クラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "effekseer_manager.h"
#include "..\effekseer_resource\effekseer_resource.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"

/*
 *  インスタンスの取得
 */
aqua::core::CEffekseerManager&
aqua::core::CEffekseerManager::
GetInstance( void )
{
    static CEffekseerManager instance;

    return instance;
}

/*
 *  Effekseerクラスの読み込み
 */
aqua::core::CEffekseerResource*
aqua::core::CEffekseerManager::
Load( const std::string& file_name )
{
    // Effekseer検索
    CEffekseerResource* effect = Find( file_name );

    // Effekseerが見つからなかった
    if( !effect )
    {
        // 新しくEffekseer生成
        effect = AQUA_NEW CEffekseerResource( );

        // 読み込み
        effect->Load( file_name );

        // Effekseerリストに追加
        m_EffekseerList.push_back( effect );
    }

    // 参照カウンタ加算
    effect->AddReference( );

    return effect;
}

/*
 *  Effekseerクラスの解放
 */
void
aqua::core::CEffekseerManager::
Unload( core::CEffekseerResource* effect )
{
    if( !effect ) return;

    if( m_EffekseerList.empty( ) ) return;

    // 参照カウンタ減算
    // 参照がなくなったら解放
    if( effect->RemoveReference( ) > 0 ) return;

    EFFEKSEER_LIST::iterator it  = m_EffekseerList.begin( );
    EFFEKSEER_LIST::iterator end = m_EffekseerList.end( );

    while( it != end )
    {
        if( (*it)->GetResourceName( ) == effect->GetResourceName( ) )
        {
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );

            m_EffekseerList.erase( it );

            break;
        }

        ++it;
    }
}

/*
 *  Effekseerクラスの検索
 */
aqua::core::CEffekseerResource*
aqua::core::CEffekseerManager::
Find( const std::string& file_name )
{
    if( m_EffekseerList.empty( ) ) return NULL;

    EFFEKSEER_LIST::iterator it  = m_EffekseerList.begin( );
    EFFEKSEER_LIST::iterator end = m_EffekseerList.end( );

    // ファイル名が一致したEffekseerクラスを返す
    while( it != end )
    {
        if( ( *it )->GetResourceName( ) == file_name )
            return ( *it );

        ++it;
    }

    return NULL;
}

/*
 *  Effekseerリストのクリア
 */
void
aqua::core::CEffekseerManager::
Clear( void )
{
    if( m_EffekseerList.empty( ) ) return;

    EFFEKSEER_LIST::iterator it  = m_EffekseerList.begin( );
    EFFEKSEER_LIST::iterator end = m_EffekseerList.end( );

    while( it != end )
    {
        if( (*it) )
        {
            // Effekseer解放
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );
        }

        ++it;
    }

    // Effekseerリスト解放
    m_EffekseerList.clear( );
}

/*
 *  コンストラクタ
 */
aqua::core::CEffekseerManager::
CEffekseerManager( void )
{
    m_EffekseerList.clear( );
}

/*
 *  コピーコンストラクタ
 */
aqua::core::CEffekseerManager::
CEffekseerManager( const aqua::core::CEffekseerManager& rhs )
{
    (void)rhs;
}

/*
 *  代入演算子
 */
aqua::core::CEffekseerManager&
aqua::core::CEffekseerManager::
operator=( const aqua::core::CEffekseerManager& rhs )
{
    (void)rhs;

    return *this;
}
