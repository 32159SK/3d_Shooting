
/*!
 *  @file       circle_primitive.cpp
 *  @brief      �~�`��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "circle_primitive.h"
#include "..\..\..\debug\debug.h"

/*
 *  �R���X�g���N�^
 */
aqua::CCirclePrimitive::
CCirclePrimitive( void )
    : center( CVector2::ZERO )
    , radius( 0.0f )
    , vertex_count( 36 )
    , color( aqua::CColor::WHITE )
    , fill( TRUE )
    , thickness( 1.0f )
    , blend_mode( aqua::ALPHABLEND::ALPHA )
{
}

/*
 *  ������
 */
void
aqua::CCirclePrimitive::
Setup(const aqua::CVector2& center_, float radius_, int vertex_count_, const aqua::CColor& color_, bool fill_ , float thickness_ , aqua::ALPHABLEND blend_mode_)
{
    center          = center_;
    radius          = radius_;
    vertex_count    = vertex_count_;
    color           = color_;
    fill            = fill_;
    thickness       = thickness_;
    blend_mode      = blend_mode_;
}

/*
 *  �`��
 */
void
aqua::CCirclePrimitive::
Draw( void )
{
    // ��\���̎��͕`�悵�Ȃ�
    if( !visible ) return;

    // �A���t�@�u�����h�ݒ�
    SetDrawBlendMode( (int)blend_mode, color.alpha );

    // �`��
    DrawCircleAA( center.x, center.y, radius, vertex_count, color.GetColor(), ( fill ? TRUE : FALSE ), thickness );

    // �A���t�@�u�����h���[�h���f�t�H���g�ɖ߂�
    SetDrawBlendMode((int)aqua::ALPHABLEND::ALPHA, aqua::CColor::MAX_COLOR );
}
