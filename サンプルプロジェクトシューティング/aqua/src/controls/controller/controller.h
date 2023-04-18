
/*!
 *  @file       controller.h
 *  @brief      XINPUT���͊Ǘ�
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
     *  @brief      aqua::controller���O���
     */
    namespace controller
    {
        /*!
         *  @brief      �f�o�C�XID
         */
        enum class DEVICE_ID
        {
            //! 1P�W���C�p�b�h
            P1,
            //! 2P�W���C�p�b�h
            P2,
            //! 3P�W���C�p�b�h
            P3,
            //! 4P�W���C�p�b�h
            P4,

            //! �ő�f�o�C�X��
            MAX
        };

        /*!
         *  @brief      �{�^��ID
         */
        enum class BUTTON_ID
        {
            //! �{�^����
            UP              = XINPUT_BUTTON_DPAD_UP,
            //! �{�^����
            DOWN            = XINPUT_BUTTON_DPAD_DOWN,
            //! �{�^����
            LEFT            = XINPUT_BUTTON_DPAD_LEFT,
            //! �{�^���E
            RIGHT           = XINPUT_BUTTON_DPAD_RIGHT,
            //! START�{�^��
            START           = XINPUT_BUTTON_START,
            //! BACK�{�^��
            BACK            = XINPUT_BUTTON_BACK,
            //! ���X�e�B�b�N��������
            LEFT_THUMB      = XINPUT_BUTTON_LEFT_THUMB,
            //! �E�X�e�B�b�N��������
            RIGHT_THUMB     = XINPUT_BUTTON_RIGHT_THUMB,
            //! LB�{�^��
            LEFT_SHOULDER   = XINPUT_BUTTON_LEFT_SHOULDER,
            //! RB�{�^��
            RIGHT_SHOULDER  = XINPUT_BUTTON_RIGHT_SHOULDER,
            //! A�{�^��
            A               = XINPUT_BUTTON_A,
            //! B�{�^��
            B               = XINPUT_BUTTON_B,
            //! X�{�^��
            X               = XINPUT_BUTTON_X,
            //! Y�{�^��
            Y               = XINPUT_BUTTON_Y
        };

        /*!
         *  @brief      �A�i���O�X�e�B�b�N����ID
         */
        enum class STICK_DIRECTION
        {
            //! ������
            LEFT,
            //! �E����
            RIGHT,
            //! �����
            UP,
            //! ������
            DOWN
        };
    }

    /*!
     *  @brief      aqua::core���O���
     */
    namespace core
    {
        /*!
         *  @class      CController
         *
         *  @brief      �R���g���[���[(XINPUT)���͊Ǘ��N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CController
        {
        public:
            /*!
             *  @brief      �C���X�^���X�̎擾
             *
             *  @return     �C���X�^���X�ւ̎Q��
             */
            static CController&    GetInstance( void );

            /*!
             *  @brief      ������
             */
            void            Initialize( void );

            /*!
             *  @brief      ���͏��X�V
             */
            void            Update( void );

            /*!
             *  @brief      ���
             */
            void            Finalize( void );

            /*!
             *  @brief      �{�^������
             *
             *  @param[in]  device      �f�o�C�XID
             *  @param[in]  button      �{�^��ID
             *
             *  @return     ���͏��
             *  @retval     true    ������Ă���
             *  @retval     false   ������Ă��Ȃ�
             */
            bool            Button( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button );

            /*!
             *  @brief      �g���K�[����
             *
             *  @param[in]  device      �f�o�C�XID
             *  @param[in]  button      �{�^��ID
             *
             *  @return     ���͏��
             *  @retval     true    �����ꂽ�u��
             *  @retval     false   ������Ă��Ȃ����A�����ꑱ���Ă���
             */
            bool            Trigger( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button );

            /*!
             *  @brief      �����[�X����
             *
             *  @param[in]  device      �f�o�C�XID
             *  @param[in]  button      �{�^��ID
             *
             *  @return     ���͏��
             *  @retval     true    �����ꂽ�u��
             *  @retval     false   ������Ă��Ȃ����A�����ꑱ���Ă���
             */
            bool            Released( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button );

            /*!
             *  @brief      �g���K�[����
             *              ���A�i���O�X�e�B�b�N
             *
             *  @param[in]  device      �f�o�C�XID
             *  @param[in]  direction   ����ID
             *
             *  @return     ���͏��
             *  @retval     true    �����ꂽ�u��
             *  @retval     false   ������Ă��Ȃ����A�����ꑱ���Ă���
             */
            bool            TriggerAnalogStickLeft( aqua::controller::DEVICE_ID device, aqua::controller::STICK_DIRECTION direction );

            /*!
             *  @brief      �g���K�[����
             *              �E�A�i���O�X�e�B�b�N
             *
             *  @param[in]  device      �f�o�C�XID
             *  @param[in]  direction   ����ID
             *
             *  @return     ���͏��
             *  @retval     true    �����ꂽ�u��
             *  @retval     false   ������Ă��Ȃ����A�����ꑱ���Ă���
             */
            bool            TriggerAnalogStickRight( aqua::controller::DEVICE_ID device, aqua::controller::STICK_DIRECTION direction );

            /*!
             *  @brief      ���A�i���O�X�e�B�b�N�擾
             *
             *  @param[in]  device      �f�o�C�XID
             *
             *  @return     ���A�i���O�X�e�B�b�N�̏��(-1.0f�`1.0f)
             */
            aqua::CVector2  GetAnalogStickLeft( aqua::controller::DEVICE_ID device );

            /*!
             *  @brief      �E�A�i���O�X�e�B�b�N�擾
             *
             *  @param[in]  device      �f�o�C�XID
             *
             *  @return     �E�A�i���O�X�e�B�b�N�̏��(-1.0f�`1.0f)
             */
            aqua::CVector2  GetAnalogStickRight( aqua::controller::DEVICE_ID device );

            /*!
             *  @brief      ���g���K�[�擾
             *
             *  @param[in]  device      �f�o�C�XID
             *
             *  @return     ���g���K�[�̏��(0.0f�`1.0f)
             */
            float           GetTriggerLeft( aqua::controller::DEVICE_ID device );

            /*!
             *  @brief      �E�g���K�[�擾
             *
             *  @param[in]  device      �f�o�C�XID
             *
             *  @return     �E�g���K�[�̏��(0.0f�`1.0f)
             */
            float           GetTriggerRight( aqua::controller::DEVICE_ID device );

            /*!
             *  @brief      �o�C�u���[�V�����̊J�n
             *
             *  @param[in]  device      �f�o�C�XID
             *  @param[in]  power       �U���̋���(0�`1000)
             *  @param[in]  time        �U�����鎞��(�b�P��)
             */
            void            StartVibration( aqua::controller::DEVICE_ID device, int power, float time );

            /*!
             *  @brief      �ڑ����擾
             *
             *  @return     �ڑ���
             */
            int             GetConnectCount( void );

        private:
            /*!
             *  @brief      �R���X�g���N�^
             */
            CController( void );

            /*!
             *  @brief      �R�s�[�R���X�g���N�^
             *
             *  @param[in]  rhs �R�s�[�I�u�W�F�N�g
             */
            CController( const CController& rhs );

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CController( void ) = default;

            /*!
             *  @brief      ������Z�q
             *
             *  @param[in]  rhs ����I�u�W�F�N�g
             *
             *  @return     ���g�̃I�u�W�F�N�g
             */
            CController& operator=( const CController& rhs );

            //! �W���C�p�b�h�̍ő�ڑ���
            static const int    m_max_xcontroller_device;
            //! �A�i���O�X�e�B�b�N���͂̌��E�l
            static const int    m_limit_cant_analog;
            //! �g���K�[���͂̍ő�l
            static const int    m_max_trigger;
            //! �A�i���O�X�e�B�b�N�̖����͈�
            static const int    m_analog_dead_zone;
            //! XINPUT�̓��͏��
            XINPUT_STATE*       m_XInputState;
            //! 1�t���[���O�̓��͏��
            XINPUT_STATE*       m_PrevXInputState;
        };
    }
}
