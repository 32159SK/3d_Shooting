
/*!
 *  @file       font_resource.cpp
 *  @brief      フォントリソース
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include <DxLib.h>
#include "font_resource.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"

const std::string    aqua::core::CFontResource::m_font_family_table[] =
{
    "メイリオ",
    "ＭＳ ゴシック",
    "ＭＳ 明朝",
    "HG行書体",
    "HG創英角ﾎﾟｯﾌﾟ体",
    "游ゴシック",
    "游明朝",
};

const int           aqua::core::CFontResource::m_default_font_size = 10;

/*
 *  コンストラクタ
 */
aqua::core::CFontResource::
CFontResource( void )
    : IResourceObject( aqua::core::RESOURCE_TYPE::CREATE_FONT )
    , m_FontSize( m_default_font_size )
    , m_FontFamilyID( FONT_FAMILY_ID::MEIRIO )
    , m_EdgeBold( 0 )
{
}

/*
 *  生成
 */
void
aqua::core::CFontResource::
Create( int size, int edge_bold, bool anti_aliasing, aqua::FONT_FAMILY_ID family_id )
{
    if( m_Enabel ) return;

    // フォント生成
    // エッジの有無
    if ( edge_bold > 0 )
        if ( anti_aliasing )
            m_ResourceHandle = CreateFontToHandle(m_font_family_table[(int)family_id].c_str(), size, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, edge_bold);
        else
            m_ResourceHandle = CreateFontToHandle(m_font_family_table[(int)family_id].c_str(), size, -1, DX_FONTTYPE_EDGE, -1, edge_bold);
    else
        if ( anti_aliasing )
            m_ResourceHandle = CreateFontToHandle(m_font_family_table[(int)family_id].c_str(), size, -1, DX_FONTTYPE_ANTIALIASING_8X8);
        else
            m_ResourceHandle = CreateFontToHandle(m_font_family_table[(int)family_id].c_str(), size, -1, DX_FONTTYPE_NORMAL);

    AQUA_DX_ASSERT( m_ResourceHandle, "フォントの作成に失敗しました。" );

    // 生成したフォントタイプ
    m_ResourceType = RESOURCE_TYPE::CREATE_FONT;

    m_FontSize      = size;
    m_FontFamilyID  = family_id;
    m_EdgeBold      = edge_bold;

    // 生成済み
    m_Enabel = true;
}

/*
 *  削除
 */
void
aqua::core::CFontResource::
Delete( void )
{
    // フォント削除
    DeleteFontToHandle( m_ResourceHandle );

    m_FontSize          = m_default_font_size;
    m_FontFamilyID      = FONT_FAMILY_ID::MEIRIO;
    m_EdgeBold          = 0;
    m_ResourceHandle    = AQUA_UNUSED_HANDLE;
    m_ReferenceCount    = 0;
    m_ResourceType      = RESOURCE_TYPE::DUMMY;
    m_Enabel            = false;
}

/*
 *  フォントの比較
 */
bool
aqua::core::CFontResource::
CheckFont( aqua::core::CFontResource* font )
{
    return CheckFont( font->m_FontSize, font->m_EdgeBold, font->m_FontFamilyID );
}

/*
 *  フォントの比較
 */
bool
aqua::core::CFontResource::
CheckFont( int size, int edge_bold, FONT_FAMILY_ID famiry_id )
{
    return ( m_FontSize == size && m_EdgeBold == edge_bold && m_FontFamilyID == famiry_id );
}

/*
 *  使用禁止
 */
void
aqua::core::CFontResource::
Load( const std::string& file_name )
{
    (void)file_name;
}

/*
 *  使用禁止
 */
void
aqua::core::CFontResource::
Unload( void )
{
}
