
/*!
 *  @file       line_primitive_3d.h
 *  @brief      3D�����`��N���X
 *  @author     Toshihito Ohashi
 *  @date       2022/03/29
 *  @version    7.17
 *
 *  Copyright (c) 2021-2022, Toshihito Ohahsi. All rights reserved.
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
     *  @class      CLinePrimitive3D
     *
     *  @brief      �����`��N���X
     *
     *  @author     Toshihito Ohashi
     *
     *  @date       2022/03/29
     *
     *  @version    7.17
     */
    class CLinePrimitive3D
        : public aqua::core::IDrawObject, public CCollision
    {
    public:
        //! �ʒuA
        aqua::CVector3      pointA;
        //! �ʒuB
        aqua::CVector3      pointB;
        //! �F
        aqua::CColor        color;
        //! �A���t�@�u�����h���[�h
        aqua::ALPHABLEND    blend_mode;

        /*!
         *  @brief      �R���X�g���N�^
         */
        CLinePrimitive3D(void);

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CLinePrimitive3D(void) = default;

        /*!
         *  @brief      ������
         *
         *  @param[in]  pointA          �ʒuA
         *  @param[in]  pointB          �ʒuB
         *  @param[in]  color           �F
         *  @param[in]  thickness       ���̑���
         *  @param[in]  blend_mode      �A���t�@�u�����h
         */
        void    Setup(const aqua::CVector3& pointA_, const aqua::CVector3& pointB_, const aqua::CColor& color_ = 0xffffffff, aqua::ALPHABLEND blend_mode_ = aqua::ALPHABLEND::ALPHA);

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
