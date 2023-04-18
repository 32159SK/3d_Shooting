
/*!
 *  @file       texture.cpp
 *  @brief      2Dテクスチャクラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include <windows.h>
#include "texture.h"
#include "texture_manager\texture_manager.h"

/*
 *  コンストラクタ
 */
aqua::CTexture::
CTexture( void )
    : m_TextureResource( nullptr )
{
}

/*
 *  コピーコンストラクタ
 */
aqua::CTexture::
CTexture( const aqua::CTexture& texture )
    : m_TextureResource( nullptr )
{
    if( m_TextureResource )
        m_TextureResource->RemoveReference( );

    m_TextureResource = texture.m_TextureResource;

    // 参照カウンタ加算
    m_TextureResource->AddReference( );
}

/*
 *  テクスチャ読み込み
 */
void
aqua::CTexture::
Load( const std::string& file_name )
{
    // テクスチャリソース退避
    core::CTextureResource* texture = m_TextureResource;

    // テクスチャマネージャからテクスチャ取得
    m_TextureResource = core::CTextureManager::GetInstance( ).Load( file_name );

    if( texture )
    {
        int count = texture->RemoveReference( );

        // 前のテクスチャの参照カウンタがなくなったら解放
        if( count <= 0 )
            core::CTextureManager::GetInstance( ).Unload( texture );
    }
}

/*
 *  テクスチャ解放
 */
void
aqua::CTexture::
Unload( void )
{
    // テクスチャ解放
    if( m_TextureResource )
        core::CTextureManager::GetInstance( ).Unload( m_TextureResource );

    m_TextureResource = nullptr;
}

/*
 *  代入演算子のオーバーロード
 */
aqua::CTexture&
aqua::CTexture::
operator=( const aqua::CTexture& texture )
{
    // テクスチャを持っていたら参照を減算
    if( m_TextureResource )
        m_TextureResource->RemoveReference( );

    m_TextureResource = texture.m_TextureResource;

    // 参照カウンタ加算
    m_TextureResource->AddReference( );

    return *this;
}

/*
 *  テクスチャ生成
 */
void
aqua::CTexture::
Create( int width, int height, bool alpha_channel )
{
    // テクスチャリソース退避
    core::CTextureResource* texture = m_TextureResource;

    // テクスチャマネージャからテクスチャ取得
    m_TextureResource = core::CTextureManager::GetInstance( ).Create( width, height, alpha_channel );

    if( texture )
    {
        int count = texture->RemoveReference( );

        // 前のテクスチャの参照カウンタがなくなったら解放
        if( count <= 0 )
            core::CTextureManager::GetInstance( ).Delete( texture );
    }
}

/*
 *  テクスチャ解放
 */
void
aqua::CTexture::
Delete( void )
{
    // テクスチャ解放
    if( m_TextureResource )
        core::CTextureManager::GetInstance( ).Delete( m_TextureResource );

    m_TextureResource = nullptr;
}
