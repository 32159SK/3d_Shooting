
/*!
 *  @file       font.cpp
 *  @brief      フォントクラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "font.h"
#include "font_manager\font_manager.h"

/*
 *  コンストラクタ
 */
aqua::CFont::
CFont( void )
    : m_FontResource( nullptr )
{
}

/*
 *  コピーコンストラクタ
 */
aqua::CFont::
CFont( const aqua::CFont& mesh )
    : m_FontResource( nullptr )
{
    if( m_FontResource )
        m_FontResource->RemoveReference( );

    m_FontResource = mesh.m_FontResource;

    // 参照カウンタ加算
    m_FontResource->AddReference( );
}

/*
 *  フォント読み込み
 */
void
aqua::CFont::
Create( int size, int edge_bold, bool anti_aliasing, aqua::FONT_FAMILY_ID family_id )
{
    // フォントリソース退避
    core::CFontResource* font = m_FontResource;

    // フォントマネージャからフォント取得
    m_FontResource = core::CFontManager::GetInstance( ).Create( size, edge_bold, anti_aliasing, family_id );

    if( font )
    {
        int count = font->RemoveReference( );

        // 前のフォントの参照カウンタがなくなったら解放
        if( count <= 0 )
            core::CFontManager::GetInstance( ).Delete( font );
    }
}

/*
 *  フォント解放
 */
void
aqua::CFont::
Delete( void )
{
    // フォント解放
    if( m_FontResource )
        core::CFontManager::GetInstance( ).Delete( m_FontResource );

    m_FontResource = nullptr;
}

/*
 *  代入演算子のオーバーロード
 */
aqua::CFont&
aqua::CFont::
operator=( const aqua::CFont& font )
{
    // フォントを持っていたら参照を減算
    if( m_FontResource )
        m_FontResource->RemoveReference( );

    m_FontResource = font.m_FontResource;

    // 参照カウンタ加算
    m_FontResource->AddReference( );

    return *this;
}
