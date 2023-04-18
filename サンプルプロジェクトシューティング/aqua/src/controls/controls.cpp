
/*!
 *  @file       controls.inl
 *  @brief      入力判定
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "controls.h"

/*
 *  キーボード入力判定
 *  連続した入力判定
 */
bool
aqua::keyboard::
Button( aqua::keyboard::KEY_ID key )
{
    return aqua::core::CKeyboard::GetInstance( ).Button( key );
}

/*
 *  キーボード入力判定
 *  押された瞬間を判定
 */
bool
aqua::keyboard::
Trigger( aqua::keyboard::KEY_ID key )
{
    return aqua::core::CKeyboard::GetInstance( ).Trigger( key );
}

/*
 *  キーボード入力判定
 *  離された瞬間を判定
 */
bool
aqua::keyboard::
Released( aqua::keyboard::KEY_ID key )
{
    return aqua::core::CKeyboard::GetInstance( ).Released( key );
}

/*
 *  マウス座標の取得
 */
aqua::CPoint
aqua::mouse::
GetCursorPos( void )
{
    return aqua::core::CMouse::GetInstance( ).GetCursorPos( );
}

/*
 *  マウスの移動量の取得
 */
aqua::CPoint
aqua::mouse::
GetCursorMovement( void )
{
    return aqua::core::CMouse::GetInstance( ).GetCursorMovement( );
}

/*
 *  マウス入力判定
 *  連続した入力判定
 */
bool
aqua::mouse::
Button( aqua::mouse::BUTTON_ID button )
{
    return aqua::core::CMouse::GetInstance( ).Button( button );
}

/*
 *  マウス入力判定
 *  押された瞬間を判定
 */
bool
aqua::mouse::
Trigger( aqua::mouse::BUTTON_ID button )
{
    return aqua::core::CMouse::GetInstance( ).Trigger( button );
}

/*
 *  マウス入力判定
 *  離された瞬間を判定
 */
bool
aqua::mouse::
Released( aqua::mouse::BUTTON_ID button )
{
    return aqua::core::CMouse::GetInstance( ).Released( button );
}

/*
 *  マウスホイール値取得
 */
int
aqua::mouse::
GetWheel( void )
{
    return aqua::core::CMouse::GetInstance( ).GetWheel( );
}

/*
 *  XINPUT入力判定
 *  連続した入力判定
 */
bool
aqua::controller::
Button( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button )
{
    return aqua::core::CController::GetInstance( ).Button( device, button );
}

/*
 *  XINPUT入力判定
 *  押された瞬間を判定
 */
bool
aqua::controller::
Trigger( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button )
{
    return aqua::core::CController::GetInstance( ).Trigger( device, button );
}

/*
 *  XINPUT入力判定
 *  離された瞬間を判定
 */
bool
aqua::controller::
Released( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button )
{
    return aqua::core::CController::GetInstance( ).Released( device, button );
}

/*
 *  トリガー判定
 */
bool
aqua::controller::
TriggerAnalogStickLeft( aqua::controller::DEVICE_ID device, aqua::controller::STICK_DIRECTION direction )
{
    return aqua::core::CController::GetInstance( ).TriggerAnalogStickLeft( device, direction );
}

/*
 *  トリガー判定
 */
bool
aqua::controller::
TriggerAnalogStickRight( aqua::controller::DEVICE_ID device, aqua::controller::STICK_DIRECTION direction )
{
    return aqua::core::CController::GetInstance( ).TriggerAnalogStickRight( device, direction );
}

/*
 *  左アナログスティックの取得
 */
aqua::CVector2
aqua::controller::
GetAnalogStickLeft( aqua::controller::DEVICE_ID device )
{
    return aqua::core::CController::GetInstance( ).GetAnalogStickLeft( device );
}

/*
 *  右アナログスティックの取得
 */
aqua::CVector2
aqua::controller::
GetAnalogStickRight( aqua::controller::DEVICE_ID device )
{
    return aqua::core::CController::GetInstance( ).GetAnalogStickRight( device );
}

/*
 *  左トリガーの取得
 */
float
aqua::controller::
GetTriggerLeft( aqua::controller::DEVICE_ID device )
{
    return aqua::core::CController::GetInstance( ).GetTriggerLeft( device );
}

/*
 *  右トリガーの取得
 */
float
aqua::controller::
GetTriggerRight( aqua::controller::DEVICE_ID device )
{
    return aqua::core::CController::GetInstance( ).GetTriggerRight( device );
}

/*
 *  バイブレーションの開始
 */
void
aqua::controller::
StartVibration( aqua::controller::DEVICE_ID device, int power, float time )
{
    aqua::core::CController::GetInstance( ).StartVibration( device, power, time );
}

/*
 *  XINPUT接続台数取得
 */
int
aqua::controller::
GetConnectCount( void )
{
    return aqua::core::CController::GetInstance( ).GetConnectCount( );
}
