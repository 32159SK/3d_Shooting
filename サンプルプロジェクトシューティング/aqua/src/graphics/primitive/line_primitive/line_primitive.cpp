
/*!
 *  @file       line_primitive.cpp
 *  @brief      �����`��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "line_primitive.h"
#include "..\..\..\debug\debug.h"

/*
 *  �R���X�g���N�^
 */
aqua::CLinePrimitive::
CLinePrimitive( void )
    : pointA( CVector2::ZERO )
    , pointB( CVector2::ZERO )
    , color( aqua::CColor::WHITE )
    , thickness( 1.0f )
    , blend_mode( aqua::ALPHABLEND::ALPHA )
{
}

/*
 *  ������
 */
void
aqua::CLinePrimitive::
Setup(const aqua::CVector2& pointA_, const aqua::CVector2& pointB_, const aqua::CColor& color_ , float thickness_ , aqua::ALPHABLEND blend_mode_ )
{
    pointA      = pointA_;
    pointB      = pointB_;
    color       = color_;
    thickness   = thickness_;
    blend_mode  = blend_mode_;
}

/*
 *  �`��
 */
void
aqua::CLinePrimitive::
Draw( void )
{
    // ��\���̎��͕`�悵�Ȃ�
    if( !visible ) return;

    // �A���t�@�u�����h�ݒ�
    SetDrawBlendMode((int)blend_mode, color.alpha );

    // �`��
    DrawLineAA( pointA.x, pointA.y, pointB.x, pointB.y, color.GetColor(), thickness );

    // �A���t�@�u�����h���[�h���f�t�H���g�ɖ߂�
    SetDrawBlendMode((int)aqua::ALPHABLEND::ALPHA, aqua::CColor::MAX_COLOR );
}
