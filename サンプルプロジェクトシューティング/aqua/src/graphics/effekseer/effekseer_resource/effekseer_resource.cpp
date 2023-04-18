
/*!
 *  @file       effekseer_resource.cpp
 *  @brief      Effekseer���\�[�X
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
 *  �R���X�g���N�^
 */
aqua::core::CEffekseerResource::
CEffekseerResource( void )
    : IResourceObject( aqua::core::RESOURCE_TYPE::LOAD_EFFEKSEER )
{
}

/*
 *  Effekseer�ǂݍ���
 */
void
aqua::core::CEffekseerResource::
Load( const std::string& file_name )
{
    if( m_Enabel ) return;

    // �G�t�F�N�g�ǂݍ���
    m_ResourceHandle = LoadEffekseerEffect( file_name.c_str( ) );

    AQUA_DX_ASSERT( m_ResourceHandle, file_name + "�̓ǂݍ��݂Ɏ��s���܂����B" );

    // �t�@�C���p�X��ۑ�
    m_ResourceName = file_name;

    // �ǂݍ��ݍς�
    m_Enabel = true;
}

/*
 *  Effekseer���
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
