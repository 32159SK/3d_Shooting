
/*!
 *  @file       vector2.h
 *  @brief      �񎟌��x�N�g��
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

/*!
 *  @brief  aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CVector2
     *
     *  @brief      �񎟌��x�N�g���N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CVector2
    {
    public:
        //! X����
        float x;
        //! Y����
        float y;

        /*!
         *  @brief  �R���X�g���N�^
         */
        CVector2( void );

        /*!
         *  @brief  �R���X�g���N�^
         *
         *  @param[in]  x   X����
         *  @param[in]  y   Y����
         */
        CVector2( float x, float y );

        /*!
         *  @brief  �R���X�g���N�^
         *
         *  @param[in]  v  �x�N�g��
         */
        CVector2( const CVector2& v );

        /*!
         *  @brief  �f�X�g���N�^
         */
        ~CVector2( void ) = default;

        /*!
         *  @brief      �x�N�g���̐��K��<br>
         *              ���g�̃x�N�g�������K�������
         *
         *  @return     ���K�����ꂽ�x�N�g��
         */
        CVector2            Normalize( void );

        /*!
         *  @brief      �x�N�g���̐��K��
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     ���K�����ꂽ�x�N�g��
         */
        static CVector2     Normalize( const CVector2& v );

        /*!
         *  @brief      �x�N�g���̑傫���擾
         *
         *  @return     �x�N�g���̑傫��
         */
        float               Length( void );

        /*!
         *  @brief      �x�N�g���̑傫���擾
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���̑傫��
         */
        static float        Length( const CVector2& v );

        /*!
         *  @brief      2�̃x�N�g���̓���<br>
         *              dot = vA�EvB
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     ����
         */
        static float        Dot( const CVector2& vA, const CVector2& vB );

        /*!
         *  @brief      2�̃x�N�g���̊O��<br>
         *              cross = vA�~vB
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �O��
         */
        static float        Cross( const CVector2& vA, const CVector2& vB );

        /*!
         *  @brief      ������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        CVector2&           operator=( const CVector2& v )
        {
            x = v.x;
            y = v.y;

            return *this;
        }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        CVector2&           operator+=( const CVector2& v )
        {
            x += v.x;
            y += v.y;

            return *this;
        }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        CVector2&           operator-=( const CVector2& v )
        {
            x -= v.x;
            y -= v.y;

            return *this;
        }

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  scalar  �X�J���[�l
         *
         *  @return     �x�N�g���N���X
         */
        CVector2&           operator*=( float scalar )
        {
            x *= scalar;
            y *= scalar;

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
        bool                operator==( const CVector2& v ) const { return (x == v.x && y == v.y); }

        /*!
         *  @brief      �s�����Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     ��̃x�N�g�����������Ȃ�
         *  @retval     true    �������Ȃ�
         *  @retval     false   ������
         */
        bool                operator!=( const CVector2& v ) const { return (x != v.x || y != v.y); }

        /*!
         *  @brief      ���������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector2     operator+( const CVector2& v ) { return v; }

        /*!
         *  @brief      ���������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector2     operator-( const CVector2& v ) { return CVector2(-v.x, -v.y); }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector2     operator+(const CVector2& vA, const CVector2& vB) { return aqua::CVector2(vA.x + vB.x, vA.y + vB.y); }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector2     operator-(const CVector2& vA, const CVector2& vB) { return CVector2(vA.x - vB.x, vA.y - vB.y); }

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector2     operator*(const CVector2& vA, const CVector2& vB) { return CVector2(vA.x * vB.x, vA.y * vB.y); }

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v       �x�N�g���N���X
         *  @param[in]  scalar  �X�J���[�l
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector2     operator*(const CVector2& v, float scalar) { return CVector2(v.x * scalar, v.y * scalar); }

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  scalar  �X�J���[�l
         *  @param[in]  v       �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector2     operator*(float scalar, const CVector2& v) { return CVector2(v.x * scalar, v.y * scalar); }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector2     operator/(const CVector2& vA, const CVector2& vB) { return CVector2(vA.x / vB.x, vA.y / vB.y); }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v       �x�N�g���N���X
         *  @param[in]  scalar  �X�J���[�l
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector2     operator/(const CVector2& v, float scalar) { return CVector2(v.x / scalar, v.y / scalar); }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  scalar  �X�J���[�l
         *  @param[in]  v       �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector2     operator/(float scalar, const CVector2& v) { return CVector2(scalar / v.x, scalar / v.y); }

        /*!
         *  @brief      �f�o�b�O���O�ɒl��\������
         */
        void                DebugLog( void );

        //! ���������ׂ�0�̃x�N�g��
        static const CVector2   ZERO;
        //! ���������ׂ�1�̃x�N�g��
        static const CVector2   ONE;
    };
}
