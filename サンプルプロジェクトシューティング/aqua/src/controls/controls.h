
/*!
 *  @file       controls.h
 *  @brief      ���͔���
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "keyboard\keyboard.h"
#include "mouse\mouse.h"
#include "controller\controller.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @brief      aqua::keyboard���O���
     */
    namespace keyboard
    {
        /*!
         *  @brief      ���͔���
         *              �A���������͔���
         *
         *  @param[in]  key     �L�[ID
         *
         *  @return     ���͏��
         *  @retval     true    ���͂���Ă���
         *  @retval     false   ���͂���Ă��Ȃ�
         */
        bool            Button( aqua::keyboard::KEY_ID key );

        /*!
         *  @brief      ���͔���
         *              �������u�Ԃ𔻒�
         *
         *  @param[in]  key     �L�[ID
         *
         *  @return     ���͏��
         *  @retval     true    �����ꂽ
         *  @retval     false   ������Ă��Ȃ����A���������Ă���
         */
        bool            Trigger( aqua::keyboard::KEY_ID key );

        /*!
         *  @brief      ���͔���
         *              �����ꂽ�u�Ԃ𔻒�
         *
         *  @param[in]  key     �L�[ID
         *
         *  @return     ���͏��
         *  @retval     true    �����ꂽ
         *  @retval     false   ������Ă��Ȃ�
         */
        bool            Released( aqua::keyboard::KEY_ID key );
    }

    /*!
     *  @brief      aqua::mouse���O���
     */
    namespace mouse
    {
        /*!
         *  @brief      �}�E�X���W�擾
         *
         *  @return     �}�E�X���W
         */
        aqua::CPoint    GetCursorPos(void);

        /*!
         *  @brief      �}�E�X�̈ړ��ʎ擾
         *
         *  @return     �}�E�X�̈ړ���
         */
        aqua::CPoint    GetCursorMovement(void);

        /*!
         *  @brief      �}�E�X�{�^������
         *              �A���������͔���
         *
         *  @param[in]  button  �}�E�X�{�^��ID
         *
         *  @return     ���͏��
         *  @retval     true    ���͂���Ă���
         *  @retval     false   ���͂���Ă��Ȃ�
         */
        bool            Button(aqua::mouse::BUTTON_ID button);

        /*!
         *  @brief      �}�E�X�{�^������
         *              �����ꂽ�u�Ԃ𔻒�
         *
         *  @param[in]  button  �}�E�X�{�^��ID
         *
         *  @return     ���͏��
         *  @retval     true    �����ꂽ
         *  @retval     false   ������Ă��Ȃ����A���������Ă���
         */
        bool            Trigger(aqua::mouse::BUTTON_ID button);

        /*!
         *  @brief      �}�E�X�{�^������
         *              �����ꂽ�u�Ԃ𔻒�
         *
         *  @param[in]  button  �}�E�X�{�^��ID
         *
         *  @return     ���͏��
         *  @retval     true    �����ꂽ
         *  @retval     false   ������Ă��Ȃ�
         */
        bool            Released(aqua::mouse::BUTTON_ID button);

        /*!
         *  @brief      �z�C�[���l�擾
         *
         *  @return     �z�[���l�擾
         *  @retval     ���̐�     ���Ƀz�C�[�����ꂽ
         *  @retval     ���̐�     ��O�Ƀz�C�[�����ꂽ
         */
        int             GetWheel(void);
    }

    /*!
     *  @brief      aqua::controller���O���
     */
    namespace controller
    {
        /*!
         *  @brief      ���͔���
         *              �A���������͔���
         *
         *  @param[in]  device  �f�o�C�XID
         *  @param[in]  button  �{�^��ID
         *
         *  @return     ���͏��
         *  @retval     true    ���͂���Ă���
         *  @retval     false   ���͂���Ă��Ȃ�
         */
        bool            Button( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button );

        /*!
         *  @brief      ���͔���
         *              �������u�Ԃ𔻒�
         *
         *  @param[in]  device  �f�o�C�XID
         *  @param[in]  button  �{�^��ID
         *
         *  @return     ���͏��
         *  @retval     true    �����ꂽ
         *  @retval     false   ������Ă��Ȃ����A���������Ă���
         */
        bool            Trigger( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button );

        /*!
         *  @brief      ���͔���
         *              �����ꂽ�u�Ԃ𔻒�
         *
         *  @param[in]  device  �f�o�C�XID
         *  @param[in]  button  �{�^��ID
         *
         *  @return     ���͏��
         *  @retval     true    �����ꂽ
         *  @retval     false   ������Ă��Ȃ�
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
         *  @param[in]  device  �f�o�C�XID
         *
         *  @return     ���A�i���O�X�e�B�b�N�̏��
         */
        aqua::CVector2  GetAnalogStickLeft( aqua::controller::DEVICE_ID device );

        /*!
         *  @brief      �E�A�i���O�X�e�B�b�N�擾
         *
         *  @param[in]  device  �f�o�C�XID
         *
         *  @return     �E�A�i���O�X�e�B�b�N�̏��
         */
        aqua::CVector2  GetAnalogStickRight( aqua::controller::DEVICE_ID device );

        /*!
         *  @brief      ���g���K�[�擾
         *
         *  @param[in]  device      �f�o�C�XID
         *
         *  @return     ���g���K�[�̏��
         */
        float           GetTriggerLeft( aqua::controller::DEVICE_ID device );

        /*!
         *  @brief      �E�g���K�[�擾
         *
         *  @param[in]  device      �f�o�C�XID
         *
         *  @return     �E�g���K�[�̏��
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
         *  @brief      �ڑ��䐔�擾
         *
         *  @return     �ڑ��䐔
         */
        int             GetConnectCount( void );
    }
}
