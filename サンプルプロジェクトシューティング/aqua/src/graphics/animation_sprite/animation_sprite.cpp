
/*!
 *  @file       animation_sprite.cpp
 *  @brief      アニメーション付きスプライトクラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "animation_sprite.h"
#include "..\..\debug\debug.h"
#include "..\..\framework\framework.h"
#include "..\..\utility\json_loader\rapidjson\document.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>

const char*     aqua::CAnimationSprite::m_key_names[] =
{
    "file",
    "frame",
    "width",
    "height",
    "cols",
    "rows",
    "animations",
    "frames",
    "interval",
    "loop",
};

const float     aqua::CAnimationSprite::m_second            = 1.0f;
const int       aqua::CAnimationSprite::m_dummy_anime_id    = -1;

/*
 *  コンストラクタ
 */
aqua::CAnimationSprite::
CAnimationSprite( void )
    : position( CVector2::ZERO )
    , anchor( CVector2::ZERO )
    , scale( CVector2::ONE )
    , rotation( 0.0f )
    , color( aqua::CColor::WHITE )
    , blend_mode( aqua::ALPHABLEND::ALPHA )
    , m_FrameWidth( 0 )
    , m_FrameHeight( 0 )
    , m_FrameCols( 0 )
    , m_FrameRows( 0 )
    , m_CurrentAnimeID( m_dummy_anime_id )
    , m_CurrentFrame( 0.0f )
    , m_CurrentAnimeFPS( 1.0f )
    , m_Rect( CRect::ZERO )
    , m_StopFlag( false )
    , m_PlaySpeedRate( 1.0f )
{
}

/*
 *  生成
 */
void
aqua::CAnimationSprite::
Create( const std::string& file_name )
{
    Create( file_name, 0 );
}

/*
 *  生成
 */
void
aqua::CAnimationSprite::
Create( const std::string& file_name, const std::string& anime_name )
{
    Delete();

    // ASSファイルの読み込みと解析
    LoadASS( file_name );

    // テクスチャ読み込み
    m_Texture.Load( m_FileName );

    // アニメーションを変更
    Change( anime_name );
}

/*
 *  生成
 */
void
aqua::CAnimationSprite::
Create( const std::string& file_name, int anime_id )
{
    Delete();

    // ASSファイルの読み込みと解析
    LoadASS( file_name );

    // テクスチャ読み込み
    m_Texture.Load( m_FileName );

    // アニメーションを変更
    Change( anime_id );
}

/*
 *  解放
 */
void
aqua::CAnimationSprite::
Delete( void )
{
    m_Texture.Unload( );

    m_AnimationList.clear( );

    m_FileName.clear( );

    m_FrameWidth        = 0;
    m_FrameHeight       = 0;
    m_FrameCols         = 0;
    m_FrameRows         = 0;
    m_CurrentAnimeID    = m_dummy_anime_id;
    m_CurrentFrame      = 0.0f;
    m_CurrentAnimeFPS   = 0.0f;
    m_Rect              = CRect::ZERO;
    m_StopFlag          = false;
    m_PlaySpeedRate     = 1.0f;
}

/*
 *  更新
 */
void
aqua::CAnimationSprite::
Update( void )
{
    // アニメーション停止フラグが立っていたら進めない
    if( m_StopFlag ) return;

    // デルタタイム取得
    float delta_time = aqua::core::CFramework::GetInstance().GetDeltaTime();

    // デルタタイムを使ってアニメーションフレームを更新
    // アニメーションの再生速度率も反映
    m_CurrentFrame += m_CurrentAnimeFPS * m_PlaySpeedRate * delta_time;

    // アニメーションの最大フレームを超えていない
    if( m_CurrentFrame < m_AnimationList[m_CurrentAnimeID].frames.size( ) )
        return;

    // ループ設定であればフレームを先頭にもどす
    // そうでなければ最終フレームで固定する
    if( m_AnimationList[m_CurrentAnimeID].loop )
        m_CurrentFrame = 0.0f;
}

/*
 *  描画
 */
void
aqua::CAnimationSprite::
Draw( void )
{
    // テクスチャが読み込まれていなければ描画しない
    if( !m_Texture.IsEnable( ) ) return;

    // 非表示の時は描画しない
    if( !visible ) return;

    // カレントフレームを取得
    int index = (int)m_CurrentFrame;

    // 最大フレームを超えていたら制限
    if( index >= (int)m_AnimationList[m_CurrentAnimeID].frames.size( ) )
        index = (int)m_AnimationList[m_CurrentAnimeID].frames.size() - 1;

    // 指定されたアニメーションから描画範囲を算出
    int frame = m_AnimationList[m_CurrentAnimeID].frames[index];

    m_Rect.left   = ( frame % m_FrameCols ) * m_FrameWidth;
    m_Rect.top    = ( frame / m_FrameCols ) * m_FrameHeight;
    m_Rect.right  = m_Rect.left + m_FrameWidth;
    m_Rect.bottom = m_Rect.top + m_FrameHeight;

    // アルファブレンド設定
    SetDrawBlendMode( (int)blend_mode, color.alpha );

    // 輝度設定
    SetDrawBright( color.red, color.green, color.blue );

    // 描画
    DrawRectRotaGraph3F( position.x + anchor.x, position.y + anchor.y, m_Rect.left, m_Rect.top, m_Rect.right - m_Rect.left, m_Rect.bottom - m_Rect.top, anchor.x, anchor.y, scale.x, scale.y, rotation, m_Texture.GetResourceHandle( ), TRUE );

    // 輝度をデフォルトに戻す
    SetDrawBright( aqua::CColor::MAX_COLOR, aqua::CColor::MAX_COLOR, aqua::CColor::MAX_COLOR );

    // アルファブレンドモードをデフォルトに戻す
    SetDrawBlendMode( (int)aqua::ALPHABLEND::ALPHA, aqua::CColor::MAX_COLOR );
}

/*
 *  アニメーションの変更
 */
void
aqua::CAnimationSprite::
Change( const std::string& anime_name )
{
    Change( ConvertAnimationNameToAnimationID( anime_name ) );
}

/*
 *  アニメーションの変更
 */
void
aqua::CAnimationSprite::
Change( int anime_id )
{
    // アニメーションIDが同じなら変更しない
    if( m_CurrentAnimeID == anime_id )
        return;

    m_CurrentAnimeID = anime_id;
    m_CurrentFrame   = 0.0f;

    // アニメーションリストがあれば再生FPSを算出
    if( m_AnimationList.size( ) )
        m_CurrentAnimeFPS = (float)( m_second / (float)m_AnimationList[m_CurrentAnimeID].interval );

    // 停止フラグをOFF
    m_StopFlag = false;
}

/*
 *  アニメーションの再生
 */
void
aqua::CAnimationSprite::
Play( void )
{
    m_StopFlag = false;
}

/*
 *  アニメーションの停止
 */
void
aqua::CAnimationSprite::
Stop( void )
{
    m_StopFlag = true;
}

/*
 *  アニメーションフレームのリセット
 */
void
aqua::CAnimationSprite::
ResetAnimationFrame( void )
{
    m_CurrentFrame = 0.0f;
}

/*
 *  アニメーションの終了検知
 */
bool
aqua::CAnimationSprite::
Finished( void )
{
    if( m_AnimationList.empty( ) )
        return false;

    // ループ設定の場合、終了検知をしない
    if( m_AnimationList[m_CurrentAnimeID].loop )
        return false;

    // アニメーションが最終フレームになっていない
    if( m_CurrentFrame < (float)m_AnimationList[m_CurrentAnimeID].frames.size( ) )
        return false;

    return true;
}

/*
 *  アニメーション名取得
 */
std::string
aqua::CAnimationSprite::
GetAnimationName( void )
{
    // アニメーションリストがなければ空の文字列を返す
    if( m_AnimationList.empty( ) )
        return "";

    if( m_CurrentAnimeID < 0 || m_CurrentAnimeID >= m_AnimationList.size( ) )
        return "";

    return m_AnimationList[m_CurrentAnimeID].name;
}

/*
 *  アニメーション数の取得
 */
int
aqua::CAnimationSprite::
GetAnimationCount( void ) const
{
    if( m_AnimationList.empty( ) )
        return 0;

    return (int)m_AnimationList.size( );
}


/*
 *  ASSファイルの読み込みと解析
 */
void
aqua::CAnimationSprite::
LoadASS( const std::string& file_name )
{
    // ファイルを開く
    std::ifstream ifs(file_name, std::ios::in);

    AQUA_ASSERT( !ifs.fail(), file_name + "の読み込みに失敗しました。" );

    // データの読み込み
    const std::string json( (std::istreambuf_iterator<char>( ifs ) ), std::istreambuf_iterator<char>( ) );

    // ファイルを閉じる
    ifs.close( );

    // RapicJSONドキュメント
    rapidjson::Document doc;

    // JSONデータを解析する
    doc.Parse( json.c_str( ) );

    AQUA_ASSERT( !doc.HasParseError( ), file_name + "の解析に失敗しました。構文に誤りがあります。");

    // ファイル名取得
    m_FileName = doc[m_key_names[(int)ASS_KEY::FILE]].GetString( );

    // フレームオブジェクト取得
    const rapidjson::Value& frame_object = doc[m_key_names[(int)ASS_KEY::FRAME]];

    // フレームの幅
    m_FrameWidth = frame_object[m_key_names[(int)ASS_KEY::WIDTH]].GetInt( );

    // フレームの高さ
    m_FrameHeight = frame_object[m_key_names[(int)ASS_KEY::HEIGHT]].GetInt( );

    // 横に並んでいるフレーム数
    m_FrameCols = frame_object[m_key_names[(int)ASS_KEY::COLS]].GetInt( );

    // 縦に並んでいるフレーム数
    m_FrameRows = frame_object[m_key_names[(int)ASS_KEY::ROWS]].GetInt( );

    // アニメーションオブジェクト取得
    const rapidjson::Value& animations_object = doc[m_key_names[(int)ASS_KEY::ANIMATIONS]];

    rapidjson::Value::ConstMemberIterator it  = animations_object.MemberBegin( );
    rapidjson::Value::ConstMemberIterator end = animations_object.MemberEnd( );

    while( it != end )
    {
        ANIMATION_DATA data;

        // 名前を取得
        data.name = it->name.GetString( );

        // フレーム情報などのアニメーションデータ取得
        const rapidjson::Value& animation_data = it->value;

        // アニメーションフレームテーブル取得
        const rapidjson::Value& frames = animation_data[m_key_names[(int)ASS_KEY::FRAMES]];

        for( rapidjson::SizeType i = 0; i < frames.Size( ); ++i )
            data.frames.push_back( frames[i].GetInt( ) );

        // 更新間隔取得
        data.interval = (float)animation_data[m_key_names[(int)ASS_KEY::INTERVAL]].GetDouble( );

        // ループ設定取得
        data.loop = animation_data[m_key_names[(int)ASS_KEY::LOOP]].GetBool( );

        // アニメーションデータリストに追加
        m_AnimationList.push_back( data );

        ++it;
    }
}
/*
 *  アニメーション名をアニメーションIDに変換
 */
int
aqua::CAnimationSprite::
ConvertAnimationNameToAnimationID( const std::string& anime_name )
{
    if( m_AnimationList.empty( ) ) return 0;

    for( int i = 0; i < (int)m_AnimationList.size( ); ++i )
    {
        // 名前が一致したIDを返す
        if( m_AnimationList[i].name == anime_name )
            return i;
    }

    return 0;
}
