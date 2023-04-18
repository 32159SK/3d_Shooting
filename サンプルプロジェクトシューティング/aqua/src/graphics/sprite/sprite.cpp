
/*!
 *  @file       sprite.cpp
 *  @brief      2Dテクスチャ描画クラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "sprite.h"
#include "..\..\debug\debug.h"

/*
 *  コンストラクタ
 */
aqua::CSprite::
CSprite( void )
    : position( CVector2::ZERO )
    , rect( CRect::ZERO )
    , anchor( CVector2::ZERO )
    , scale( CVector2::ONE )
    , rotation( 0.0f )
    , color( aqua::CColor::WHITE )
    , blend_mode( aqua::ALPHABLEND::ALPHA )
    , m_GraphicFilter( aqua::GRAPHIC_FILTER::NONE )
    , m_GaussFilterPixelWitdh( 0 )
    , m_GaussFilterParam( 0 )
{
}

/*
 *  生成
 */
void
aqua::CSprite::
Create( const std::string& file_name )
{
    Delete();

    m_Texture.Load( file_name );

    // 読み込み範囲を設定
    rect.left   = 0;
    rect.top    = 0;
    rect.right  = m_Texture.GetWidth( );
    rect.bottom = m_Texture.GetHeight( );
}

/*
 *  生成
 */
void
aqua::CSprite::
Create( const CSurface& surface )
{
    Delete();

    m_Texture = surface.m_Texture;

    // 読み込み範囲を設定
    rect.left   = 0;
    rect.top    = 0;
    rect.right  = m_Texture.GetWidth( );
    rect.bottom = m_Texture.GetHeight( );
}

/*
 *  解放
 */
void
aqua::CSprite::
Delete( void )
{
    m_Texture.Unload( );
}

/*
 *  描画
 */
void
aqua::CSprite::
Draw( void )
{
    // テクスチャが読み込まれていなければ描画しない
    if( !m_Texture.IsEnable( ) ) return;

    // 非表示の時は描画しない
    if( !visible ) return;

    // アルファブレンド設定
    SetDrawBlendMode((int)blend_mode, color.alpha );

    // 輝度設定
    SetDrawBright( color.red, color.green, color.blue );

    // テクスチャリソースハンドル取得
    int handle = m_Texture.GetResourceHandle( );

    switch( m_GraphicFilter )
    {
    case aqua::GRAPHIC_FILTER::GAUSS:
        {
            // 空のスクリーンを作成
            handle = MakeScreen( m_Texture.GetWidth( ), m_Texture.GetHeight( ), true );

            GraphFilterBlt( m_Texture.GetResourceHandle( ), handle, DX_GRAPH_FILTER_GAUSS, m_GaussFilterPixelWitdh, m_GaussFilterParam );
        }
        break;
    }

    // 描画
    DrawRectRotaGraph3F( position.x + anchor.x, position.y + anchor.y, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, anchor.x, anchor.y, scale.x, scale.y, rotation, handle, TRUE );

    // 輝度をデフォルトに戻す
    SetDrawBright( aqua::CColor::MAX_COLOR, aqua::CColor::MAX_COLOR, aqua::CColor::MAX_COLOR );

    // アルファブレンドモードをデフォルトに戻す
    SetDrawBlendMode((int)aqua::ALPHABLEND::ALPHA, aqua::CColor::MAX_COLOR );

    // ハンドルを削除
    if( m_GraphicFilter != aqua::GRAPHIC_FILTER::NONE && handle != AQUA_DX_ERROR )
        DeleteGraph( handle );
}

/*
 *  ガウスフィルターの適用
 */
void
aqua::CSprite::
ApplyGaussFilter( int pixel_width, int param )
{
    m_GraphicFilter = aqua::GRAPHIC_FILTER::GAUSS;

    m_GaussFilterPixelWitdh = pixel_width;

    m_GaussFilterParam = param;
}

/*
 *  グラフィックフィルターの解除
 */
void
aqua::CSprite::
UnsetGraphicFilter( void )
{
    m_GraphicFilter = aqua::GRAPHIC_FILTER::NONE;
}
