
/*!
*  @file       video_player.cpp
*  @brief      ビデオプレイヤー
*  @author     Kazuya Maruyama
*  @date       2021/03/10
*  @version    7.17
*
*  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
*/

#include <DxLib.h>
#include "video_player.h"
#include "..\..\framework\framework.h"
#include "..\..\utility\memory\memory.h"

/*
 *  コンストラクタ
 */
aqua::CVideoPlayer::
CVideoPlayer( void )
    : m_PlayFlag( false )
    , position( CVector2::ZERO )
{
}

/*
 *  読み込み
 */
void
aqua::CVideoPlayer::
Create( const std::string& file_name )
{
    Delete( );

    m_Video.Load( file_name );
}

/*
 *  解放
 */
void
aqua::CVideoPlayer::
Delete( void )
{
    m_Video.Unload( );
}

/*
 *  描画
 */
void
aqua::CVideoPlayer::
Draw( void )
{
    // ビデオが読み込まれていなければ描画しない
    if( !m_Video.IsEnable( ) ) return;

    // 非表示の時は描画しない
    if( !visible ) return;

    // 描画
    DrawExtendGraph( (int)position.x, (int)position.y, aqua::core::CFramework::GetInstance( ).GetWindowWidth( ), aqua::core::CFramework::GetInstance( ).GetWindowHeight( ), m_Video.GetResourceHandle( ), FALSE ) ;
}

/*
 *  再生
 */
void
aqua::CVideoPlayer::
Play( void )
{
    if( m_PlayFlag ) return;

    m_PlayFlag = true;

    PlayMovieToGraph( m_Video.GetResourceHandle( ) );
}

/*
 *  停止
 */
void
aqua::CVideoPlayer::
Stop( void )
{
    if( !m_PlayFlag ) return;

    m_PlayFlag = false;

    // 画面を一時停止
    PauseMovieToGraph( m_Video.GetResourceHandle( ) );

    // 動画の再生位置を先頭に戻す
    SeekMovieToGraph(m_Video.GetResourceHandle(), 0);
}

/*
 *  一時停止
 */
void
aqua::CVideoPlayer::
Pause(void)
{
    if (!m_PlayFlag) return;

    m_PlayFlag = false;

    // 画面を一時停止
    PauseMovieToGraph(m_Video.GetResourceHandle());
}

/*
 *  終了判定
 */
bool
aqua::CVideoPlayer::
Finished( void )
{
    if( !m_PlayFlag ) return true;

    return ( !GetMovieStateToGraph( m_Video.GetResourceHandle( ) ) );
}

/*
 *  リソースハンドル取得
 */
int
aqua::CVideoPlayer::
GetResourceHandle( void ) const
{
    return m_Video.GetResourceHandle( );
}
