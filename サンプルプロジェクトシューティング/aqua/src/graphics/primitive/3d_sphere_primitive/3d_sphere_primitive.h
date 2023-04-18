
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
     *  @class      CSpherePrimitive
     *
     *  @brief      ���`�`��N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CSpherePrimitive
        : public aqua::core::IDrawObject, public CCollision
    {
    public:
        //! �ʒu
        aqua::CVector3      position;
        //! �|���S���ׂ̍���
        int                 div_num;
        //! ���a
        float               radius;
        //! �F
        aqua::CColor        color;
        //! ���ˌ��F
        aqua::CColor        spc_color;

        //! ���g��h��Ԃ�
        bool                fill;

        /*!
         *  @brief      �R���X�g���N�^
         */
        CSpherePrimitive(void);

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CSpherePrimitive(void) = default;

        /*!
         *  @brief      ������
         *
         *  @param[in]  position    ���S���W
         *  @param[in]  r           ���a
         *  @param[in]  divnum      �|���S���ׂ̍���
         *  @param[in]  color       �F
         *  @param[in]  spc_color   ���ˌ��F
         *  @param[in]  fill        �h��ׂ��t���O
         */
        void    Setup(const aqua::CVector3& position_, float r, int divnum , const aqua::CColor& color_, const aqua::CColor& spc_color_, bool fill_ = true);

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
