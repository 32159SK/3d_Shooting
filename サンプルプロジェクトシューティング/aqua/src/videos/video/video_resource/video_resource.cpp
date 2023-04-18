
/*!
 *  @file       video_resource.cpp
 *  @brief      ビデオリソース
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include <DxLib.h>
#include "video_resource.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"

/*
 *  コンストラクタ
 */
aqua::core::CVideoResource::
CVideoResource( void )
    : IResourceObject( aqua::core::RESOURCE_TYPE::LOAD_VIDEO )
{
}

/*
 *  読み込み
 */
void
aqua::core::CVideoResource::
Load( const std::string& file_name )
{
    if( m_Enabel ) return;

    // ビデオ読み込み
    m_ResourceHandle = LoadGraph( file_name.c_str( ) );

    AQUA_DX_ASSERT( m_ResourceHandle, file_name + "の読み込みに失敗しました。" );

    // ファイルパスを保存
    m_ResourceName = file_name;

    // 読み込み済み
    m_Enabel = true;
}

/*
 *  解放
 */
void
aqua::core::CVideoResource::
Unload( void )
{
    DeleteGraph( m_ResourceHandle );

    m_ResourceHandle = AQUA_UNUSED_HANDLE;

    m_ReferenceCount = 0;

    m_ResourceName.clear( );

    m_ResourceType = RESOURCE_TYPE::DUMMY;

    m_Enabel = false;
}
