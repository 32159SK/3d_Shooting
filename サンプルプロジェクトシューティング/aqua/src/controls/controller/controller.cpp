
/*!
 *  @file       controller.cpp
 *  @brief      �W���C�p�b�h���͊Ǘ�
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
 *  ������
 */
aqua::core::CController&
aqua::core::CController::
GetInstance( void )
{
    static CController instance;

    return instance;
}

/*
 *  ������
 */
void
aqua::core::CController::
Initialize( void )
{
    // XINPUT�X�e�[�g����
    if( !m_XInputState )
        m_XInputState = AQUA_NEW XINPUT_STATE[m_max_xcontroller_device];

    ZeroMemory( m_XInputState, sizeof( XINPUT_STATE ) * m_max_xcontroller_device );

    // �O��XINPUT�X�e�[�g����
    if( !m_PrevXInputState )
        m_PrevXInputState = AQUA_NEW XINPUT_STATE[m_max_xcontroller_device];

    ZeroMemory( m_PrevXInputState, sizeof( XINPUT_STATE ) * m_max_xcontroller_device );

    //// �A�i���O�X�e�B�b�N�̖����͈͂�ݒ�
    //for( int i = DX_INPUT_PAD1; i <= m_max_xcontroller_device; ++i )
    //    SetJoypadDeadZone( i, m_analog_dead_zone );

    // �o�C�u���[�V�������g�p����
    SetUseJoypadVibrationFlag( TRUE );
}

/*
 *  �X�V
 */
void
aqua::core::CController::
Update( void )
{
    // �ڑ�����Ă���䐔���J��Ԃ�
    for( int i = 0; i < GetConnectCount( ); ++i )
    {
        // 1�t���[���O�̏�Ԃ�ۑ�
        m_PrevXInputState[i] = m_XInputState[i];

        // ���͏�Ԃ��擾
        GetJoypadXInputState( i + DX_INPUT_PAD1, &m_XInputState[i] );
    }
}

/*
 *  ���
 */
void
aqua::core::CController::
Finalize( void )
{
    AQUA_SAFE_DELETE_ARRAY( m_PrevXInputState );
    AQUA_SAFE_DELETE_ARRAY( m_XInputState );
}

/*
 *  �{�^������
 */
bool
aqua::core::CController::
Button( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button )
{
    return ( m_XInputState[static_cast<int>(device)].Buttons[static_cast<int>(button)] );
}

/*
 *  �g���K�[����
 */
bool
aqua::core::CController::
Trigger( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button )
{
    return ( m_XInputState[static_cast<int>(device)].Buttons[static_cast<int>(button)] ) && !( m_PrevXInputState[static_cast<int>(device)].Buttons[static_cast<int>(button)] );
}

/*
 *  �����[�X����
 */
bool
aqua::core::CController::
Released( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button )
{
    return !( m_XInputState[static_cast<int>(device)].Buttons[static_cast<int>(button)] ) && ( m_PrevXInputState[static_cast<int>(device)].Buttons[static_cast<int>(button)] );
}

/*
 *  �A�i���O�X�e�B�b�N�̃g���K�[����
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
 *  �A�i���O�X�e�B�b�N�̃g���K�[����
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
 *  ���A�i���O�X�e�B�b�N�擾
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

    // Y�������𔽓]
    return aqua::CVector2( ax, -ay ) / (float)m_limit_cant_analog;
}

/*
 *  �E�A�i���O�X�e�B�b�N�擾
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

    // Y�������𔽓]
    return aqua::CVector2( ax, -ay ) / (float)m_limit_cant_analog;
}

/*
 *  ���g���K�[�擾
 */
float
aqua::core::CController::
GetTriggerLeft( aqua::controller::DEVICE_ID device )
{
    return (float)m_XInputState[static_cast<int>(device)].LeftTrigger / (float)m_max_trigger;
}

/*
 *  �E�g���K�[�擾
 */
float
aqua::core::CController::
GetTriggerRight( aqua::controller::DEVICE_ID device )
{
    return (float)m_XInputState[static_cast<int>(device)].RightTrigger / (float)m_max_trigger;
}

/*
 *  �o�C�u���[�V�����̊J�n
 */
void
aqua::core::CController::
StartVibration( aqua::controller::DEVICE_ID device, int power, float time )
{
    StartJoypadVibration(static_cast<int>(device) + DX_INPUT_PAD1, power, (int)( time * 1000.0f ) );
}

/*
 *  �ڑ����擾
 */
int
aqua::core::CController::
GetConnectCount( void )
{
    return GetJoypadNum( );
}

/*
 *  �R���X�g���N�^
 */
aqua::core::CController::
CController( void )
    : m_XInputState( nullptr )
    , m_PrevXInputState( nullptr )
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
aqua::core::CController::
CController( const aqua::core::CController& rhs )
    : m_XInputState(nullptr)
    , m_PrevXInputState(nullptr)
{
    (void)rhs;
}

/*
 *  ������Z�q
 */
aqua::core::CController&
aqua::core::CController::
operator=( const CController& rhs )
{
    (void)rhs;

    return *this;
}
