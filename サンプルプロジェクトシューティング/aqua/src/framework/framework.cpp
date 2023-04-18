
/*!
 *  @file       framework.cpp
 *  @brief      フレームワーク
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma comment( lib, "imm32.lib" )
#pragma comment( lib, "Shlwapi.lib" )

#include <windows.h>
#include <imm.h>
#include <time.h>
#include <shlwapi.h>
#include <string>
#include <sstream>
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "framework.h"
#include "..\debug\debug.h"
#include "..\graphics\graphics.h"
#include "..\game_object\game_object.h"
#include "..\controls\controls.h"
#include "..\sounds\sounds.h"

const char*         aqua::core::CFramework::m_class_name                = "AQUA GAME LIBRARY 7.17";
const unsigned int  aqua::core::CFramework::m_width                     = 1280;
const unsigned int  aqua::core::CFramework::m_height                    = 720;
const int           aqua::core::CFramework::m_color_bit                 = 32;
const float         aqua::core::CFramework::m_one_millisecond           = 1000.0f;
const float         aqua::core::CFramework::m_max_delta_time            = 0.16f;
const float         aqua::core::CFramework::m_default_delta_time_scale  = 1.0f;
const int           aqua::core::CFramework::m_default_frame_rate        = 60;
const int           aqua::core::CFramework::m_calc_frame_count          = 60;
const int           aqua::core::CFramework::m_max_effekseer_particle    = 5000;

/*
 *  インスタンスの取得
 */
aqua::core::CFramework&
aqua::core::CFramework::
GetInstance( void )
{
    static CFramework instance;

    return instance;
}

/*
 *  初期化
 */
void
aqua::core::CFramework::
Initialize( HINSTANCE instance_handle, aqua::IGameObject* game )
{
    // インスタンスハンドル登録
    m_hInstance = instance_handle;

    // IMEを禁止する
    ImmDisableIME( 0xffffffff );

    // 乱数の初期化
    srand( (unsigned int)time( NULL ) );

    // 入力処理関係初期化
    aqua::core::CKeyboard::GetInstance( ).Initialize( );
    aqua::core::CMouse::GetInstance( ).Initialize( );
    aqua::core::CController::GetInstance( ).Initialize( );

    // Log.txtを生成しない
    SetOutApplicationLogValidFlag( FALSE );

    // ウィンドウが非アクティブ時も更新する
    SetAlwaysRunFlag( TRUE );

    // ウィンドウテキストの変更
    SetMainWindowText( m_class_name );

    // バックバッファサイズ指定
    SetGraphMode( m_width, m_height, m_color_bit );

    // ウィンドウサイズ指定
    SetWindowSize( m_width, m_height );

#ifdef AQUA_DEBUG
    // ウィンドウモードで起動
    ChangeWindowMode( TRUE );
#else
    // フルスクリーンモードで起動
    ChangeWindowMode( FALSE );

    // ゲーム画面の解像度に合わせてフルスクリーンにする
    SetFullScreenResolutionMode( DX_FSRESOLUTIONMODE_NATIVE );
#endif

    // DirectX11のバージョンを指定する
    if( SetUseDirect3DVersion( DX_DIRECT3D_11 ) == AQUA_DX_ERROR )
        return;

    // DXライブラリ初期化
    if( DxLib_Init( ) == AQUA_DX_ERROR )
        return;

    // Effekseer初期化
    if( Effkseer_Init( m_max_effekseer_particle ) == AQUA_DX_ERROR )
    {
        DxLib_End( );

        return;
    }

    // フルスクリーンウィンドウ切り替え時にリソースが消えるのを防ぐ
    SetChangeScreenModeGraphicsSystemResetFlag( FALSE );

    // DXライブラリのデバイスロストした時のコールバックを設定
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    // Effekseerに2D描画を設定する
    Effekseer_Set2DSetting(m_width, m_height);

    // Zバッファの有効化
    SetUseZBuffer3D( TRUE );

    // Zバッファへの書き込みを有効化
    SetWriteZBuffer3D( TRUE );

#ifdef AQUA_DEBUG
    CVisualDebugger::GetInstance().Initialize();
#endif

    // バックバッファに書き込む
    SetDrawScreen( DX_SCREEN_BACK );

    // デフォルトフォントをエッジ付きに設定する
    ChangeFontType( DX_FONTTYPE_EDGE );

    AQUA_ASSERT( game, "ゲームオブジェクトを引き渡してください。" );

    // ゲームオブジェクトノード設定
    m_GameNode = game;

    // ゲームオブジェクトノード初期化
    m_GameNode->Initialize( );
}

/*
 *  更新
 */
void
aqua::core::CFramework::
Update( void )
{
    // Windowsからの命令を処理
    while( ProcessMessage( ) != AQUA_DX_ERROR )
    {
        // フレームカウント算出
        CalcFrameCount( );

        // ゲーム処理
        GameProcess( );

        // フレーム同期
        FrameSync( );

        // Escキーで終了
        if( CheckHitKey( KEY_INPUT_ESCAPE ) == TRUE )
            break;
    }
}

/*
 *  解放
 */
void
aqua::core::CFramework::
Finalize( void )
{
#ifdef AQUA_DEBUG
    CVisualDebugger::GetInstance().Finalize();
#endif

    // ゲームオブジェクトノード解放
    m_GameNode->Finalize( );

    // メモリ解放
    AQUA_SAFE_DELETE( m_GameNode );

    // テクスチャの全解放
    aqua::core::CTextureManager::GetInstance( ).Clear( );

    // サウンド全解放
    aqua::core::CSoundManager::GetInstance().Clear();

    // 入力処理関係解放
    aqua::core::CController::GetInstance( ).Finalize( );
    aqua::core::CKeyboard::GetInstance( ).Finalize( );

    // マスク画面を削除する
    DeleteMaskScreen();

    // Effekseer解放
    Effkseer_End( );

    // DXライブラリ解放
    DxLib_End( );
}

/*
 *  リセット
 */
void
aqua::core::CFramework::
Reset( void )
{
    m_GameNode->Finalize( );

    m_GameNode->Initialize( );
}

/*
 *  デルタタイム取得
 */
float
aqua::core::CFramework::
GetDeltaTime( void ) const
{
#ifdef AQUA_DEBUG
    return m_DeltaTime * m_DeltaTimeScale * core::CVisualDebugger::GetInstance( ).GetDebugDeltaTimeScale( );
#else
    return m_DeltaTime * m_DeltaTimeScale;
#endif
}

/*
 *  デルタタイム倍率取得
 */
float
aqua::core::CFramework::
GetDeltaTimeScale(void) const
{
#ifdef AQUA_DEBUG
    return m_DeltaTimeScale * core::CVisualDebugger::GetInstance().GetDebugDeltaTimeScale();
#else
    return m_DeltaTimeScale;
#endif
}

/*
 *  ゲームオブジェクトの検索
 */
aqua::IGameObject*
aqua::core::CFramework::
FindGameObject( const std::string& name )
{
    if( !m_GameNode ) return nullptr;

    return m_GameNode->FindChild( name );
}

/*
 *  ゲームオブジェクトの検索
 */
aqua::IGameObject*
aqua::core::CFramework::
FindGameObject( aqua::FIND_METHOD func )
{
    if( !m_GameNode ) return nullptr;

    return m_GameNode->FindChild( func );
}

/*
 *  コンストラクタ
 */
aqua::core::CFramework::
CFramework( void )
    : m_hInstance( NULL )
    , m_hWindow( NULL )
    , m_WindowMode( true )
    , m_GameNode( nullptr )
    , m_FrameRate( m_default_frame_rate )
    , m_FrameCount( 0 )
    , m_Fps( 0.0f )
    , m_DeltaTime( 0.0f )
    , m_StartTime( 0 )
    , m_PrevTime( 0 )
    , m_DeltaTimeScale( m_default_delta_time_scale )
{
}

/*
 *  コピーコンストラクタ
 */
aqua::core::CFramework::
CFramework( const aqua::core::CFramework& rhs )
    : m_hInstance(NULL)
    , m_hWindow(NULL)
    , m_WindowMode(true)
    , m_GameNode(nullptr)
    , m_FrameRate(m_default_frame_rate)
    , m_FrameCount(0)
    , m_Fps(0.0f)
    , m_DeltaTime(0.0f)
    , m_StartTime(0)
    , m_PrevTime(0)
    , m_DeltaTimeScale(m_default_delta_time_scale)

{
    (void)rhs;
}

/*
 *  代入演算子
 */
aqua::core::CFramework&
aqua::core::CFramework::
operator=( const aqua::core::CFramework& rhs )
{
    (void)rhs;

    return *this;
}

/*
 *  更新するフレームカウントの計算
 */
void
aqua::core::CFramework::
CalcFrameCount( void )
{
    // 現在の時間を取得
    int now_time = GetNowCount( );

    // 計算開始時
    if( m_FrameCount == 0 )
    {
        m_StartTime = now_time;
    }
    // 指定されたフレームカウント時
    else if( m_FrameCount == m_calc_frame_count )
    {
        // フレームの平均を算出してFPSを求める
        m_Fps = m_one_millisecond / ( ( now_time - m_StartTime ) / (float)m_calc_frame_count );

        m_FrameCount = 0;

        m_StartTime = now_time;
    }

    // フレームカウントを更新
    ++m_FrameCount;

    // 前の処理との時間の差
    int sub_time = now_time - m_PrevTime;

    // デルタタイムを算出
    m_DeltaTime = (float)sub_time / m_one_millisecond;

    // 最大デルタタイムで制限する
    if( m_DeltaTime > m_max_delta_time )
        m_DeltaTime = m_max_delta_time;

    // 今の時間を保存
    m_PrevTime = now_time;
}

/*
 *  更新フレームの待機処理
 */
void
aqua::core::CFramework::
FrameSync( void )
{
    // 今とフレーム計測開始時の差を算出
    int tookTime = GetNowCount( ) - m_StartTime;

    // 待機時間を算出
    int waitTime = m_FrameCount * (int)m_one_millisecond / m_FrameRate - tookTime;

    // 待機時間があればその分待って同期する
    if( waitTime > 0 )
        WaitTimer( waitTime );
}

/*
 *  ゲームプロセス実行
 */
void
aqua::core::CFramework::
GameProcess( void )
{
    // 入力処理関係更新
    aqua::core::CKeyboard::GetInstance( ).Update( );
    aqua::core::CMouse::GetInstance( ).Update( );
    aqua::core::CController::GetInstance( ).Update( );

    // サウンド処理更新
    CSoundManager::GetInstance( ).Update( );

#ifdef AQUA_DEBUG
    // ビジュアルデバッガー取得
    core::CVisualDebugger& debug = core::CVisualDebugger::GetInstance( );

    // デバッグ更新・入力処理
    debug.Update( );

    // ゲーム更新
    if( !debug.GetDebugPauseFlag( ) )
        m_GameNode->Update();
#else
    // ゲーム更新
    m_GameNode->Update( );
#endif

#ifdef AQUA_DEBUG
    // デバッグモードに合わせて、エフェクトをすべてポーズする
    GetEffekseer2DManager()->SetPausedToAllEffects(debug.GetDebugPauseFlag());
#endif

    // Effekseer更新
    UpdateEffekseer2D();

#ifdef AQUA_DEBUG
    // ゲーム描画
    if (!debug.GetDebugPauseFlag())
        m_GameNode->Draw( );
#else
    // ゲーム描画
    m_GameNode->Draw();
#endif

    // スクリーンショットの撮影
    // Debug時の情報を写さないようにこのタイミングで行う
    if( aqua::keyboard::Trigger( aqua::keyboard::KEY_ID::F9 ) )
        ScreenShot( );

#ifdef AQUA_DEBUG
    // デバッグ描画処理
    debug.Draw( );
#endif

    // バックバッファの転送
    ScreenFlip( );
}

/*
 *  スクリーンショットの撮影
 */
void
aqua::core::CFramework::
ScreenShot( void )
{
    DATEDATA dd;

    // 現在の時間取得
    GetDateTime( &dd ) ;

     // フォルダの有無チェック
    // なければ作成
    if( !PathIsDirectory( "capture" ) )
        CreateDirectory( "capture", NULL );

    // 日付をファイル名にする
    std::string file_name = "capture\\";

    file_name += std::to_string( dd.Year ) + std::to_string( dd.Mon ) + std::to_string( dd.Day ) + "_";

    file_name += std::to_string( dd.Hour ) + std::to_string( dd.Min ) + std::to_string( dd.Sec ) + ".bmp";

    // スクリーンショットの書き出し
    SaveDrawScreenToBMP( 0, 0, m_width, m_height, file_name.c_str( ));
}
