
/*!
 *  @file       box_primitive.h
 *  @brief      ��`�`��N���X
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
     *  @class      CBoxPrimitive
     *
     *  @brief      ��`�`��N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CBoxPrimitive
        : public aqua::core::IDrawObject
    {
    public:
        //! �ʒu
        aqua::CVector2      position;
        //! ��
        float               width;
        //! ����
        float               height;
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
        CBoxPrimitive( void );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CBoxPrimitive( void ) = default;

        /*!
         *  @brief      ������
         *
         *  @param[in]  position    �ʒu(����)
         *  @param[in]  width       ��
         *  @param[in]  height      ����
         *  @param[in]  color       �F
         *  @param[in]  fill        �h��Ԃ��t���O
         *  @param[in]  thickness   ���̑���
         *  @param[in]  blend_mode  �A���t�@�u�����h
         */
        void    Setup(const aqua::CVector2& position_, float width_ = 1.0f, float height_ = 1.0f, const aqua::CColor& color_ = 0xffffffff, bool fill_ = true, float thickness_ = 1.0f, aqua::ALPHABLEND blend_mode_ = aqua::ALPHABLEND::ALPHA);

        /*!
         *  @brief      �`��
         */
        void    Draw( void );
    };
}
