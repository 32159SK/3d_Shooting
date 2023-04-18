
/*!
 *  @file       video_manager.cpp
 *  @brief      �r�f�I�Ǘ��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "video_manager.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"
#include "..\..\video\video_resource\video_resource.h"

/*
 *  �C���X�^���X�̎擾
 */
aqua::core::CVideoManager&
aqua::core::CVideoManager::
GetInstance( void )
{
    static CVideoManager instance;

    return instance;
}

/*
 *  �r�f�I�N���X�̓ǂݍ���
 */
aqua::core::CVideoResource*
aqua::core::CVideoManager::
Load( const std::string& file_name )
{
    // �r�f�I����
    CVideoResource* video = Find( file_name );

    // �r�f�I��������Ȃ�����
    if( !video )
    {
        // �V�����r�f�I����
        video = AQUA_NEW CVideoResource( );

        // �ǂݍ���
        video->Load( file_name );

        // �r�f�I���X�g�ɒǉ�
        m_VideoResourceList.push_back( video );
    }
    
    // �Q�ƃJ�E���^���Z
    video->AddReference( );

    return video;
}

/*
 *  �r�f�I�N���X�̉��
 */
void
aqua::core::CVideoManager::
Unload( core::CVideoResource* video )
{
    if( !video ) return;

    if( m_VideoResourceList.empty( ) ) return;

    // �Q�ƃJ�E���^���Z
    // �Q�Ƃ��Ȃ��Ȃ�������
    if( video->RemoveReference( ) > 0 ) return;

    VIDEO_RESOURCE_LIST::iterator it  = m_VideoResourceList.begin( );
    VIDEO_RESOURCE_LIST::iterator end = m_VideoResourceList.end( );

    while( it != end )
    {
        if( (*it)->GetResourceName( ) == video->GetResourceName( ) )
        {
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );

            m_VideoResourceList.erase( it );

            break;
        }

        ++it;
    }
}

/*
 *  �r�f�I�N���X�̌���
 */
aqua::core::CVideoResource*
aqua::core::CVideoManager::
Find( const std::string& file_name )
{
    if( m_VideoResourceList.empty( ) ) return nullptr;

    VIDEO_RESOURCE_LIST::iterator it  = m_VideoResourceList.begin( );
    VIDEO_RESOURCE_LIST::iterator end = m_VideoResourceList.end( );

    // �t�@�C��������v�����r�f�I�N���X��Ԃ�
    while( it != end )
    {
        if( ( *it )->GetResourceName( ) == file_name )
            return ( *it );

        ++it;
    }

    return nullptr;
}

/*
 *  �r�f�I���X�g�̃N���A
 */
void
aqua::core::CVideoManager::
Clear( void )
{
    if( m_VideoResourceList.empty( ) ) return;

    VIDEO_RESOURCE_LIST::iterator it  = m_VideoResourceList.begin( );
    VIDEO_RESOURCE_LIST::iterator end = m_VideoResourceList.end( );

    while( it != end )
    {
        if( (*it) )
        {
            // �r�f�I���
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );
        }

        ++it;
    }

    // �r�f�I���X�g���
    m_VideoResourceList.clear( );
}

/*
 *  �R���X�g���N�^
 */
aqua::core::CVideoManager::
CVideoManager( void )
{
    m_VideoResourceList.clear( );
}

/*
 *  �R�s�[�R���X�g���N�^
 */
aqua::core::CVideoManager::
CVideoManager( const aqua::core::CVideoManager& rhs )
{
    (void)rhs;
}

/*
 *  ������Z�q
 */
aqua::core::CVideoManager&
aqua::core::CVideoManager::
operator=( const aqua::core::CVideoManager& rhs )
{
    (void)rhs;

    return *this;
}
