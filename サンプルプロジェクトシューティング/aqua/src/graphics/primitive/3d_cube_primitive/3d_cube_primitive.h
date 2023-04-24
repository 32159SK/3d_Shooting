
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
     *  @class      CCubePrimitive3D
     *
     *  @brief      �����`��N���X
     *
     *  @author     Kazuto Shimazaki
     *
     *  @date       2023/04/14
     *
     *  @version    7.17
     */
    class CCubePrimitive
        : public aqua::core::IDrawObject, public CCollision
    {
    public:
        //! ���S���W
        aqua::CVector3      position;
        //! ��
        float               width;
        //! ����
        float               height;
        //! ���s
        float               depth;
        //! ������]�p�x
        float           m_VRotate;
        //! ������]�p�x
        float           m_HRotate;
        //! �P���]�p�x
        float           m_TRotate;

        //! �F
        aqua::CColor        color;
        //! ���ˌ��F
        aqua::CColor        spc_color;
        //! �h��ׂ�
        bool                fill;
        //! ���_���W���
        tagVERTEX3D         vertex[8];


        /*!
         *  @brief      �R���X�g���N�^
         */
        CCubePrimitive(void);

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CCubePrimitive(void) = default;
       
        /*!
         *  @brief      ������
         *
         *  @param[in]  center_pos      ���S���W
         *  @param[in]  width_          ��
         *  @param[in]  height_         ����
         *  @param[in]  depth           ���s
         *  @param[in]  color_          �F
         *  @param[in]  spc_color_      ���ˌ��F
         *  @param[in]  fill_           �h��ׂ�
         */
        void    Setup(const aqua::CVector3& center_pos, float width_, float height_, float depth, const aqua::CColor& color_ = 0xffffffff, const aqua::CColor& spc_color_ = 0xffffffff, bool fill_ = true);

        /*!
         *  @brief      �ό`
         */
        void    Transform(void);

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

        /*!
         *  @brief      �Փ˔���
         *  @param[in]  center_pos      ���̒��S
         *  @param[in]  r               ���a
         */
        bool    CheckCollision(CVector3& center_pos, float r)override;

    private:
        WORD                index[36];
        static const int    polygon_count;
        static const int    vertex_count;
        static const int    index_count;

    };
}
