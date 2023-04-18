
/*!
 *  @file       triangle_primitive.h
 *  @brief      �O�p�`�`��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>
#include "..\..\alphablend\alphablend.h"
#include "..\..\draw_object\draw_object.h"
#include "..\..\..\mathematics\mathematics.h"
#include "..\..\color\color.h"
#include "..\..\..\utility\utility.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CTrianglePrimitive
     *
     *  @brief      �O�p�`�`��N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CTrianglePrimitive
        : public aqua::core::IDrawObject
    {
    public:
        //! �ʒuA
        aqua::CVector2      pointA;
        //! �ʒuB
        aqua::CVector2      pointB;
        //! �ʒuC
        aqua::CVector2      pointC;
        //! �F
        aqua::CColor        color;
        //! ���g��h��Ԃ�
        bool                fill;
        //! ����
        float               thickness;
        //! �A���t�@�u�����h���[�h
        aqua::ALPHABLEND    blend_mode;

        /*!
         *  @brief      �R���X�g���N�^
         */
        CTrianglePrimitive( void );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CTrianglePrimitive( void ) = default;

        /*!
         *  @brief      ������
         *
         *  @param[in]  pointA          �ʒuA
         *  @param[in]  pointB          �ʒuB
         *  @param[in]  pointC          �ʒuC
         *  @param[in]  color           �F
         *  @param[in]  thickness       ���̑���
         *  @param[in]  blend_mode      �A���t�@�u�����h
         */
        void    Setup(const aqua::CVector2& pointA_, const aqua::CVector2& pointB_, const aqua::CVector2& pointC_, const aqua::CColor& color_ = 0xffffffff, bool fill_ = true, float thickness_ = 1.0f, aqua::ALPHABLEND blend_mode_ = aqua::ALPHABLEND::ALPHA);

        /*!
         *  @brief      �`��
         */
        void    Draw( void );
    };
}
