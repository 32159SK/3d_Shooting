
/*!
 *  @file       effekseer.cpp
 *  @brief      Effekseer�N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include <windows.h>
#include "effekseer.h"
#include "effekseer_manager\effekseer_manager.h"

/*
 *  �R���X�g���N�^
 */
aqua::CEffekseer::
CEffekseer( void )
    : m_EffekseerResource( nullptr )
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
aqua::CEffekseer::
CEffekseer( const aqua::CEffekseer& effect )
    : m_EffekseerResource( nullptr )
{
    if( m_EffekseerResource )
        m_EffekseerResource->RemoveReference( );

    m_EffekseerResource = effect.m_EffekseerResource;

    // �Q�ƃJ�E���^���Z
    m_EffekseerResource->AddReference( );
}

/*
 *  Effekseer�ǂݍ���
 */
void
aqua::CEffekseer::
Load( const std::string& file_name )
{
    // Effekseer���\�[�X�ޔ�
    core::CEffekseerResource* effect = m_EffekseerResource;

    // Effekseer�}�l�[�W������Effekseer�擾
    m_EffekseerResource = core::CEffekseerManager::GetInstance( ).Load( file_name );

    if( effect )
    {
        int count = effect->RemoveReference( );

        // �O��Effekseer�̎Q�ƃJ�E���^���Ȃ��Ȃ�������
        if( count <= 0 )
            core::CEffekseerManager::GetInstance( ).Unload( effect );
    }
}

/*
 *  Effekseer���
 */
void
aqua::CEffekseer::
Unload( void )
{
    // Effekseer���
    if( m_EffekseerResource )
        core::CEffekseerManager::GetInstance( ).Unload( m_EffekseerResource );

    m_EffekseerResource = nullptr;
}

/*
 *  ������Z�q�̃I�[�o�[���[�h
 */
aqua::CEffekseer&
aqua::CEffekseer::
operator=( const aqua::CEffekseer& effect )
{
    // Effekseer�������Ă�����Q�Ƃ����Z
    if( m_EffekseerResource )
        m_EffekseerResource->RemoveReference( );

    m_EffekseerResource = effect.m_EffekseerResource;

    // �Q�ƃJ�E���^���Z
    m_EffekseerResource->AddReference( );

    return *this;
}
