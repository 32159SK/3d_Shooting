
/*!
 *  @file       video.cpp
 *  @brief      �r�f�I�Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "video.h"
#include "video_manager\video_manager.h"
#include "..\..\utility\memory\memory.h"

/*
 *  �R���X�g���N�^
 */
aqua::CVideo::
CVideo( void )
    : m_VideoResource( nullptr )
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
aqua::CVideo::
CVideo( const aqua::CVideo& video )
{
    if( m_VideoResource )
        m_VideoResource->RemoveReference( );

    m_VideoResource = video.m_VideoResource;

    // �Q�ƃJ�E���^���Z
    m_VideoResource->AddReference( );
}

/*
 *  �r�f�I�̓ǂݍ���
 */
void
aqua::CVideo::
Load( const std::string& file_name )
{
    // �r�f�I���\�[�X�ޔ�
    core::CVideoResource* video = m_VideoResource;

    // �r�f�I�}�l�[�W������r�f�I�����[�h
    m_VideoResource = core::CVideoManager::GetInstance( ).Load( file_name );

    if( video )
    {
        int count = video->RemoveReference( );

        // �O�̃r�f�I�̎Q�ƃJ�E���^���Ȃ��Ȃ�������
        if( count <= 0 )
            core::CVideoManager::GetInstance( ).Unload( video );
    }
}

/*
 *  �r�f�I�̉��
 */
void
aqua::CVideo::
Unload( void )
{
    // �r�f�I���
    if( m_VideoResource )
        core::CVideoManager::GetInstance( ).Unload( m_VideoResource );

    m_VideoResource = nullptr;
}

/*
 *  ������Z�q�̃I�[�o�[���[�h
 */
aqua::CVideo&
aqua::CVideo::
operator=( const aqua::CVideo& video )
{
    // �r�f�I�������Ă�����Q�Ƃ����Z
    if( m_VideoResource )
        m_VideoResource->RemoveReference( );

    m_VideoResource = video.m_VideoResource;

    // �Q�ƃJ�E���^���Z
    m_VideoResource->AddReference( );

    return *this;
}
