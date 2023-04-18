
/*!
 *  @file       triangle_primitive.cpp
 *  @brief      �O�p�`�`��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "triangle_primitive.h"
#include "..\..\..\debug\debug.h"

/*
 *  �R���X�g���N�^
 */
aqua::CTrianglePrimitive::
CTrianglePrimitive( void )
    : pointA( CVector2::ZERO )
    , pointB( CVector2::ZERO )
    , pointC( CVector2::ZERO )
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
aqua::CTrianglePrimitive::
Setup(const aqua::CVector2& pointA_, const aqua::CVector2& pointB_, const aqua::CVector2& pointC_, const aqua::CColor& color_, bool fill_, float thickness_, aqua::ALPHABLEND blend_mode_)
{
    pointA      = pointA_;
    pointB      = pointB_;
    pointC      = pointC_;
    color       = color_;
    fill        = fill_;
    thickness   = thickness_;
    blend_mode  = blend_mode_;
}

/*
 *  �`��
 */
void
aqua::CTrianglePrimitive::
Draw( void )
{
    // ��\���̎��͕`�悵�Ȃ�
    if( !visible ) return;

    // �A���t�@�u�����h�ݒ�
    SetDrawBlendMode((int)blend_mode, color.alpha );

    // �`��
    DrawTriangleAA( pointA.x, pointA.y, pointB.x, pointB.y, pointC.x, pointC.y, color.GetColor(), ( fill ? TRUE : FALSE ), thickness );

    // �A���t�@�u�����h���[�h���f�t�H���g�ɖ߂�
    SetDrawBlendMode((int)aqua::ALPHABLEND::ALPHA, aqua::CColor::MAX_COLOR );
}
