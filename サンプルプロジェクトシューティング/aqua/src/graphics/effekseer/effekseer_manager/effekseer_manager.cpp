
/*!
 *  @file       effekseer_manager.cpp
 *  @brief      Effekseer�Ǘ��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "effekseer_manager.h"
#include "..\effekseer_resource\effekseer_resource.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"

/*
 *  �C���X�^���X�̎擾
 */
aqua::core::CEffekseerManager&
aqua::core::CEffekseerManager::
GetInstance( void )
{
    static CEffekseerManager instance;

    return instance;
}

/*
 *  Effekseer�N���X�̓ǂݍ���
 */
aqua::core::CEffekseerResource*
aqua::core::CEffekseerManager::
Load( const std::string& file_name )
{
    // Effekseer����
    CEffekseerResource* effect = Find( file_name );

    // Effekseer��������Ȃ�����
    if( !effect )
    {
        // �V����Effekseer����
        effect = AQUA_NEW CEffekseerResource( );

        // �ǂݍ���
        effect->Load( file_name );

        // Effekseer���X�g�ɒǉ�
        m_EffekseerList.push_back( effect );
    }

    // �Q�ƃJ�E���^���Z
    effect->AddReference( );

    return effect;
}

/*
 *  Effekseer�N���X�̉��
 */
void
aqua::core::CEffekseerManager::
Unload( core::CEffekseerResource* effect )
{
    if( !effect ) return;

    if( m_EffekseerList.empty( ) ) return;

    // �Q�ƃJ�E���^���Z
    // �Q�Ƃ��Ȃ��Ȃ�������
    if( effect->RemoveReference( ) > 0 ) return;

    EFFEKSEER_LIST::iterator it  = m_EffekseerList.begin( );
    EFFEKSEER_LIST::iterator end = m_EffekseerList.end( );

    while( it != end )
    {
        if( (*it)->GetResourceName( ) == effect->GetResourceName( ) )
        {
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );

            m_EffekseerList.erase( it );

            break;
        }

        ++it;
    }
}

/*
 *  Effekseer�N���X�̌���
 */
aqua::core::CEffekseerResource*
aqua::core::CEffekseerManager::
Find( const std::string& file_name )
{
    if( m_EffekseerList.empty( ) ) return NULL;

    EFFEKSEER_LIST::iterator it  = m_EffekseerList.begin( );
    EFFEKSEER_LIST::iterator end = m_EffekseerList.end( );

    // �t�@�C��������v����Effekseer�N���X��Ԃ�
    while( it != end )
    {
        if( ( *it )->GetResourceName( ) == file_name )
            return ( *it );

        ++it;
    }

    return NULL;
}

/*
 *  Effekseer���X�g�̃N���A
 */
void
aqua::core::CEffekseerManager::
Clear( void )
{
    if( m_EffekseerList.empty( ) ) return;

    EFFEKSEER_LIST::iterator it  = m_EffekseerList.begin( );
    EFFEKSEER_LIST::iterator end = m_EffekseerList.end( );

    while( it != end )
    {
        if( (*it) )
        {
            // Effekseer���
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );
        }

        ++it;
    }

    // Effekseer���X�g���
    m_EffekseerList.clear( );
}

/*
 *  �R���X�g���N�^
 */
aqua::core::CEffekseerManager::
CEffekseerManager( void )
{
    m_EffekseerList.clear( );
}

/*
 *  �R�s�[�R���X�g���N�^
 */
aqua::core::CEffekseerManager::
CEffekseerManager( const aqua::core::CEffekseerManager& rhs )
{
    (void)rhs;
}

/*
 *  ������Z�q
 */
aqua::core::CEffekseerManager&
aqua::core::CEffekseerManager::
operator=( const aqua::core::CEffekseerManager& rhs )
{
    (void)rhs;

    return *this;
}
