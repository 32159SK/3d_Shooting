
/*!
 *  @file       rect.h
 *  @brief      ��`�N���X
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
     *  @class      CRect
     *
     *  @brief      ��`�N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CRect
    {
    public:
        //! ���[
        int     left;
        //! ��[
        int     top;
        //! �E�[
        int     right;
        //! ���[
        int     bottom;

        /*!
         *  @brief      �R���X�g���N�^
         */
        CRect( void );

        /*!
         *  @brief      �R���X�g���N�^
         *
         *  @param[in]  rect    ��`�N���X
         */
        CRect( const CRect& rect );

        /*!
         *  @brief      �R���X�g���N�^
         *
         *  @param[in]  left    ����
         *  @param[in]  top     �㑤
         *  @param[in]  right   �E��
         *  @param[in]  bottom  ����
         */
        CRect( int left, int top, int right, int bottom );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CRect( void ) = default;

        /*!
         *  @brief      ��`�̕����擾
         *
         *  @return     ��`�̕�
         */
        int     GetWidth( void ) const;

        /*!
         *  @brief      ��`�̍������擾
         *
         *  @return     ��`�̍���
         */
        int     GetHeight( void ) const;

        /*!
         *  @brief      �f�o�b�O���O�ɒl��\������
         */
        void    DebugLog( void );

        //! �v�f�����ׂ�0
        static const CRect  ZERO;
    };
}
