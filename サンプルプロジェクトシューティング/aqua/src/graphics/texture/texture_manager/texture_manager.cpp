
/*!
 *  @file       texture_manager.cpp
 *  @brief      2Dテクスチャ管理クラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "texture_manager.h"
#include "..\texture_resource\texture_resource.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"

/*
 *  インスタンスの取得
 */
aqua::core::CTextureManager&
aqua::core::CTextureManager::
GetInstance( void )
{
    static CTextureManager instance;

    return instance;
}

/*
 *  テクスチャクラスの読み込み
 */
aqua::core::CTextureResource*
aqua::core::CTextureManager::
Load( const std::string& file_name )
{
    // テクスチャ検索
    CTextureResource* texture = Find( file_name );

    // テクスチャが見つからなかった
    if( !texture )
    {
        // 新しくテクスチャ生成
        texture = AQUA_NEW CTextureResource( );

        // 読み込み
        texture->Load( file_name );

        // テクスチャリストに追加
        m_TextureList.push_back( texture );
    }

    // 参照カウンタ加算
    texture->AddReference( );

    return texture;
}

/*
 *  テクスチャクラスの解放
 */
void
aqua::core::CTextureManager::
Unload( core::CTextureResource* texture )
{
    if( !texture ) return;

    if( m_TextureList.empty( ) ) return;

    // 参照カウンタ減算
    // 参照がなくなったら解放
    if( texture->RemoveReference( ) > 0 ) return;

    TEXTURE_LIST::iterator it  = m_TextureList.begin( );
    TEXTURE_LIST::iterator end = m_TextureList.end( );

    while( it != end )
    {
        if( (*it)->GetResourceName( ) == texture->GetResourceName( ) )
        {
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );

            m_TextureList.erase( it );

            break;
        }

        ++it;
    }
}

/*
 *  テクスチャクラスの検索
 */
aqua::core::CTextureResource*
aqua::core::CTextureManager::
Find( const std::string& file_name )
{
    if( m_TextureList.empty( ) ) return NULL;

    TEXTURE_LIST::iterator it  = m_TextureList.begin( );
    TEXTURE_LIST::iterator end = m_TextureList.end( );

    // ファイル名が一致したテクスチャクラスを返す
    while( it != end )
    {
        if( ( *it )->GetResourceName( ) == file_name )
            return ( *it );

        ++it;
    }

    return NULL;
}

/*
 *  テクスチャリストのクリア
 */
void
aqua::core::CTextureManager::
Clear( void )
{
    if( m_TextureList.empty( ) ) return;

    TEXTURE_LIST::iterator it  = m_TextureList.begin( );
    TEXTURE_LIST::iterator end = m_TextureList.end( );

    while( it != end )
    {
        if( (*it) )
        {
            // テクスチャ解放
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );
        }

        ++it;
    }

    // テクスチャリスト解放
    m_TextureList.clear( );
}

/*
 *  コンストラクタ
 */
aqua::core::CTextureManager::
CTextureManager( void )
{
    m_TextureList.clear( );
}

/*
 *  コピーコンストラクタ
 */
aqua::core::CTextureManager::
CTextureManager( const aqua::core::CTextureManager& rhs )
{
    (void)rhs;
}

/*
 *  代入演算子
 */
aqua::core::CTextureManager&
aqua::core::CTextureManager::
operator=( const aqua::core::CTextureManager& rhs )
{
    (void)rhs;

    return *this;
}

/*
 *  テクスチャ生成
 */
aqua::core::CTextureResource*
aqua::core::CTextureManager::
Create( int width, int height, bool alpha_channel )
{
    CTextureResource* texture = nullptr;

    // 新しくテクスチャ生成
    texture = AQUA_NEW CTextureResource( );

    // 生成
    texture->Create( width, height, alpha_channel );

    // テクスチャリストに追加
    m_TextureList.push_back( texture );

    // 参照カウンタ加算
    texture->AddReference( );

    return texture;
}

/*
 *  テクスチャ解放
 */
void
aqua::core::CTextureManager::
Delete( aqua::core::CTextureResource* texture )
{
    if( !texture ) return;

    if( m_TextureList.empty( ) ) return;

    // 参照カウンタ減算
    // 参照がなくなったら解放
    if( texture->RemoveReference( ) > 0 ) return;

    TEXTURE_LIST::iterator it  = m_TextureList.begin( );
    TEXTURE_LIST::iterator end = m_TextureList.end( );

    while( it != end )
    {
        if( (*it) == texture )
        {
            (*it)->Delete( );

            AQUA_SAFE_DELETE( (*it) );

            m_TextureList.erase( it );

            break;
        }

        ++it;
    }
}
