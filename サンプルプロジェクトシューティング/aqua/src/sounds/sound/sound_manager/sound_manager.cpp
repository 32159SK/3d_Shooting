
/*!
 *  @file       sound_manager.cpp
 *  @brief      �T�E���h�Ǘ��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "sound_manager.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"
#include "..\..\sound\sound_resource\sound_resource.h"

/*
 *  �C���X�^���X�̎擾
 */
aqua::core::CSoundManager&
aqua::core::CSoundManager::
GetInstance( void )
{
    static CSoundManager instance;

    return instance;
}

/*
 *  �T�E���h�N���X�̓ǂݍ���
 */
aqua::core::CSoundResource*
aqua::core::CSoundManager::
Load( const std::string& file_name, int buffer_count )
{
    // �T�E���h����
    CSoundResource* sound = Find( file_name );

    // �T�E���h��������Ȃ�����
    if( !sound )
    {
        // �V�����T�E���h����
        sound = AQUA_NEW CSoundResource( );

        // �ǂݍ���
        sound->Load( file_name, buffer_count );

        // �T�E���h���X�g�ɒǉ�
        m_SoundResourceList.push_back( sound );
    }
    
    // �Q�ƃJ�E���^���Z
    sound->AddReference( );

    return sound;
}

/*
 *  �T�E���h�N���X�̉��
 */
void
aqua::core::CSoundManager::
Unload( core::CSoundResource* sound )
{
    if( !sound ) return;

    if( m_SoundResourceList.empty( ) ) return;

    // �Q�ƃJ�E���^���Z
    // �Q�Ƃ��Ȃ��Ȃ�������
    if( sound->RemoveReference( ) > 0 ) return;

    SOUND_RESOURCE_LIST::iterator it  = m_SoundResourceList.begin( );
    SOUND_RESOURCE_LIST::iterator end = m_SoundResourceList.end( );

    while( it != end )
    {
        if( (*it)->GetResourceName( ) == sound->GetResourceName( ) )
        {
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );

            m_SoundResourceList.erase( it );

            break;
        }

        ++it;
    }
}

/*
 *  �X�V
 */
void
aqua::core::CSoundManager::
Update( void )
{
#ifdef AQUA_DEBUG

    if( m_SoundResourceList.empty( ) ) return;

    SOUND_RESOURCE_LIST::iterator it  = m_SoundResourceList.begin( );
    SOUND_RESOURCE_LIST::iterator end = m_SoundResourceList.end( );

    while( it != end )
    {
        float frequency = (float)( (*it)->GetDefaultFrequency( ) );

        frequency *= aqua::core::CVisualDebugger::GetInstance( ).GetDebugDeltaTimeScale( );

        (*it)->SetFrequency( (int)frequency );

        ++it;
    }
#endif
}

/*
 *  �T�E���h�N���X�̌���
 */
aqua::core::CSoundResource*
aqua::core::CSoundManager::
Find( const std::string& file_name )
{
    if( m_SoundResourceList.empty( ) ) return nullptr;

    SOUND_RESOURCE_LIST::iterator it  = m_SoundResourceList.begin( );
    SOUND_RESOURCE_LIST::iterator end = m_SoundResourceList.end( );

    // �t�@�C��������v�����T�E���h�N���X��Ԃ�
    while( it != end )
    {
        if( ( *it )->GetResourceName( ) == file_name )
            return ( *it );

        ++it;
    }

    return nullptr;
}

/*
 *  �T�E���h���X�g�̃N���A
 */
void
aqua::core::CSoundManager::
Clear( void )
{
    if( m_SoundResourceList.empty( ) ) return;

    SOUND_RESOURCE_LIST::iterator it  = m_SoundResourceList.begin( );
    SOUND_RESOURCE_LIST::iterator end = m_SoundResourceList.end( );

    while( it != end )
    {
        if( (*it) )
        {
            // �T�E���h���
            (*it)->Unload( );

            AQUA_SAFE_DELETE( (*it) );
        }

        ++it;
    }

    // �T�E���h���X�g���
    m_SoundResourceList.clear( );
}

/*
 *  �R���X�g���N�^
 */
aqua::core::CSoundManager::
CSoundManager( void )
{
    m_SoundResourceList.clear( );
}

/*
 *  �R�s�[�R���X�g���N�^
 */
aqua::core::CSoundManager::
CSoundManager( const aqua::core::CSoundManager& rhs )
{
    (void)rhs;
}

/*
 *  ������Z�q
 */
aqua::core::CSoundManager&
aqua::core::CSoundManager::
operator=( const aqua::core::CSoundManager& rhs )
{
    (void)rhs;

    return *this;
}
