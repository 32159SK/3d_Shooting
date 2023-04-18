
/*!
 *  @file       shader.cpp
 *  @brief      シェーダクラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "shader.h"
#include "..\..\debug\debug.h"

/*
 *  コンストラクタ
 */
aqua::CShader::
CShader( void )
    : aqua::core::IResourceObject( aqua::core::RESOURCE_TYPE::LOAD_SHADER )
    , m_VertexShaderHandle( AQUA_UNUSED_HANDLE )
    , m_PixelShaderHandle( AQUA_UNUSED_HANDLE )
    , m_VertxConstBufferHandle( AQUA_UNUSED_HANDLE )
{
}

/*
 *  生成
 */
void
aqua::CShader::
Create( const std::string& file_name )
{
    Delete( );

    std::string vs_name = file_name + ".vso";

    // バーテックスシェーダ読み込み
    m_VertexShaderHandle = LoadVertexShader( vs_name.c_str( ) );

    AQUA_DX_ASSERT( m_VertexShaderHandle, vs_name + "の読み込みに失敗しました。" );

    std::string ps_name = file_name + ".pso";

    // ピクセルシェーダ読み込み
    m_PixelShaderHandle  = LoadPixelShader( ps_name.c_str( ) );

    AQUA_DX_ASSERT( m_PixelShaderHandle, ps_name + "の読み込みに失敗しました。" );


    m_VertxConstBufferHandle = CreateShaderConstantBuffer( sizeof( float ) * 4 );
}

/*
 *  解放
 */
void
aqua::CShader::
Delete( void )
{
    DeleteShaderConstantBuffer( m_VertxConstBufferHandle );

    m_VertxConstBufferHandle = AQUA_UNUSED_HANDLE;

    DeleteShader( m_PixelShaderHandle );
    DeleteShader( m_VertexShaderHandle );

    m_VertexShaderHandle = AQUA_UNUSED_HANDLE;
    m_PixelShaderHandle  = AQUA_UNUSED_HANDLE;
}

/*
 *  シェーダの適用開始
 */
void
aqua::CShader::
Begin( void )
{
    // オリジナルシェーダを使用する
    MV1SetUseOrigShader( TRUE );

    // シェーダ設定
    SetUseVertexShader( m_VertexShaderHandle );
    SetUsePixelShader( m_PixelShaderHandle );

    // デフォルトライトを無効化
    SetLightEnable( FALSE );

    VECTOR camera_pos = GetCameraPosition( );

    FLOAT4* buffer = (FLOAT4*)GetBufferShaderConstantBuffer( m_VertxConstBufferHandle );

    buffer->x = camera_pos.x;
    buffer->y = camera_pos.y;
    buffer->z = camera_pos.z;
    buffer->w = 0.0f;

    UpdateShaderConstantBuffer( m_VertxConstBufferHandle );

    SetShaderConstantBuffer( m_VertxConstBufferHandle, DX_SHADERTYPE_VERTEX, 4 ) ;
}

/*
 *  シェーダの適用終了
 */
void
aqua::CShader::
End( void )
{
    // デフォルトライトを有効化
    SetLightEnable( TRUE );

    // シェーダ解除
    SetUseVertexShader( AQUA_UNUSED_HANDLE );
    SetUsePixelShader( AQUA_UNUSED_HANDLE );

    // オリジナルシェーダを使用しない
    MV1SetUseOrigShader( FALSE );
}

/*
 *  シェーダで使用するテクスチャを設定
 */
void
aqua::CShader::
SetUseTexture( int register_id, int handle )
{
    SetUseTextureToShader( register_id, handle );
}
