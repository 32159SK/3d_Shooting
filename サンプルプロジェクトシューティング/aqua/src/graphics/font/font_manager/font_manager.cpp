
/*!
 *  @file       font_manager.cpp
 *  @brief      フォント管理クラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "font_manager.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"

/*
 *  インスタンスの取得
 */
aqua::core::CFontManager&
aqua::core::CFontManager::
GetInstance( void )
{
    static CFontManager instance;

    return instance;
}

/*
 *  フォント生成
 */
aqua::core::CFontResource*
aqua::core::CFontManager::
Create( int size, int edge_bold, bool anti_aliasing, aqua::FONT_FAMILY_ID family_id )
{
    // フォント検索
    CFontResource* font = Find( size, edge_bold, family_id );

    // フォントが見つからなかった
    if( !font )
    {
        // 新しくフォント生成
        font = AQUA_NEW CFontResource( );

        // 読み込み
        font->Create( size, edge_bold, anti_aliasing, family_id );

        // フォントリストに追加
        m_FontList.push_back( font );
    }

    // 参照カウンタ加算
    font->AddReference( );

    return font;
}

/*
 *  フォント解放
 */
void
aqua::core::CFontManager::
Delete( aqua::core::CFontResource* font )
{
    if( !font ) return;

    if( m_FontList.empty( ) ) return;

    // 参照カウンタ減算
    // 参照がなくなったら解放
    if( font->RemoveReference( ) > 0 ) return;

    FONT_LIST::iterator it  = m_FontList.begin( );
    FONT_LIST::iterator end = m_FontList.end( );

    while( it != end )
    {
        if( (*it)->CheckFont( font ) )
        {
            (*it)->Delete( );

            AQUA_SAFE_DELETE( (*it) );

            m_FontList.erase( it );

            break;
        }

        ++it;
    }
}

/*
 *  フォントクラスの検索
 */
aqua::core::CFontResource*
aqua::core::CFontManager::
Find( int size, int edge_bold, aqua::FONT_FAMILY_ID family_id )
{
    if( m_FontList.empty( ) ) return nullptr;

    FONT_LIST::iterator it  = m_FontList.begin( );
    FONT_LIST::iterator end = m_FontList.end( );

    // 一致したフォントクラスを返す
    while( it != end )
    {
        if( ( *it )->CheckFont( size, edge_bold, family_id ) )
            return ( *it );

        ++it;
    }

    return nullptr;
}

/*
 *  フォントリストのクリア
 */
void
aqua::core::CFontManager::
Clear( void )
{
    if( m_FontList.empty( ) ) return;

    FONT_LIST::iterator it  = m_FontList.begin( );
    FONT_LIST::iterator end = m_FontList.end( );

    while( it != end )
    {
        if( (*it) )
        {
            // フォント解放
            (*it)->Delete( );

            AQUA_SAFE_DELETE( (*it) );
        }

        ++it;
    }

    // フォントリスト解放
    m_FontList.clear( );
}

/*
 *  コンストラクタ
 */
aqua::core::CFontManager::
CFontManager( void )
{
    m_FontList.clear( );
}

/*
 *  コピーコンストラクタ
 */
aqua::core::CFontManager::
CFontManager( const aqua::core::CFontManager& rhs )
{
    (void)rhs;
}

/*
 *  代入演算子
 */
aqua::core::CFontManager&
aqua::core::CFontManager::
operator=( const aqua::core::CFontManager& rhs )
{
    (void)rhs;

    return *this;
}
