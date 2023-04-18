
/*!
 *  @file       box_primitive.cpp
 *  @brief      矩形描画クラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "box_primitive.h"
#include "..\..\..\debug\debug.h"

/*
 *  コンストラクタ
 */
aqua::CBoxPrimitive::
CBoxPrimitive( void )
    : position( CVector2::ZERO )
    , width( 0.0f )
    , height( 0.0f )
    , color( aqua::CColor::WHITE )
    , fill( true )
    , thickness( 1.0f )
    , blend_mode( aqua::ALPHABLEND::ALPHA )
{
}

/*
 *  初期化
 */
void
aqua::CBoxPrimitive::
Setup(const aqua::CVector2& position_, float width_, float height_, const aqua::CColor& color_, bool fill_, float thickness_, aqua::ALPHABLEND blend_mode_)
{
    position      = position_;
    width         = width_;
    height        = height_;
    color         = color_;
    fill          = fill_;
    thickness     = thickness_;
    blend_mode    = blend_mode_;
}

/*
 *  描画
 */
void
aqua::CBoxPrimitive::
Draw( void )
{
    // 非表示の時は描画しない
    if( !visible ) return;

    // アルファブレンド設定
    SetDrawBlendMode((int)blend_mode, color.alpha );

    // 描画
    DrawBoxAA( position.x, position.y, position.x + width, position.y + height, color.GetColor(), ( fill ? TRUE : FALSE ), thickness );

    // アルファブレンドモードをデフォルトに戻す
    SetDrawBlendMode((int)aqua::ALPHABLEND::ALPHA, aqua::CColor::MAX_COLOR );
}
