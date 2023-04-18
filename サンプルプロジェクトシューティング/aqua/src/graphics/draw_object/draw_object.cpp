
/*!
 *  @file       draw_object.cpp
 *  @brief      描画オブジェクト登録用インターフェース
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "draw_object.h"
#include "..\..\graphics\graphics.h"

/*
 *  コンストラクタ
 */
aqua::core::IDrawObject::
IDrawObject( void )
    : visible( true )
{
}

/*
 *  更新
 */
void
aqua::core::IDrawObject::
Update( void )
{
}

/*
 *  描画
 */
void
aqua::core::IDrawObject::
Draw( void )
{
}
