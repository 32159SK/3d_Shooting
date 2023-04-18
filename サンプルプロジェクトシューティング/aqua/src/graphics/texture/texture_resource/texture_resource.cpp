
/*!
 *  @file       texture_resource.cpp
 *  @brief      2Dテクスチャリソース
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include <DxLib.h>
#include <ctime>
#include "texture_resource.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"
#include "..\texture_manager\texture_manager.h"

const unsigned int aqua::core::CTextureResource::m_transparent_color = 0xffff00ff;

/*
 *  コンストラクタ
 */
aqua::core::CTextureResource::
CTextureResource( void )
    : IResourceObject( aqua::core::RESOURCE_TYPE::LOAD_TEXTURE )
    , m_Width( 0 )
    , m_Height( 0 )
{
}

/*
 *  テクスチャ読み込み
 */
void
aqua::core::CTextureResource::
Load( const std::string& file_name )
{
    if( m_Enabel ) return;

    // 透過色指定
    SetTransColor( ( m_transparent_color >> 16 ) & 0xff, ( m_transparent_color >> 8 ) & 0xff, m_transparent_color & 0xff );

    // テクスチャ読み込み
    m_ResourceHandle = LoadGraph( file_name.c_str( ) );

    AQUA_DX_ASSERT( m_ResourceHandle, file_name + "の読み込みに失敗しました。" );

    // グラフィックサイズ取得
    GetGraphSize( m_ResourceHandle, &m_Width, &m_Height );

    // ファイルパスを保存
    m_ResourceName = file_name;

    // 読み込み済み
    m_Enabel = true;
}

/*
 *  テクスチャ解放
 */
void
aqua::core::CTextureResource::
Unload( void )
{
    DeleteGraph( m_ResourceHandle );

    m_ResourceHandle = AQUA_UNUSED_HANDLE;

    m_ResourceName.clear( );

    m_ReferenceCount = 0;

    m_ResourceType = RESOURCE_TYPE::DUMMY;

    m_Enabel = false;

    m_Width = m_Height = 0;
}

/*
 *  テクスチャ生成
 */
void
aqua::core::CTextureResource::
Create( int width, int height, bool alpha_channel )
{
    if( m_Enabel ) return;

    m_Width  = width;
    m_Height = height;

    // サイズに合わせてサーフェイスを生成
    m_ResourceHandle = MakeScreen( m_Width, m_Height, ( alpha_channel ? TRUE : FALSE ) );

    AQUA_DX_ASSERT( m_ResourceHandle, "テクスチャの作成に失敗しました。" );

    // 生成したテクスチャタイプ
    m_ResourceType = RESOURCE_TYPE::CREATE_TEXTURE;

    // リソース名を保存
    // 時間で名前を付ける
    time_t now = time( NULL );
    
    tm local_time;
    
    localtime_s( &local_time, &now );

    m_ResourceName = "Texture";

    m_ResourceName += std::to_string( local_time.tm_year ) + std::to_string( local_time.tm_mon ) + std::to_string( local_time.tm_mday );

    m_ResourceName += std::to_string( local_time.tm_hour ) + std::to_string( local_time.tm_min ) + std::to_string( local_time.tm_sec );

    // 生成済み
    m_Enabel = true;
}

/*
 *  テクスチャ解放
 */
void
aqua::core::CTextureResource::
Delete( void )
{
    m_ResourceName.clear( );

    m_ReferenceCount = 0;

    m_ResourceType = RESOURCE_TYPE::DUMMY;

    m_Enabel = false;

    m_Width = m_Height = 0;
}
