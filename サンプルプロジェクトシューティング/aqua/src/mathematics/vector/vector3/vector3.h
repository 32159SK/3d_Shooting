
/*!
 *  @file       vector3.h
 *  @brief      3�����x�N�g��
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include<DxLib.h>

namespace aqua
{
    using _Vector3 = DxLib::VECTOR;
    using _Matrix = DxLib::MATRIX;

    /*!
     *  @class      CVector3
     *
     *  @brief      3�����x�N�g���N���X
     *
     *  @author     Kazuto Shimazaki
     *
     *  @date       2023/04/10
     *
     *  @version    7.17
     */
    class CVector3 : public VECTOR
	{
	public:
        /*!
         *  @brief  �R���X�g���N�^
         */
        CVector3(void);

        /*!
         *  @brief  �R���X�g���N�^
         *
         *  @param[in]  x   X����
         *  @param[in]  y   Y����
         */
        CVector3(float x, float y, float z);

        /*!
         *  @brief  �R���X�g���N�^
         *
         *  @param[in]  v  �x�N�g��
         */
        CVector3(const _Vector3& v);

        /*!
         *  @brief  �f�X�g���N�^
         */
        ~CVector3(void) = default;


        /*!
         *  @brief      �x�N�g���̐��K��<br>
         *              ���g�̃x�N�g�������K�������
         *
         *  @return     ���K�����ꂽ�x�N�g��
         */
        CVector3            Normalize(void);

        /*!
         *  @brief      �x�N�g���̐��K��
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     ���K�����ꂽ�x�N�g��
         */
        static CVector3     Normalize(const _Vector3& v);

        /*!
         *  @brief      �x�N�g���̑傫���擾
         *
         *  @return     �x�N�g���̑傫��
         */
        float               Length(void);

        /*!
         *  @brief      �x�N�g���̑傫���擾
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���̑傫��
         */
        static float        Length(const _Vector3& v);

        /*!
         *  @brief      2�̃x�N�g���̓���<br>
         *              dot = vA�EvB
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     ����
         */
        static float        Dot(const _Vector3& vA, const _Vector3& vB);

        /*!
         *  @brief      2�̃x�N�g���̊O��<br>
         *              cross = vA�~vB
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �O��
         */
        static CVector3        Cross(const _Vector3& vA, const _Vector3& vB);

        /*!
         *  @brief      ������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        CVector3& operator=(const _Vector3& v)
        {
            x = v.x;
            y = v.y;
            z = v.z;

            return *this;
        }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        CVector3& operator+=(const _Vector3& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;

            return *this;
        }
        

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        CVector3& operator-=(const _Vector3& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;

            return *this;
        }

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  scalar  �X�J���[�l
         *
         *  @return     �x�N�g���N���X
         */
        CVector3& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;

            return *this;
        }

        /*!
         *  @brief      �������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     ��̃x�N�g����������
         *  @retval     true    ������
         *  @retval     false   �������Ȃ�
         */
        bool                operator==(const _Vector3& v) const { return (x == v.x && y == v.y && z == v.z); }

        /*!
         *  @brief      �s�����Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     ��̃x�N�g�����������Ȃ�
         *  @retval     true    �������Ȃ�
         *  @retval     false   ������
         */
        bool                operator!=(const _Vector3& v) const { return (x != v.x || y != v.y && z != v.z); }

        /*!
         *  @brief      ���������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator+(const _Vector3& v) { return v; }

        /*!
         *  @brief      ���������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator-(const _Vector3& v) { return CVector3(-v.x, -v.y,-v.z); }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator+(const _Vector3& vA, const _Vector3& vB) { return aqua::CVector3(vA.x + vB.x, vA.y + vB.y, vA.z + vB.z); }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator-(const _Vector3& vA, const _Vector3& vB) { return CVector3(vA.x - vB.x, vA.y - vB.y, vA.z - vB.z); }

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator*(const _Vector3& vA, const _Vector3& vB) { return CVector3(vA.x * vB.x, vA.y * vB.y, vA.z * vB.z); }

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v       �x�N�g���N���X
         *  @param[in]  scalar  �X�J���[�l
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator*(const _Vector3& v, float scalar) { return CVector3(v.x * scalar, v.y * scalar, v.z * scalar); }

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  scalar  �X�J���[�l
         *  @param[in]  v       �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator*(float scalar, const _Vector3& v) { return CVector3(v.x * scalar, v.y * scalar, v.z * scalar); }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator/(const _Vector3& vA, const _Vector3& vB) { return CVector3(vA.x / vB.x, vA.y / vB.y, vA.z / vB.z); }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v       �x�N�g���N���X
         *  @param[in]  scalar  �X�J���[�l
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator/(const _Vector3& v, float scalar) { return CVector3(v.x / scalar, v.y / scalar, v.z / scalar); }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  scalar  �X�J���[�l
         *  @param[in]  v       �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator/(float scalar, const _Vector3& v) { return CVector3(scalar / v.x, scalar / v.y, scalar / v.z); }


        inline CVector3& operator*=(const _Matrix& mat)
        {
            (*this) = VTransform(*this, mat);

            return *this;
        }

        friend CVector3 operator*(const _Vector3& v, const _Matrix& mat) { return VTransform(v ,mat); }

        /*!
         *  @brief      �f�o�b�O���O�ɒl��\������
         */
        void                DebugLog(void);


        // ���������ׂ�0�̃x�N�g��
        static const CVector3   ZERO;
        // ���������ׂ�1�̃x�N�g��
        static const CVector3   ONE;

        // �P�����̃x�N�g��
        static const CVector3 FRONT;
        static const CVector3 BACK;
        static const CVector3 UP;
        static const CVector3 DOWN;
        static const CVector3 RIGHT;
        static const CVector3 LEFT;
	};
}