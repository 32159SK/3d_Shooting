
/*!
 *  @file       font.cpp
 *  @brief      �t�H���g�N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "font.h"
#include "font_manager\font_manager.h"

/*
 *  �R���X�g���N�^
 */
aqua::CFont::
CFont( void )
    : m_FontResource( nullptr )
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
aqua::CFont::
CFont( const aqua::CFont& mesh )
    : m_FontResource( nullptr )
{
    if( m_FontResource )
        m_FontResource->RemoveReference( );

    m_FontResource = mesh.m_FontResource;

    // �Q�ƃJ�E���^���Z
    m_FontResource->AddReference( );
}

/*
 *  �t�H���g�ǂݍ���
 */
void
aqua::CFont::
Create( int size, int edge_bold, bool anti_aliasing, aqua::FONT_FAMILY_ID family_id )
{
    // �t�H���g���\�[�X�ޔ�
    core::CFontResource* font = m_FontResource;

    // �t�H���g�}�l�[�W������t�H���g�擾
    m_FontResource = core::CFontManager::GetInstance( ).Create( size, edge_bold, anti_aliasing, family_id );

    if( font )
    {
        int count = font->RemoveReference( );

        // �O�̃t�H���g�̎Q�ƃJ�E���^���Ȃ��Ȃ�������
        if( count <= 0 )
            core::CFontManager::GetInstance( ).Delete( font );
    }
}

/*
 *  �t�H���g���
 */
void
aqua::CFont::
Delete( void )
{
    // �t�H���g���
    if( m_FontResource )
        core::CFontManager::GetInstance( ).Delete( m_FontResource );

    m_FontResource = nullptr;
}

/*
 *  ������Z�q�̃I�[�o�[���[�h
 */
aqua::CFont&
aqua::CFont::
operator=( const aqua::CFont& font )
{
    // �t�H���g�������Ă�����Q�Ƃ����Z
    if( m_FontResource )
        m_FontResource->RemoveReference( );

    m_FontResource = font.m_FontResource;

    // �Q�ƃJ�E���^���Z
    m_FontResource->AddReference( );

    return *this;
}
