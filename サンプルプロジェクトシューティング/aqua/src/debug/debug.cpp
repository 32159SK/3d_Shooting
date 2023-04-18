
/*!
 *  @file       debug.cpp
 *  @brief      デバッグ
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "debug.h"
#include "..\framework\framework.h"
#include "..\controls\controls.h"
#include <iomanip>
#include <string>
#include <sstream>

#ifdef AQUA_DEBUG

const unsigned int      aqua::core::CVisualDebugger::m_background_color                 = 0xee000000;
const char*             aqua::core::CVisualDebugger::m_debug_log_file_name              = "aqua_debug_log.txt";
const int               aqua::core::CVisualDebugger::m_max_show_debug_log               = 30;
const unsigned int      aqua::core::CVisualDebugger::m_debug_text_color                 = 0xff00ff00;
const unsigned int      aqua::core::CVisualDebugger::m_debug_text_edge_color            = 0xff004000;
const int               aqua::core::CVisualDebugger::m_max_debug_command                = 9;
const int               aqua::core::CVisualDebugger::m_debug_command_width              = 290;
const float             aqua::core::CVisualDebugger::m_default_delta_time_scale         = 1.0f;
const float             aqua::core::CVisualDebugger::m_min_delta_time_scale             = 0.1f;
const float             aqua::core::CVisualDebugger::m_max_delta_time_scale             = 2.0f;
const float             aqua::core::CVisualDebugger::m_change_delta_time_scale          = 0.1f;
const int               aqua::core::CVisualDebugger::m_delta_time_scale_input_interval  = 4;
const char*             aqua::core::CVisualDebugger::m_debug_command_names[] =
{
    "[F1]ヘルプの表示/非表示",
    "[F2]デバッグ用DTS減算",
    "[F3]デバッグ用DTS加算",
    "[F4]デバッグ用DTSリセット",
    "[F5]ゲームのリセット",
    "[F6]FPSの表示/非表示",
    "[F7]一時停止/再開",
    "[F8]デバッグログの表示/非表示",
    "[F9]スクリーンショットの撮影", 
};

/*
 *  インスタンスの取得
 */
aqua::core::CVisualDebugger&
aqua::core::CVisualDebugger::
GetInstance( void )
{
    static CVisualDebugger instance;

    return instance;
}

/*
 *  初期化
 */
void
aqua::core::CVisualDebugger::
Initialize( void )
{
    // デバッグログをクリア
    m_DebugLogList.clear( );

    // 書き出しモードで開く
    fopen_s( &m_DebugLogFile, m_debug_log_file_name, "w" );

    // すぐに閉じてファイルの中身を空にする
    if(m_DebugLogFile)
        fclose( m_DebugLogFile );

    m_DebugLogFile = nullptr;

    // 追記モードで開き直す
    fopen_s( &m_DebugLogFile, m_debug_log_file_name, "a" );
}

/*
 *  更新
 */
void
aqua::core::CVisualDebugger::
Update( void )
{
    // ヘルプの表示切り替え
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::F1))
        m_ShowDebugHelp = !m_ShowDebugHelp;

    // デルタタイムスケールの変更
    if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::F2))
    {
        if( --m_DeltaTimeScaleInputTime < 0 )
        {
            m_DeltaTimeScaleInputTime = m_delta_time_scale_input_interval;

            m_DebugDeltaTimeScale -= m_change_delta_time_scale;

            if (m_DebugDeltaTimeScale < m_min_delta_time_scale)
                m_DebugDeltaTimeScale = m_min_delta_time_scale;
        }
    }
    else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::F3))
    {
        if( --m_DeltaTimeScaleInputTime < 0 )
        {
            m_DeltaTimeScaleInputTime = m_delta_time_scale_input_interval;

            m_DebugDeltaTimeScale += m_change_delta_time_scale;

            if (m_DebugDeltaTimeScale > m_max_delta_time_scale)
                m_DebugDeltaTimeScale = m_max_delta_time_scale;
        }
    }
    else
    {
        m_DeltaTimeScaleInputTime = 0;
    }

    // デルタタイムスケールのリセット
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::F4))
    {
        m_DebugDeltaTimeScale = m_default_delta_time_scale;
    }

    // ゲームのオールリセット
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::F5))
        core::CFramework::GetInstance( ).Reset( );

    // FPSの表示切り替え
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::F6))
        m_ShowDebugFPS = !m_ShowDebugFPS;

    // ポーズ処理
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::F7))
        m_DebugPauseFlag = !m_DebugPauseFlag;


    // デバッグログの表示切替
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::F8))
        m_ShowDebugLog = !m_ShowDebugLog;
}

/*
 *  描画
 */
void
aqua::core::CVisualDebugger::
Draw( void )
{
    core::CFramework& framework = core::CFramework::GetInstance( );

    // ヘルプの表示
    if (m_ShowDebugHelp)
    {
        for( int i = 0; i < m_max_debug_command; ++i )
            DrawString( framework.GetWindowWidth( ) - m_debug_command_width, i * GetFontSize( ), m_debug_command_names[i], m_debug_text_color, m_debug_text_edge_color );
    }

    // FPSの表示
    if (m_ShowDebugFPS)
    {
        std::stringstream fps;

        fps << "[FPS]" << std::fixed << std::setprecision(2) << core::CFramework::GetInstance().GetFPS( );

        int x = framework.GetWindowWidth() - GetDrawStringWidth(fps.str().c_str(), (int)fps.str().length());

        DrawString(x, framework.GetWindowHeight( ) - GetFontSize( ) * 3, fps.str().c_str(), m_debug_text_color, m_debug_text_edge_color);

        std::stringstream dlt;

        dlt << "[DLT]" << std::fixed << std::setprecision(3) << core::CFramework::GetInstance().GetDeltaTime( );

        DrawString(x, framework.GetWindowHeight( ) - GetFontSize( ) * 2, dlt.str().c_str(), m_debug_text_color, m_debug_text_edge_color);

        std::stringstream dts;

        dts << "[DTS]" << std::fixed << std::setprecision(1) << m_DebugDeltaTimeScale;

        DrawString(x, framework.GetWindowHeight( ) - GetFontSize( ), dts.str().c_str(), m_debug_text_color, m_debug_text_edge_color);
    }

    // ポーズの表示
    if (m_DebugPauseFlag)
    {
        const std::string pause = "[PAUSE]";

        int x = framework.GetWindowWidth( ) / 2 - GetDrawStringWidth(pause.c_str(), (int)pause.length()) / 2;

        DrawString( x, 0, pause.c_str(), m_debug_text_color, m_debug_text_edge_color );
    }

    // デバッグログの表示
    if (m_ShowDebugLog)
    {
        DrawString( 0, 0, "[DEBUG_LOG]", m_debug_text_color, m_debug_text_edge_color );

        if( m_DebugLogList.empty( ) ) return;

        auto it  = m_DebugLogList.begin( );
        auto end = m_DebugLogList.end( );

        for( int i = 0; it != end; ++it, ++i )
            DrawString( 0, i * GetFontSize( ) + GetFontSize( ), (*it).c_str( ), m_debug_text_color, m_debug_text_edge_color );
    }
}

/*
 *  解放
 */
void
aqua::core::CVisualDebugger::
Finalize( void )
{
    fclose( m_DebugLogFile );

    m_DebugLogFile = nullptr;
}

/*
 *  アサート処理
 */
void
aqua::core::CVisualDebugger::
VisualAssert( bool result, const std::string& message, const std::string& file, int line )
{
    if( result ) return;

    aqua::core::CFramework& framework = aqua::core::CFramework::GetInstance();

    int width  = framework.GetWindowWidth( );
    int height = framework.GetWindowHeight( );

    // アルファブレンド設定
    SetDrawBlendMode( DX_BLENDMODE_ALPHA, ( m_background_color & 0xff000000 ) >> 24 );

    // 背景描画
    DrawBox( 0, 0, width, height, m_background_color, TRUE );

    // アルファブレンドを戻す
    SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

    // 描画メッセージの作成
    std::string t = "[ASSERT] " + message + "\n[ FILE ] " + file.substr( file.rfind( "\\" ) + 1 ) + "\n[ LINE ] " + std::to_string( line );

    // エラーメッセージの描画
    DrawString( 0, 0, t.c_str( ), m_debug_text_color, m_debug_text_edge_color );

    // 画面を更新
    ScreenFlip( );

    // メッセージを検知
    while( ProcessMessage( ) != AQUA_DX_ERROR )
    {
        // Escキーで終了
        if( CheckHitKey( KEY_INPUT_ESCAPE ) == TRUE )
            break;
    }

    // ライブラリの解放
    aqua::core::CFramework::GetInstance().Finalize();

    // アプリケーションの終了
    exit( -1 );
}

/*
 *  デバッグログ
 */
void
aqua::core::CVisualDebugger::
DebugLog( const std::string& text )
{

    // 表示の最大数を越えていたら先頭をポップ
    if ( m_DebugLogList.size() > m_max_show_debug_log )
        m_DebugLogList.pop_front( );

    m_DebugLogList.push_back( text );

    std::string t = text + "\n";

    // デバッグログファイルに追記する
    fwrite( t.c_str( ), t.length( ), 1, m_DebugLogFile );
}

/*
 *  デバッグ用デルタタイムスケール取得
 */
float
aqua::core::CVisualDebugger::
GetDebugDeltaTimeScale( void ) const
{
    return m_DebugDeltaTimeScale;
}

/*
 *  ポーズフラグ取得
 */
bool
aqua::core::CVisualDebugger::
GetDebugPauseFlag( void )
{
    return m_DebugPauseFlag;
}

/*
 *  コンストラクタ
 */
aqua::core::CVisualDebugger::
CVisualDebugger( void )
    : m_DebugLogFile( nullptr )
    , m_ShowDebugFPS( true )
    , m_ShowDebugHelp( false )
    , m_ShowDebugLog( false )
    , m_DebugPauseFlag( false )
    , m_DebugDeltaTimeScale( m_default_delta_time_scale )
    , m_DeltaTimeScaleInputTime( 0 )
{
    m_DebugLogList.clear( );
}

/*
 *  コピーコンストラクタ
 */
aqua::core::CVisualDebugger::
CVisualDebugger( const CVisualDebugger& rhs )
    : m_DebugLogFile(nullptr)
    , m_ShowDebugFPS(true)
    , m_ShowDebugHelp(false)
    , m_ShowDebugLog(false)
    , m_DebugPauseFlag(false)
    , m_DebugDeltaTimeScale(m_default_delta_time_scale)
    , m_DeltaTimeScaleInputTime(0)
{
    (void)rhs;
}

/*
 *  代入演算子
 */
aqua::core::CVisualDebugger&
aqua::core::CVisualDebugger::
operator=( const CVisualDebugger& rhs )
{
    (void)rhs;

    return *this;
}

#endif
