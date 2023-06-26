
/*!
 *  @file       3d_sphere_primitive.h
 *  @brief      ���`�`��N���X
 *  @author     Kazuya Maruyama
 *  @date       2023/04/13
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>
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
     *  @class      CCapsulePrimitive
     *
     *  @brief      ���`�`��N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CCapsulePrimitive
        : public aqua::core::IDrawObject, public CCollision
    {
    public:
        //! ��_���̈�_�̈ʒuA
        aqua::CVector3      Apos;
        //! ��_���̈�_�̈ʒuB
        aqua::CVector3      Bpos;
        //! �|���S���ׂ̍���
        int                 div_num;
        //! ���a
        float               radius;
        //! A�𒆐S�Ƃ���������]�p�x
        float               m_VRotate;
        //! A�𒆐S�Ƃ���������]�p�x
        float               m_HRotate;
        //! A�𒆐S�Ƃ����P���]�p�x
        float               m_TRotate;
        //! �F
        aqua::CColor        color;
        //! ���ˌ��F
        aqua::CColor        spc_color;

        //! ���g��h��Ԃ�
        bool                fill;

        /*!
         *  @brief      �R���X�g���N�^
         */
        CCapsulePrimitive(void);

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CCapsulePrimitive(void) = default;

        /*!
         *  @brief      ������
         *
         *  @param[in]  A_pos       ��_���̈�_�̈ʒuA
         *  @param[in]  B_pos       ��_���̈�_�̈ʒuA
         *  @param[in]  r           ���a
         *  @param[in]  divnum      �|���S���ׂ̍���
         *  @param[in]  color       �F
         *  @param[in]  spc_color   ���ˌ��F
         *  @param[in]  fill        �h��ׂ��t���O
         */
        void    Setup(const aqua::CVector3& A_pos,const aqua::CVector3& B_pos, float r, int divnum = 10, const aqua::CColor& color_ = aqua::CColor::CYAN, const aqua::CColor& spc_color_ = aqua::CColor::WHITE, bool fill_ = true);

        /*!
         *  @brief      �`��
         */
        void    Draw(void);

        /*!
         *  @brief      �Փ˔���
         *  @param[in]  pointA          �n�_
         *  @param[in]  pointB          �I�_
         */
        bool    CheckCollision(CVector3& pointA, CVector3& pointB)override;

    };
}
