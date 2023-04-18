
/*!
 *  @file       texture.cpp
 *  @brief      2D�e�N�X�`���N���X
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
 *  �R���X�g���N�^
 */
aqua::CTexture::
CTexture( void )
    : m_TextureResource( nullptr )
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
aqua::CTexture::
CTexture( const aqua::CTexture& texture )
    : m_TextureResource( nullptr )
{
    if( m_TextureResource )
        m_TextureResource->RemoveReference( );

    m_TextureResource = texture.m_TextureResource;

    // �Q�ƃJ�E���^���Z
    m_TextureResource->AddReference( );
}

/*
 *  �e�N�X�`���ǂݍ���
 */
void
aqua::CTexture::
Load( const std::string& file_name )
{
    // �e�N�X�`�����\�[�X�ޔ�
    core::CTextureResource* texture = m_TextureResource;

    // �e�N�X�`���}�l�[�W������e�N�X�`���擾
    m_TextureResource = core::CTextureManager::GetInstance( ).Load( file_name );

    if( texture )
    {
        int count = texture->RemoveReference( );

        // �O�̃e�N�X�`���̎Q�ƃJ�E���^���Ȃ��Ȃ�������
        if( count <= 0 )
            core::CTextureManager::GetInstance( ).Unload( texture );
    }
}

/*
 *  �e�N�X�`�����
 */
void
aqua::CTexture::
Unload( void )
{
    // �e�N�X�`�����
    if( m_TextureResource )
        core::CTextureManager::GetInstance( ).Unload( m_TextureResource );

    m_TextureResource = nullptr;
}

/*
 *  ������Z�q�̃I�[�o�[���[�h
 */
aqua::CTexture&
aqua::CTexture::
operator=( const aqua::CTexture& texture )
{
    // �e�N�X�`���������Ă�����Q�Ƃ����Z
    if( m_TextureResource )
        m_TextureResource->RemoveReference( );

    m_TextureResource = texture.m_TextureResource;

    // �Q�ƃJ�E���^���Z
    m_TextureResource->AddReference( );

    return *this;
}

/*
 *  �e�N�X�`������
 */
void
aqua::CTexture::
Create( int width, int height, bool alpha_channel )
{
    // �e�N�X�`�����\�[�X�ޔ�
    core::CTextureResource* texture = m_TextureResource;

    // �e�N�X�`���}�l�[�W������e�N�X�`���擾
    m_TextureResource = core::CTextureManager::GetInstance( ).Create( width, height, alpha_channel );

    if( texture )
    {
        int count = texture->RemoveReference( );

        // �O�̃e�N�X�`���̎Q�ƃJ�E���^���Ȃ��Ȃ�������
        if( count <= 0 )
            core::CTextureManager::GetInstance( ).Delete( texture );
    }
}

/*
 *  �e�N�X�`�����
 */
void
aqua::CTexture::
Delete( void )
{
    // �e�N�X�`�����
    if( m_TextureResource )
        core::CTextureManager::GetInstance( ).Delete( m_TextureResource );

    m_TextureResource = nullptr;
}
