
/*!
 *  @file       fmf_loader.cpp
 *  @brief      FMFローダー
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "fmf_loader.h"
#include "..\..\debug\debug.h"
#include "..\memory\memory.h"

/*
 *  コンストラクタ
 */
aqua::CFMFLoader::CFMFLoader( void )
    : m_Data( nullptr )
    , m_ChipLineCount( 0 )
{
    memset( &m_Header, 0, sizeof( m_Header ) );
}

/*
 *  FMFファイル読み込み
 */
void
aqua::CFMFLoader::
Load( const std::string& file_name )
{
    // 念のため解放する
    Unload( );

    FILE* fp = nullptr;

    // ファイルを開く
    fopen_s( &fp, file_name.c_str( ), "rb" );

    AQUA_ASSERT( fp, file_name + "の読み込みに失敗しました。" );

    // ヘッダ部読み込み
    fread( &m_Header, sizeof( m_Header ), 1, fp );

    // データ部用バッファ生成
    m_Data = AQUA_NEW unsigned char[m_Header.size];

    // データ部読み込み
    fread( m_Data, m_Header.size, 1, fp );

    // ファイルを閉じる
    fclose( fp );

    m_ChipLineCount = ( m_Header.bitCount ? 16 : 255 );
}

/*
 *  解放
 */
void
aqua::CFMFLoader::
Unload( void )
{
    // データ部を解放
    AQUA_SAFE_DELETE_ARRAY( m_Data );

    // ヘッダ部をクリア
    memset( &m_Header, 0, sizeof( m_Header ) );
}

/*
 *  データ部のサイズ取得
 */
int
aqua::CFMFLoader::
GetSize( void )
{
    return m_Header.size;
}

/*
 *  レイヤー数取得
 */
int
aqua::CFMFLoader::
GetLayerCount( void )
{
    return m_Header.layerCount;
}

/*
 *  マップの幅取得
 */
int
aqua::CFMFLoader::
GetMapWidth( void )
{
    return m_Header.mapWidth;
}

/*
 *  マップの高さ取得
 */
int
aqua::CFMFLoader::
GetMapHeight( void )
{
    return m_Header.mapHeight;
}

/*
 *  チップの幅取得
 */
int
aqua::CFMFLoader::
GetChipWidth( void )
{
    return m_Header.chipWidth;
}

/*
 *  チップの高さ取得
 */
int
aqua::CFMFLoader::
GetChipHeight( void )
{
    return m_Header.chipHeight;
}

/*
 *  データ部取得
 */
unsigned char*
aqua::CFMFLoader::
GetData( void )
{
    return m_Data;
}

/*
 *  1レイヤー辺りのサイズ
 */
int
aqua::CFMFLoader::
GetLayerSize( void )
{
    return m_Header.mapWidth * m_Header.mapHeight * ( m_Header.bitCount / 8 );
}

/*
 *  レイヤー別データ部取得
 */
unsigned char*
aqua::CFMFLoader::
GetLayerData( int layer_id )
{
    // 1レイヤー辺りのサイズ
    int layer_size = GetLayerSize( );

    return m_Data + ( layer_id * layer_size );
}

/*
 *  横に並んでいるチップの数
 */
int
aqua::CFMFLoader::
GetChipLineCount( void )
{
    return m_ChipLineCount;
}
