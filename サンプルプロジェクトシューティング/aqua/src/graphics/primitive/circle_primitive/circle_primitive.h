
/*!
 *  @file       circle_primitive.h
 *  @brief      �~�`��N���X
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
     *  @class      CCirclePrimitive
     *
     *  @brief      �~�`��N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CCirclePrimitive
        : public aqua::core::IDrawObject
    {
    public:
        //! ���S���W
        aqua::CVector2      center;
        //! ���a
        float               radius;
        //! �~���`�����钸�_��
        int                 vertex_count;
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
        CCirclePrimitive( void );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CCirclePrimitive( void ) = default;

        /*!
         *  @brief      ������
         *
         *  @param[in]  center          �ʒu(����)
         *  @param[in]  radius          ��
         *  @param[in]  vertex_count    ����
         *  @param[in]  color           �F
         *  @param[in]  fill            �h��Ԃ��t���O
         *  @param[in]  thickness       ���̑���
         *  @param[in]  blend_mode      �A���t�@�u�����h
         */
        void    Setup(const aqua::CVector2& center_, float radius_ = 1.0f, int vertex_count_ = 36, const aqua::CColor& color_ = 0xffffffff, bool fill_ = true, float thickness_ = 1.0f, aqua::ALPHABLEND blend_mode_ = aqua::ALPHABLEND::ALPHA);

        /*!
         *  @brief      �`��
         */
        void    Draw( void );
    };
}
