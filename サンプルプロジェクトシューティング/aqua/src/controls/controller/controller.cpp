
/*!
 *  @file       controller.cpp
 *  @brief      ジョイパッド入力管理
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "controller.h"
#include "..\..\debug\debug.h"
#include "..\..\utility\memory\memory.h"

const int   aqua::core::CController::m_max_xcontroller_device  = static_cast<int>(aqua::controller::DEVICE_ID::MAX);
const int   aqua::core::CController::m_limit_cant_analog       = 30000;
const int   aqua::core::CController::m_max_trigger             = 255;
const int   aqua::core::CController::m_analog_dead_zone        = 15000;

/*
 *  初期化
 */
aqua::core::CController&
aqua::core::CController::
GetInstance( void )
{
    static CController instance;

    return instance;
}

/*
 *  初期化
 */
void
aqua::core::CController::
Initialize( void )
{
    // XINPUTステート生成
    if( !m_XInputState )
        m_XInputState = AQUA_NEW XINPUT_STATE[m_max_xcontroller_device];

    ZeroMemory( m_XInputState, sizeof( XINPUT_STATE ) * m_max_xcontroller_device );

    // 前のXINPUTステート生成
    if( !m_PrevXInputState )
        m_PrevXInputState = AQUA_NEW XINPUT_STATE[m_max_xcontroller_device];

    ZeroMemory( m_PrevXInputState, sizeof( XINPUT_STATE ) * m_max_xcontroller_device );

    //// アナログスティックの無効範囲を設定
    //for( int i = DX_INPUT_PAD1; i <= m_max_xcontroller_device; ++i )
    //    SetJoypadDeadZone( i, m_analog_dead_zone );

    // バイブレーションを使用する
    SetUseJoypadVibrationFlag( TRUE );
}

/*
 *  更新
 */
void
aqua::core::CController::
Update( void )
{
    // 接続されている台数分繰り返す
    for( int i = 0; i < GetConnectCount( ); ++i )
    {
        // 1フレーム前の状態を保存
        m_PrevXInputState[i] = m_XInputState[i];

        // 入力状態を取得
        GetJoypadXInputState( i + DX_INPUT_PAD1, &m_XInputState[i] );
    }
}

/*
 *  解放
 */
void
aqua::core::CController::
Finalize( void )
{
    AQUA_SAFE_DELETE_ARRAY( m_PrevXInputState );
    AQUA_SAFE_DELETE_ARRAY( m_XInputState );
}

/*
 *  ボタン判定
 */
bool
aqua::core::CController::
Button( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button )
{
    return ( m_XInputState[static_cast<int>(device)].Buttons[static_cast<int>(button)] );
}

/*
 *  トリガー判定
 */
bool
aqua::core::CController::
Trigger( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button )
{
    return ( m_XInputState[static_cast<int>(device)].Buttons[static_cast<int>(button)] ) && !( m_PrevXInputState[static_cast<int>(device)].Buttons[static_cast<int>(button)] );
}

/*
 *  リリース判定
 */
bool
aqua::core::CController::
Released( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button )
{
    return !( m_XInputState[static_cast<int>(device)].Buttons[static_cast<int>(button)] ) && ( m_PrevXInputState[static_cast<int>(device)].Buttons[static_cast<int>(button)] );
}

/*
 *  アナログスティックのトリガー判定
 */
bool
aqua::core::CController::
TriggerAnalogStickLeft( aqua::controller::DEVICE_ID device, aqua::controller::STICK_DIRECTION direction )
{
    switch (direction)
    {
    case controller::STICK_DIRECTION::LEFT:
        return ( m_XInputState[static_cast<int>(device)].ThumbLX < m_limit_cant_analog && m_PrevXInputState[static_cast<int>(device)].ThumbLX > m_limit_cant_analog );
    case controller::STICK_DIRECTION::RIGHT:
        return ( m_XInputState[static_cast<int>(device)].ThumbLX > m_limit_cant_analog && m_PrevXInputState[static_cast<int>(device)].ThumbLX < m_limit_cant_analog );
    case controller::STICK_DIRECTION::UP:
        return ( m_XInputState[static_cast<int>(device)].ThumbLY < m_limit_cant_analog && m_PrevXInputState[static_cast<int>(device)].ThumbLY > m_limit_cant_analog );
    case controller::STICK_DIRECTION::DOWN:
        return ( m_XInputState[static_cast<int>(device)].ThumbLY > m_limit_cant_analog && m_PrevXInputState[static_cast<int>(device)].ThumbLY < m_limit_cant_analog );
    }

    return false;
}

/*
 *  アナログスティックのトリガー判定
 */
bool
aqua::core::CController::
TriggerAnalogStickRight( aqua::controller::DEVICE_ID device, aqua::controller::STICK_DIRECTION direction )
{
    switch (direction)
    {
    case controller::STICK_DIRECTION::LEFT:
        return ( m_XInputState[static_cast<int>(device)].ThumbRX < m_limit_cant_analog && m_PrevXInputState[static_cast<int>(device)].ThumbRX > m_limit_cant_analog );
    case controller::STICK_DIRECTION::RIGHT:
        return ( m_XInputState[static_cast<int>(device)].ThumbRX > m_limit_cant_analog && m_PrevXInputState[static_cast<int>(device)].ThumbRX < m_limit_cant_analog );
    case controller::STICK_DIRECTION::UP:
        return ( m_XInputState[static_cast<int>(device)].ThumbRY < m_limit_cant_analog && m_PrevXInputState[static_cast<int>(device)].ThumbRY > m_limit_cant_analog );
    case controller::STICK_DIRECTION::DOWN:
        return ( m_XInputState[static_cast<int>(device)].ThumbRY > m_limit_cant_analog && m_PrevXInputState[static_cast<int>(device)].ThumbRY < m_limit_cant_analog );
    }

    return false;
}

/*
 *  左アナログスティック取得
 */
aqua::CVector2
aqua::core::CController::
GetAnalogStickLeft( aqua::controller::DEVICE_ID device )
{
    int x = m_XInputState[static_cast<int>(device)].ThumbLX;
    int y = m_XInputState[static_cast<int>(device)].ThumbLY;

    float ax = (abs(x) < m_analog_dead_zone ? 0.0f : x);
    float ay = (abs(y) < m_analog_dead_zone ? 0.0f : y);

    if (x < 0.0f)
        ax = max((float)x, -m_limit_cant_analog);
    else if (x > 0.0f)
        ax = min((float)x, m_limit_cant_analog);

    if (y < 0.0f)
        ay = max((float)y, -m_limit_cant_analog);
    else if (y > 0.0f)
        ay = min((float)y, m_limit_cant_analog);

    // Y軸だけを反転
    return aqua::CVector2( ax, -ay ) / (float)m_limit_cant_analog;
}

/*
 *  右アナログスティック取得
 */
aqua::CVector2
aqua::core::CController::
GetAnalogStickRight( aqua::controller::DEVICE_ID device )
{
    int x = m_XInputState[static_cast<int>(device)].ThumbRX;
    int y = m_XInputState[static_cast<int>(device)].ThumbRY;

    float ax = (abs(x) < m_analog_dead_zone ? 0.0f : x);
    float ay = (abs(y) < m_analog_dead_zone ? 0.0f : y);

    if (x < 0.0f)
        ax = max((float)x, -m_limit_cant_analog);
    else if (x > 0.0f)
        ax = min((float)x, m_limit_cant_analog);

    if (y < 0.0f)
        ay = max((float)y, -m_limit_cant_analog);
    else if (y > 0.0f)
        ay = min((float)y, m_limit_cant_analog);

    // Y軸だけを反転
    return aqua::CVector2( ax, -ay ) / (float)m_limit_cant_analog;
}

/*
 *  左トリガー取得
 */
float
aqua::core::CController::
GetTriggerLeft( aqua::controller::DEVICE_ID device )
{
    return (float)m_XInputState[static_cast<int>(device)].LeftTrigger / (float)m_max_trigger;
}

/*
 *  右トリガー取得
 */
float
aqua::core::CController::
GetTriggerRight( aqua::controller::DEVICE_ID device )
{
    return (float)m_XInputState[static_cast<int>(device)].RightTrigger / (float)m_max_trigger;
}

/*
 *  バイブレーションの開始
 */
void
aqua::core::CController::
StartVibration( aqua::controller::DEVICE_ID device, int power, float time )
{
    StartJoypadVibration(static_cast<int>(device) + DX_INPUT_PAD1, power, (int)( time * 1000.0f ) );
}

/*
 *  接続数取得
 */
int
aqua::core::CController::
GetConnectCount( void )
{
    return GetJoypadNum( );
}

/*
 *  コンストラクタ
 */
aqua::core::CController::
CController( void )
    : m_XInputState( nullptr )
    , m_PrevXInputState( nullptr )
{
}

/*
 *  コピーコンストラクタ
 */
aqua::core::CController::
CController( const aqua::core::CController& rhs )
    : m_XInputState(nullptr)
    , m_PrevXInputState(nullptr)
{
    (void)rhs;
}

/*
 *  代入演算子
 */
aqua::core::CController&
aqua::core::CController::
operator=( const CController& rhs )
{
    (void)rhs;

    return *this;
}
