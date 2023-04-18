
/*!
 *  @file       thread.h
 *  @brief      �X���b�h�Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <windows.h>

/*!
 *  @brief  aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      IThread
     *
     *  @brief      �X���b�h�x�[�X�N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class IThread
    {
    public:
        /*!
         *  @brief      �R���X�g���N�^
         */
        IThread( void );

        /*!
         *  @brief      �f�X�g���N�^
         */
        virtual ~IThread( void );

        /*!
         *  @brief      �X���b�h�ōs�������̎��s<br>
         *              �K���I�[�o�[���C�h���Ď���
         */
        virtual void    Run( void ) = 0;

        /*!
         *  @brief      �X���b�h���s�J�n
         */
        virtual void    Start( void );

        /*!
         *  @brief      �X���b�h��~(������~)
         */
        virtual void    Stop( void );

        /*!
         *  @brief      �X���b�h��~�Ƒҋ@<br>
         *              �X���b�h����~����܂őҋ@����
         */
        virtual void    StopAndWait( void );

        /*!
         *  @brief      �X���b�h�̋N���`�F�b�N
         *
         *  @retval     true    �N�����Ă���
         *  @retval     false   �N�����Ă��Ȃ�
         */
        virtual bool    IsRunning( void ) const;

        /*!
         *  @brief      �X���b�h�̗L����ԃ`�F�b�N
         *
         *  @retval     true    �L��
         *  @retval     false   ����
         */
        virtual bool    IsValid( void ) const;

    protected:
        /*!
         *  @brief      ��莞�ԃX���b�h���~����
         *
         *  @param[in]  milliseconds    ��~����(�~���b)
         */
        virtual void    Sleep( unsigned int milliseconds );

        /*!
         *  @brief      �X���b�h�R�[���o�b�N�֐�
         */
        static unsigned int __stdcall ThreadCallback( void* p );

        //! �X���b�h�n���h��
        HANDLE          m_ThreadHandle;
        //! �C�x���g�n���h��
        HANDLE          m_EventHandle;
        //! �X���b�h��~�t���O
        volatile bool   m_StopFlag;
    };
}
