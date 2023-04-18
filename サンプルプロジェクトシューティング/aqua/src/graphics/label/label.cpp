
/*!
 *  @file       label.cpp
 *  @brief      文字列描画クラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "label.h"
#include "..\..\debug\debug.h"

/*
 *  コンストラクタ
 */
aqua::CLabel::
CLabel( void )
    : position( CVector2::ZERO )
    , color( CColor::WHITE )
    , edge_color( CColor::BLACK )
    , blend_mode( aqua::ALPHABLEND::ALPHA )
{
    text.clear( );
}

/*
 *  生成
 */
void
aqua::CLabel::
Create( int size )
{
    Create( size, 0 );
}

/*
 *  生成
 */
void
aqua::CLabel::
Create( int size, int edge_bold )
{
    m_Font.Create( size, edge_bold, false, aqua::FONT_FAMILY_ID::MS_GOTHIC );
}

/*
 *  生成
 */
void
aqua::CLabel::
Create(int size, int edge_bold, bool anti_aliasing)
{
    m_Font.Create(size, edge_bold, anti_aliasing, aqua::FONT_FAMILY_ID::MS_GOTHIC);
}

/*
 *  生成
 */
void
aqua::CLabel::
Create( int size, int edge_bold, bool anti_aliasing, aqua::FONT_FAMILY_ID family_id )
{
    m_Font.Create( size, edge_bold, anti_aliasing, family_id );
}

/*
 *  描画
 */
void
aqua::CLabel::
Draw( void )
{
    // フォントが生成されていない
    if( !m_Font.IsEnable( ) )
        return;

    // 非表示の時は描画しない
    if( !visible ) return;

    // アルファブレンド設定
    SetDrawBlendMode((int)blend_mode, color.alpha );

    // 文字列描画
    DrawStringToHandle( (int)position.x, (int)position.y, text.c_str( ), color.GetColor( ), m_Font.GetResourceHandle( ), edge_color.GetColor( ) );

    // アルファブレンドモードをデフォルトに戻す
    SetDrawBlendMode((int)aqua::ALPHABLEND::ALPHA, aqua::CColor::MAX_COLOR );
}

/*
 *  削除
 */
void
aqua::CLabel::
Delete( void )
{
    m_Font.Delete( );
}

/*
 *  文字列の幅取得
 */
int
aqua::CLabel::
GetTextWidth( void ) const
{
    return GetDrawStringWidthToHandle( text.c_str( ), (int)text.length( ), m_Font.GetResourceHandle( ) );
}

/*
 *  フォントの高さ取得
 */
int
aqua::CLabel::
GetFontHeight( void ) const
{
    return m_Font.GetHeight( );
}

/*
 *  リソースハンドル取得
 */
int
aqua::CLabel::
GetResourceHandle( void ) const
{
    return m_Font.GetResourceHandle( );
}
