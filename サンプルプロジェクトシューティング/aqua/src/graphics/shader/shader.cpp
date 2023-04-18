
/*!
 *  @file       shader.cpp
 *  @brief      �V�F�[�_�N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "shader.h"
#include "..\..\debug\debug.h"

/*
 *  �R���X�g���N�^
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
 *  ����
 */
void
aqua::CShader::
Create( const std::string& file_name )
{
    Delete( );

    std::string vs_name = file_name + ".vso";

    // �o�[�e�b�N�X�V�F�[�_�ǂݍ���
    m_VertexShaderHandle = LoadVertexShader( vs_name.c_str( ) );

    AQUA_DX_ASSERT( m_VertexShaderHandle, vs_name + "�̓ǂݍ��݂Ɏ��s���܂����B" );

    std::string ps_name = file_name + ".pso";

    // �s�N�Z���V�F�[�_�ǂݍ���
    m_PixelShaderHandle  = LoadPixelShader( ps_name.c_str( ) );

    AQUA_DX_ASSERT( m_PixelShaderHandle, ps_name + "�̓ǂݍ��݂Ɏ��s���܂����B" );


    m_VertxConstBufferHandle = CreateShaderConstantBuffer( sizeof( float ) * 4 );
}

/*
 *  ���
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
 *  �V�F�[�_�̓K�p�J�n
 */
void
aqua::CShader::
Begin( void )
{
    // �I���W�i���V�F�[�_���g�p����
    MV1SetUseOrigShader( TRUE );

    // �V�F�[�_�ݒ�
    SetUseVertexShader( m_VertexShaderHandle );
    SetUsePixelShader( m_PixelShaderHandle );

    // �f�t�H���g���C�g�𖳌���
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
 *  �V�F�[�_�̓K�p�I��
 */
void
aqua::CShader::
End( void )
{
    // �f�t�H���g���C�g��L����
    SetLightEnable( TRUE );

    // �V�F�[�_����
    SetUseVertexShader( AQUA_UNUSED_HANDLE );
    SetUsePixelShader( AQUA_UNUSED_HANDLE );

    // �I���W�i���V�F�[�_���g�p���Ȃ�
    MV1SetUseOrigShader( FALSE );
}

/*
 *  �V�F�[�_�Ŏg�p����e�N�X�`����ݒ�
 */
void
aqua::CShader::
SetUseTexture( int register_id, int handle )
{
    SetUseTextureToShader( register_id, handle );
}
