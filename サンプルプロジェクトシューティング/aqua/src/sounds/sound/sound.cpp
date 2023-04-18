
/*!
 *  @file       sound.cpp
 *  @brief      �T�E���h�Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "sound.h"
#include "sound_manager\sound_manager.h"
#include "..\..\utility\memory\memory.h"

/*
 *  �R���X�g���N�^
 */
aqua::CSound::
CSound( void )
    : m_SoundResource( nullptr )
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
aqua::CSound::
CSound( const aqua::CSound& sound )
{
    if( m_SoundResource )
        m_SoundResource->RemoveReference( );

    m_SoundResource = sound.m_SoundResource;

    // �Q�ƃJ�E���^���Z
    m_SoundResource->AddReference( );
}

/*
 *  �T�E���h�̓ǂݍ���
 */
void
aqua::CSound::
Load( const std::string& file_name, int buffer_count )
{
    // �T�E���h���\�[�X�ޔ�
    core::CSoundResource* sound = m_SoundResource;

    // �T�E���h�}�l�[�W������T�E���h�����[�h
    m_SoundResource = core::CSoundManager::GetInstance( ).Load( file_name, buffer_count );

    if( sound )
    {
        int count = sound->RemoveReference( );

        // �O�̃T�E���h�̎Q�ƃJ�E���^���Ȃ��Ȃ�������
        if( count <= 0 )
            core::CSoundManager::GetInstance( ).Unload( sound );
    }
}

/*
 *  �T�E���h�̉��
 */
void
aqua::CSound::
Unload( void )
{
    // �T�E���h���
    if( m_SoundResource )
        core::CSoundManager::GetInstance( ).Unload( m_SoundResource );

    m_SoundResource = nullptr;
}

/*
 *  ������Z�q�̃I�[�o�[���[�h
 */
aqua::CSound&
aqua::CSound::
operator=( const aqua::CSound& sound )
{
    // �T�E���h�������Ă�����Q�Ƃ����Z
    if( m_SoundResource )
        m_SoundResource->RemoveReference( );

    m_SoundResource = sound.m_SoundResource;

    // �Q�ƃJ�E���^���Z
    m_SoundResource->AddReference( );

    return *this;
}
