
/*!
 *  @file       camera.h
 *  @brief      �J����
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include<DxLib.h>
#include"../../mathematics/vector/vector.h"

namespace aqua
{

    /*!
     *  @brief      �p�x�̌���
     */
    enum ANGLE
    {
        V,          //! �������� 
        H,          //! ��������
        T           //! �P�����
    };


    /*!
     *  @class      CCamera
     *
     *  @brief      �J����
     *
     *  @author     Kazuto Shimazaki
     *
     *  @date       2023/04/10
     *
     *  @version    7.17
     */
    class CCamera
    {
    public:
        //! ��O�N���b�v����
        float           m_Near;
        //! ���N���b�v����
        float           m_Far;
        //! ����p
        float           m_Fov;
        //! ������]�p�x
        float           m_VRotate;
        //! ������]�p�x
        float           m_HRotate;
        //! �P���]�p�x
        float           m_TRotate;
        //! �����_����J�����܂ł̋���
        float           m_Distace;
        //! �J�����̈ʒu
        aqua::CVector3  m_Position;
        //! �J�����̒����_(���Ă�����W)
        aqua::CVector3  m_Target;
        //! �J�����̏����
        aqua::CVector3  m_CameraUp;

        /*!
         *  @brief  �R���X�g���N�^
         */
        CCamera(void);

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CCamera(void) = default;

        /*!
         *  @brief  �J�����̃Z�b�g
         *
         *  @param[in]  ne    ��O
         *  @param[in]  fa    ��
         */
        void SetCamera(float ne,float fa);

        /*!
         *  @brief  �J�����̃Z�b�g
         *
         *  @param[in]  ne    ��O
         *  @param[in]  fa    ��
         *  @param[in]  pos   �ʒu
         *  @param[in]  tag   �����_
         */
        void SetCamera(float ne, float fa, aqua::CVector3 pos, aqua::CVector3 tag);

        /*!
         *  @brief  �J�����̃Z�b�g
         *
         *  @param[in]  ne    ��O
         *  @param[in]  fa    ��
         *  @param[in]  pos   �ʒu
         *  @param[in]  tag   �����_
         *  @param[in]  up    �����
         */
        void SetCamera(float ne, float fa, aqua::CVector3 pos, aqua::CVector3 tag, aqua::CVector3 up);

        /*!
         *  @brief  �J�����̃Z�b�g(������)
         */
        void SetCamera(void);

        /*!
         *  @brief      �p�x�̕ύX
         * 
         *  @param[in]  angle  �ύX����p�x�̌���
         *  @param[in]  rad    �p�x�̑傫��
         */
        void        SetAngle(ANGLE angle, float rad);


        void        Update(void);

    };

}