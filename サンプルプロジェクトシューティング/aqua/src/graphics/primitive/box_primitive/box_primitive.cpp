
/*!
 *  @file       box_primitive.cpp
 *  @brief      ��`�`��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "box_primitive.h"
#include "..\..\..\debug\debug.h"

/*
 *  �R���X�g���N�^
 */
aqua::CBoxPrimitive::
CBoxPrimitive( void )
    : position( CVector2::ZERO )
    , width( 0.0f )
    , height( 0.0f )
    , color( aqua::CColor::WHITE )
    , fill( true )
    , thickness( 1.0f )
    , blend_mode( aqua::ALPHABLEND::ALPHA )
{
}

/*
 *  ������
 */
void
aqua::CBoxPrimitive::
Setup(const aqua::CVector2& position_, float width_, float height_, const aqua::CColor& color_, bool fill_, float thickness_, aqua::ALPHABLEND blend_mode_)
{
    position      = position_;
    width         = width_;
    height        = height_;
    color         = color_;
    fill          = fill_;
    thickness     = thickness_;
    blend_mode    = blend_mode_;
}

/*
 *  �`��
 */
void
aqua::CBoxPrimitive::
Draw( void )
{
    // ��\���̎��͕`�悵�Ȃ�
    if( !visible ) return;

    // �A���t�@�u�����h�ݒ�
    SetDrawBlendMode((int)blend_mode, color.alpha );

    // �`��
    DrawBoxAA( position.x, position.y, position.x + width, position.y + height, color.GetColor(), ( fill ? TRUE : FALSE ), thickness );

    // �A���t�@�u�����h���[�h���f�t�H���g�ɖ߂�
    SetDrawBlendMode((int)aqua::ALPHABLEND::ALPHA, aqua::CColor::MAX_COLOR );
}
