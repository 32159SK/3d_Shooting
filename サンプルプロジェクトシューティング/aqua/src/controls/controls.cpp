
/*!
 *  @file       controls.inl
 *  @brief      ���͔���
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "controls.h"

/*
 *  �L�[�{�[�h���͔���
 *  �A���������͔���
 */
bool
aqua::keyboard::
Button( aqua::keyboard::KEY_ID key )
{
    return aqua::core::CKeyboard::GetInstance( ).Button( key );
}

/*
 *  �L�[�{�[�h���͔���
 *  �����ꂽ�u�Ԃ𔻒�
 */
bool
aqua::keyboard::
Trigger( aqua::keyboard::KEY_ID key )
{
    return aqua::core::CKeyboard::GetInstance( ).Trigger( key );
}

/*
 *  �L�[�{�[�h���͔���
 *  �����ꂽ�u�Ԃ𔻒�
 */
bool
aqua::keyboard::
Released( aqua::keyboard::KEY_ID key )
{
    return aqua::core::CKeyboard::GetInstance( ).Released( key );
}

/*
 *  �}�E�X���W�̎擾
 */
aqua::CPoint
aqua::mouse::
GetCursorPos( void )
{
    return aqua::core::CMouse::GetInstance( ).GetCursorPos( );
}

/*
 *  �}�E�X�̈ړ��ʂ̎擾
 */
aqua::CPoint
aqua::mouse::
GetCursorMovement( void )
{
    return aqua::core::CMouse::GetInstance( ).GetCursorMovement( );
}

/*
 *  �}�E�X���͔���
 *  �A���������͔���
 */
bool
aqua::mouse::
Button( aqua::mouse::BUTTON_ID button )
{
    return aqua::core::CMouse::GetInstance( ).Button( button );
}

/*
 *  �}�E�X���͔���
 *  �����ꂽ�u�Ԃ𔻒�
 */
bool
aqua::mouse::
Trigger( aqua::mouse::BUTTON_ID button )
{
    return aqua::core::CMouse::GetInstance( ).Trigger( button );
}

/*
 *  �}�E�X���͔���
 *  �����ꂽ�u�Ԃ𔻒�
 */
bool
aqua::mouse::
Released( aqua::mouse::BUTTON_ID button )
{
    return aqua::core::CMouse::GetInstance( ).Released( button );
}

/*
 *  �}�E�X�z�C�[���l�擾
 */
int
aqua::mouse::
GetWheel( void )
{
    return aqua::core::CMouse::GetInstance( ).GetWheel( );
}

/*
 *  XINPUT���͔���
 *  �A���������͔���
 */
bool
aqua::controller::
Button( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button )
{
    return aqua::core::CController::GetInstance( ).Button( device, button );
}

/*
 *  XINPUT���͔���
 *  �����ꂽ�u�Ԃ𔻒�
 */
bool
aqua::controller::
Trigger( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button )
{
    return aqua::core::CController::GetInstance( ).Trigger( device, button );
}

/*
 *  XINPUT���͔���
 *  �����ꂽ�u�Ԃ𔻒�
 */
bool
aqua::controller::
Released( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button )
{
    return aqua::core::CController::GetInstance( ).Released( device, button );
}

/*
 *  �g���K�[����
 */
bool
aqua::controller::
TriggerAnalogStickLeft( aqua::controller::DEVICE_ID device, aqua::controller::STICK_DIRECTION direction )
{
    return aqua::core::CController::GetInstance( ).TriggerAnalogStickLeft( device, direction );
}

/*
 *  �g���K�[����
 */
bool
aqua::controller::
TriggerAnalogStickRight( aqua::controller::DEVICE_ID device, aqua::controller::STICK_DIRECTION direction )
{
    return aqua::core::CController::GetInstance( ).TriggerAnalogStickRight( device, direction );
}

/*
 *  ���A�i���O�X�e�B�b�N�̎擾
 */
aqua::CVector2
aqua::controller::
GetAnalogStickLeft( aqua::controller::DEVICE_ID device )
{
    return aqua::core::CController::GetInstance( ).GetAnalogStickLeft( device );
}

/*
 *  �E�A�i���O�X�e�B�b�N�̎擾
 */
aqua::CVector2
aqua::controller::
GetAnalogStickRight( aqua::controller::DEVICE_ID device )
{
    return aqua::core::CController::GetInstance( ).GetAnalogStickRight( device );
}

/*
 *  ���g���K�[�̎擾
 */
float
aqua::controller::
GetTriggerLeft( aqua::controller::DEVICE_ID device )
{
    return aqua::core::CController::GetInstance( ).GetTriggerLeft( device );
}

/*
 *  �E�g���K�[�̎擾
 */
float
aqua::controller::
GetTriggerRight( aqua::controller::DEVICE_ID device )
{
    return aqua::core::CController::GetInstance( ).GetTriggerRight( device );
}

/*
 *  �o�C�u���[�V�����̊J�n
 */
void
aqua::controller::
StartVibration( aqua::controller::DEVICE_ID device, int power, float time )
{
    aqua::core::CController::GetInstance( ).StartVibration( device, power, time );
}

/*
 *  XINPUT�ڑ��䐔�擾
 */
int
aqua::controller::
GetConnectCount( void )
{
    return aqua::core::CController::GetInstance( ).GetConnectCount( );
}
