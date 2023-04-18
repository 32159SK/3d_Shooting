
/*!
 *  @file       texture_manager.cpp
 *  @brief      2D�e�N�X�`���Ǘ��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "texture_manager.h"
#include "..\texture_resource\texture_resource.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"

/*
 *  �C���X�^���X�̎擾
 */
aqua::core::CTextureManager&
aqua::core::CTextureManager::
GetInstance( void )
{
    static CTextureManager instance;

    return instance;
}

/*
 *  �e�N�X�`���N���X�̓ǂݍ���
 */
aqua::core::CTextureResource*
aqua::core::CTextureManager::
Load( const std::string& file_name )
{
    // �e�N�X�`������
    CTextureResource* texture = Find( file_name );

    // �e�N�X�`����������Ȃ�����
    if( !texture )
    {
        // �V�����e�N�X�`������
        texture = AQUA_NEW CTextureResource( );

        // �ǂݍ���
        texture->Load( file_name );

        // �e�N�X�`�����X�g�ɒǉ�
        m_TextureList.push_back( texture );
    }

    // �Q�ƃJ�E���^���Z
    texture->AddReference( );

    return texture;
}

/*
 *  �e�N�X�`���N���X�̉��
 */
void
aqua::core::CTextureManager::
Unload( core::CTextureResource* texture )
{
    if( !texture ) return;

    if( m_TextureList.empty( ) ) return;

    // �Q�ƃJ�E���^���Z
    // �Q�Ƃ��Ȃ��Ȃ�������
    if( texture->RemoveReference( ) > 0 ) return;

    TEXTURE_LIST::iterator it  = m_TextureList.begin( );
    TEXTURE_LIST::iterator end = m_TextureList.end( );

    while( it != end )
    {
        if( (*it)->GetResourceName( ) == texture->GetResourceName( ) )
        {
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );

            m_TextureList.erase( it );

            break;
        }

        ++it;
    }
}

/*
 *  �e�N�X�`���N���X�̌���
 */
aqua::core::CTextureResource*
aqua::core::CTextureManager::
Find( const std::string& file_name )
{
    if( m_TextureList.empty( ) ) return NULL;

    TEXTURE_LIST::iterator it  = m_TextureList.begin( );
    TEXTURE_LIST::iterator end = m_TextureList.end( );

    // �t�@�C��������v�����e�N�X�`���N���X��Ԃ�
    while( it != end )
    {
        if( ( *it )->GetResourceName( ) == file_name )
            return ( *it );

        ++it;
    }

    return NULL;
}

/*
 *  �e�N�X�`�����X�g�̃N���A
 */
void
aqua::core::CTextureManager::
Clear( void )
{
    if( m_TextureList.empty( ) ) return;

    TEXTURE_LIST::iterator it  = m_TextureList.begin( );
    TEXTURE_LIST::iterator end = m_TextureList.end( );

    while( it != end )
    {
        if( (*it) )
        {
            // �e�N�X�`�����
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );
        }

        ++it;
    }

    // �e�N�X�`�����X�g���
    m_TextureList.clear( );
}

/*
 *  �R���X�g���N�^
 */
aqua::core::CTextureManager::
CTextureManager( void )
{
    m_TextureList.clear( );
}

/*
 *  �R�s�[�R���X�g���N�^
 */
aqua::core::CTextureManager::
CTextureManager( const aqua::core::CTextureManager& rhs )
{
    (void)rhs;
}

/*
 *  ������Z�q
 */
aqua::core::CTextureManager&
aqua::core::CTextureManager::
operator=( const aqua::core::CTextureManager& rhs )
{
    (void)rhs;

    return *this;
}

/*
 *  �e�N�X�`������
 */
aqua::core::CTextureResource*
aqua::core::CTextureManager::
Create( int width, int height, bool alpha_channel )
{
    CTextureResource* texture = nullptr;

    // �V�����e�N�X�`������
    texture = AQUA_NEW CTextureResource( );

    // ����
    texture->Create( width, height, alpha_channel );

    // �e�N�X�`�����X�g�ɒǉ�
    m_TextureList.push_back( texture );

    // �Q�ƃJ�E���^���Z
    texture->AddReference( );

    return texture;
}

/*
 *  �e�N�X�`�����
 */
void
aqua::core::CTextureManager::
Delete( aqua::core::CTextureResource* texture )
{
    if( !texture ) return;

    if( m_TextureList.empty( ) ) return;

    // �Q�ƃJ�E���^���Z
    // �Q�Ƃ��Ȃ��Ȃ�������
    if( texture->RemoveReference( ) > 0 ) return;

    TEXTURE_LIST::iterator it  = m_TextureList.begin( );
    TEXTURE_LIST::iterator end = m_TextureList.end( );

    while( it != end )
    {
        if( (*it) == texture )
        {
            (*it)->Delete( );

            AQUA_SAFE_DELETE( (*it) );

            m_TextureList.erase( it );

            break;
        }

        ++it;
    }
}
