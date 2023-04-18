
/*!
 *  @file       aqua.cpp
 *  @brief      AQUA Game Library
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "aqua.h"

/*
 *  ライブラリセットアップ
 */
void
aqua::
Setup( HINSTANCE instance_handle, aqua::IGameObject* game )
{
    // メモリリーク検知
    AQUA_CHECK_MEMORY_LEAK;

    // ゲームフレームワーク取得
    aqua::core::CFramework& framework = aqua::core::CFramework::GetInstance( );

    // ゲームフレームワーク初期化
    framework.Initialize( instance_handle, game );

    // ゲームフレームワーク更新
    framework.Update( );

    // ゲームフレームワーク解放
    framework.Finalize( );
}

/*
 *  インスタンスハンドル取得
 */
HINSTANCE
aqua::
GetInstanceHandle( void )
{
    return aqua::core::CFramework::GetInstance( ).GetInstanceHandle( );
}

/*
 *  ウィンドウハンドル取得
 */
HWND
aqua::
GetWindowHandle( void )
{
    return aqua::core::CFramework::GetInstance( ).GetWindowHandle( );
}

/*
 *  ウィンドウの横幅取得
 */
unsigned int
aqua::
GetWindowWidth( void )
{
    return aqua::core::CFramework::GetInstance( ).GetWindowWidth( );
}

/*
 *  ウィンドウの縦幅取得
 */
unsigned int
aqua::
GetWindowHeight( void )
{
    return aqua::core::CFramework::GetInstance( ).GetWindowHeight( );
}

/*
 *  デルタタイム取得
 */
float
aqua::
GetDeltaTime( void )
{
    return aqua::core::CFramework::GetInstance( ).GetDeltaTime( );
}

/*
 *  デルタタイム(倍率なし)取得
 */
float
aqua::
GetUnscaledDeltaTime( void )
{
    return aqua::core::CFramework::GetInstance( ).GetUnscaledDeltaTime( );
}

/*
 *  デルタタイム倍率取得
 */
float
aqua::
GetDeltaTimeScale( void )
{
    return aqua::core::CFramework::GetInstance( ).GetDeltaTimeScale( );
}

/*
 *  デルタタイム倍率設定
 */
void
aqua::
SetDeltaTimeScale( float scale )
{
    aqua::core::CFramework::GetInstance( ).SetDeltaTimeScale( scale );
}

/*
 *  フレームレート設定
 */
void
aqua::
SetFrameRate( int frame_rate )
{
    aqua::core::CFramework::GetInstance( ).SetFrameRate( frame_rate );
}

/*
 *  ゲームオブジェクトの検索
 */
aqua::IGameObject*
aqua::
FindGameObject( const std::string& name )
{
    return aqua::core::CFramework::GetInstance( ).FindGameObject( name );
}

/*
 *  ゲームオブジェクトの検索
 */
aqua::IGameObject*
aqua::
FindGameObject( aqua::FIND_METHOD func )
{
    return aqua::core::CFramework::GetInstance( ).FindGameObject( func );
}

/*
 *  画面のクリア
 */
void
aqua::
Clear( unsigned int color )
{
    // 画面の背景色を設定
    SetBackgroundColor( ( ( color & 0x00ff0000 ) >> 16 ), ( ( color & 0x0000ff00 ) >> 8 ), ( color & 0x000000ff ) );

    // 画面のクリア
    ClearDrawScreen( );
}
