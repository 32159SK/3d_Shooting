
/*!
 *  @file       effekseer_resource.cpp
 *  @brief      Effekseerリソース
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "effekseer_resource.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"
#include "..\effekseer_manager\effekseer_manager.h"

/*
 *  コンストラクタ
 */
aqua::core::CEffekseerResource::
CEffekseerResource( void )
    : IResourceObject( aqua::core::RESOURCE_TYPE::LOAD_EFFEKSEER )
{
}

/*
 *  Effekseer読み込み
 */
void
aqua::core::CEffekseerResource::
Load( const std::string& file_name )
{
    if( m_Enabel ) return;

    // エフェクト読み込み
    m_ResourceHandle = LoadEffekseerEffect( file_name.c_str( ) );

    AQUA_DX_ASSERT( m_ResourceHandle, file_name + "の読み込みに失敗しました。" );

    // ファイルパスを保存
    m_ResourceName = file_name;

    // 読み込み済み
    m_Enabel = true;
}

/*
 *  Effekseer解放
 */
void
aqua::core::CEffekseerResource::
Unload( void )
{
    DeleteEffekseerEffect( m_ResourceHandle );

    m_ResourceHandle = AQUA_UNUSED_HANDLE;

    m_ResourceName.clear( );

    m_ReferenceCount = 0;

    m_ResourceType = RESOURCE_TYPE::DUMMY;

    m_Enabel = false;
}
