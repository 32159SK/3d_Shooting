
/*!
 *  @file       sprite.cpp
 *  @brief      2D�e�N�X�`���`��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "sprite.h"
#include "..\..\debug\debug.h"

/*
 *  �R���X�g���N�^
 */
aqua::CSprite::
CSprite( void )
    : position( CVector2::ZERO )
    , rect( CRect::ZERO )
    , anchor( CVector2::ZERO )
    , scale( CVector2::ONE )
    , rotation( 0.0f )
    , color( aqua::CColor::WHITE )
    , blend_mode( aqua::ALPHABLEND::ALPHA )
    , m_GraphicFilter( aqua::GRAPHIC_FILTER::NONE )
    , m_GaussFilterPixelWitdh( 0 )
    , m_GaussFilterParam( 0 )
{
}

/*
 *  ����
 */
void
aqua::CSprite::
Create( const std::string& file_name )
{
    Delete();

    m_Texture.Load( file_name );

    // �ǂݍ��ݔ͈͂�ݒ�
    rect.left   = 0;
    rect.top    = 0;
    rect.right  = m_Texture.GetWidth( );
    rect.bottom = m_Texture.GetHeight( );
}

/*
 *  ����
 */
void
aqua::CSprite::
Create( const CSurface& surface )
{
    Delete();

    m_Texture = surface.m_Texture;

    // �ǂݍ��ݔ͈͂�ݒ�
    rect.left   = 0;
    rect.top    = 0;
    rect.right  = m_Texture.GetWidth( );
    rect.bottom = m_Texture.GetHeight( );
}

/*
 *  ���
 */
void
aqua::CSprite::
Delete( void )
{
    m_Texture.Unload( );
}

/*
 *  �`��
 */
void
aqua::CSprite::
Draw( void )
{
    // �e�N�X�`�����ǂݍ��܂�Ă��Ȃ���Ε`�悵�Ȃ�
    if( !m_Texture.IsEnable( ) ) return;

    // ��\���̎��͕`�悵�Ȃ�
    if( !visible ) return;

    // �A���t�@�u�����h�ݒ�
    SetDrawBlendMode((int)blend_mode, color.alpha );

    // �P�x�ݒ�
    SetDrawBright( color.red, color.green, color.blue );

    // �e�N�X�`�����\�[�X�n���h���擾
    int handle = m_Texture.GetResourceHandle( );

    switch( m_GraphicFilter )
    {
    case aqua::GRAPHIC_FILTER::GAUSS:
        {
            // ��̃X�N���[�����쐬
            handle = MakeScreen( m_Texture.GetWidth( ), m_Texture.GetHeight( ), true );

            GraphFilterBlt( m_Texture.GetResourceHandle( ), handle, DX_GRAPH_FILTER_GAUSS, m_GaussFilterPixelWitdh, m_GaussFilterParam );
        }
        break;
    }

    // �`��
    DrawRectRotaGraph3F( position.x + anchor.x, position.y + anchor.y, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, anchor.x, anchor.y, scale.x, scale.y, rotation, handle, TRUE );

    // �P�x���f�t�H���g�ɖ߂�
    SetDrawBright( aqua::CColor::MAX_COLOR, aqua::CColor::MAX_COLOR, aqua::CColor::MAX_COLOR );

    // �A���t�@�u�����h���[�h���f�t�H���g�ɖ߂�
    SetDrawBlendMode((int)aqua::ALPHABLEND::ALPHA, aqua::CColor::MAX_COLOR );

    // �n���h�����폜
    if( m_GraphicFilter != aqua::GRAPHIC_FILTER::NONE && handle != AQUA_DX_ERROR )
        DeleteGraph( handle );
}

/*
 *  �K�E�X�t�B���^�[�̓K�p
 */
void
aqua::CSprite::
ApplyGaussFilter( int pixel_width, int param )
{
    m_GraphicFilter = aqua::GRAPHIC_FILTER::GAUSS;

    m_GaussFilterPixelWitdh = pixel_width;

    m_GaussFilterParam = param;
}

/*
 *  �O���t�B�b�N�t�B���^�[�̉���
 */
void
aqua::CSprite::
UnsetGraphicFilter( void )
{
    m_GraphicFilter = aqua::GRAPHIC_FILTER::NONE;
}
