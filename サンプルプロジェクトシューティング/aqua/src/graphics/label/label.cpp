
/*!
 *  @file       label.cpp
 *  @brief      ������`��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "label.h"
#include "..\..\debug\debug.h"

/*
 *  �R���X�g���N�^
 */
aqua::CLabel::
CLabel( void )
    : position( CVector2::ZERO )
    , color( CColor::WHITE )
    , edge_color( CColor::BLACK )
    , blend_mode( aqua::ALPHABLEND::ALPHA )
{
    text.clear( );
}

/*
 *  ����
 */
void
aqua::CLabel::
Create( int size )
{
    Create( size, 0 );
}

/*
 *  ����
 */
void
aqua::CLabel::
Create( int size, int edge_bold )
{
    m_Font.Create( size, edge_bold, false, aqua::FONT_FAMILY_ID::MS_GOTHIC );
}

/*
 *  ����
 */
void
aqua::CLabel::
Create(int size, int edge_bold, bool anti_aliasing)
{
    m_Font.Create(size, edge_bold, anti_aliasing, aqua::FONT_FAMILY_ID::MS_GOTHIC);
}

/*
 *  ����
 */
void
aqua::CLabel::
Create( int size, int edge_bold, bool anti_aliasing, aqua::FONT_FAMILY_ID family_id )
{
    m_Font.Create( size, edge_bold, anti_aliasing, family_id );
}

/*
 *  �`��
 */
void
aqua::CLabel::
Draw( void )
{
    // �t�H���g����������Ă��Ȃ�
    if( !m_Font.IsEnable( ) )
        return;

    // ��\���̎��͕`�悵�Ȃ�
    if( !visible ) return;

    // �A���t�@�u�����h�ݒ�
    SetDrawBlendMode((int)blend_mode, color.alpha );

    // ������`��
    DrawStringToHandle( (int)position.x, (int)position.y, text.c_str( ), color.GetColor( ), m_Font.GetResourceHandle( ), edge_color.GetColor( ) );

    // �A���t�@�u�����h���[�h���f�t�H���g�ɖ߂�
    SetDrawBlendMode((int)aqua::ALPHABLEND::ALPHA, aqua::CColor::MAX_COLOR );
}

/*
 *  �폜
 */
void
aqua::CLabel::
Delete( void )
{
    m_Font.Delete( );
}

/*
 *  ������̕��擾
 */
int
aqua::CLabel::
GetTextWidth( void ) const
{
    return GetDrawStringWidthToHandle( text.c_str( ), (int)text.length( ), m_Font.GetResourceHandle( ) );
}

/*
 *  �t�H���g�̍����擾
 */
int
aqua::CLabel::
GetFontHeight( void ) const
{
    return m_Font.GetHeight( );
}

/*
 *  ���\�[�X�n���h���擾
 */
int
aqua::CLabel::
GetResourceHandle( void ) const
{
    return m_Font.GetResourceHandle( );
}
