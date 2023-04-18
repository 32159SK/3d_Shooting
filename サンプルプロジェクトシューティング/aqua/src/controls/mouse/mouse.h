
/*!
 *  @file       mouse.h
 *  @brief      �}�E�X���͊Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DXLib.h>
#include "..\..\utility\utility.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @brief      aqua::mouse���O���
     */
    namespace mouse
    {
        /*!
         *  @brief      �}�E�X�{�^��ID<br>
         *              �N���b�N����Ŏg�p�\�ȃ{�^��ID
         */
        enum class BUTTON_ID
        {
            //! ���{�^��
            LEFT    = MOUSE_INPUT_LEFT,
            //! �E�{�^��
            RIGHT   = MOUSE_INPUT_RIGHT,
            //! ���{�^��
            MIDDLE  = MOUSE_INPUT_MIDDLE
        };
    }

    /*!
     *  @brief      aqua::core���O���
     */
    namespace core
    {
        /*!
         *  @class      CMouse
         *
         *  @brief      �}�E�X���͊Ǘ��N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CMouse
        {
        public:
            /*!
             *  @brief      �C���X�^���X�̎擾
             *
             *  @return     �C���X�^���X�ւ̎Q��
             */
            static CMouse&   GetInstance(void);

            /*!
             *  @brief      ������
             */
            void    Initialize(void);

            /*!
             *  @brief      ���͏��X�V
             */
            void    Update(void);

            /*!
             *  @brief      �{�^������
             *
             *  @param[in]  button  �}�E�X�{�^��ID
             *
             *  @return     ���͏��
             *  @retval     true    ������Ă���
             *  @retval     false   ������Ă��Ȃ�
             */
            bool            Button(aqua::mouse::BUTTON_ID button);

            /*!
             *  @brief      �g���K�[����
             *
             *  @param[in]  button  �}�E�X�{�^��ID
             *
             *  @return     ���͏��
             *  @retval     true    �����ꂽ�u��
             *  @retval     false   ������Ă��Ȃ����A�����ꑱ���Ă���
             */
            bool            Trigger(aqua::mouse::BUTTON_ID button);

            /*!
             *  @brief      �����[�X����
             *
             *  @param[in]  button  �}�E�X�{�^��ID
             *
             *  @return     ���͏��
             *  @retval     true    �����ꂽ�u��
             *  @retval     false   ������Ă��Ȃ����A�����ꑱ���Ă���
             */
            bool            Released(aqua::mouse::BUTTON_ID button);

            /*!
             *  @brief      �}�E�X�J�[�\���̈ʒu�擾
             *
             *  @return     �}�E�X�J�[�\���̈ʒu
             */
            aqua::CPoint    GetCursorPos(void);

            /*!
             *  @brief      �}�E�X�J�[�\���̈ړ��ʎ擾
             *
             *  @return     �}�E�X�J�[�\���̈ړ���
             */
            aqua::CPoint    GetCursorMovement(void);

            /*!
             *  @brief      �}�E�X�z�C�[���l�擾
             *
             *  @return     �z�C�[���l
             *  @retval     ���̐�     ���Ƀz�C�[�����ꂽ
             *  @retval     ���̐�     ��O�Ƀz�C�[�����ꂽ
             *  @retval     0          �z�C�[������Ă��Ȃ�
             */
            int             GetWheel(void);

        private:
            /*!
             *  @brief      �R���X�g���N�^
             */
            CMouse(void);

            /*!
             *  @brief      �R�s�[�R���X�g���N�^
             *
             *  @param[in]  rhs �R�s�[�I�u�W�F�N�g
             */
            CMouse(const CMouse& rhs);

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CMouse(void) = default;

            /*!
             *  @brief      ������Z�q
             *
             *  @param[in]  rhs ����I�u�W�F�N�g
             *
             *  @return     ���g�̃I�u�W�F�N�g
             */
            CMouse& operator=(const CMouse& rhs);

            //! �}�E�X�̓��͏��
            int         m_MouseState;
            //! �O�̃}�E�X�̓��͏��
            int         m_PrevMouseState;
            //! �J�[�\���ʒu
            CPoint      m_CursorPos;
            //! �O�̃J�[�\���ʒu
            CPoint      m_PrevCursorPos;
        };
    }
}
