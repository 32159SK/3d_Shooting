
/*!
 *  @file       timer.cpp
 *  @brief      �^�C�}�[�N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "timer.h"
#include "..\..\framework\framework.h"

const float aqua::CTimer::m_default_time_scale = 1.0f;

/*
 *  �R���X�g���N�^
 */
aqua::CTimer::
CTimer( void )
    : m_CurrentTime( 0.0f )
    , m_LimitTime( 0.0f )
    , m_TimeScale( m_default_time_scale )
{
}

/*
 *  ������
 */
void
aqua::CTimer::
Setup( float limit )
{
    Setup( limit, m_default_time_scale );
}

/*
 *  ������
 */
void
aqua::CTimer::
Setup( float limit, float scale )
{
    m_LimitTime = limit;
    m_TimeScale = scale;

    Reset( );
}

/*
 *  �X�V
 */
void
aqua::CTimer::
Update( void )
{
    m_CurrentTime += aqua::core::CFramework::GetInstance( ).GetDeltaTime( ) * m_TimeScale;
}

/*
 *  ���Z�b�g
 */
void
aqua::CTimer::
Reset( void )
{
    m_CurrentTime = 0.0f;
}

/*
 *  �I������
 */
bool
aqua::CTimer::
Finished( void ) const
{
    return ( m_CurrentTime >= m_LimitTime );
}

/*
 *  ���݂̌o�ߎ��Ԃ��擾
 */
float
aqua::CTimer::
GetTime( void ) const
{
    return m_CurrentTime;
}

/*
 *  �w�肵�����E���Ԃ��擾
 */
float
aqua::CTimer::
GetLimit( void ) const
{
    return m_LimitTime;
}

/*
 *  ���Ԃ�ݒ�
 */
void
aqua::CTimer::
SetTime(float time)
{
    m_CurrentTime = time;

    if (m_CurrentTime < 0.0f)
        m_CurrentTime = 0.0f;
    else if (m_CurrentTime > m_LimitTime)
        m_CurrentTime = m_LimitTime;
}

/*
 *  �v�����Ԃ�ݒ�
 */
void
aqua::CTimer::
SetLimit( float limit )
{
    m_LimitTime = limit;

    if( m_LimitTime < 0.0f )
        m_LimitTime = 0.0f;
}

/*
 *  �^�C���X�P�[�����擾
 */
float
aqua::CTimer::
GetTimeScale( void ) const
{
    return m_TimeScale;
}

/*
 *  �^�C���X�P�[����ݒ�
 */
void
aqua::CTimer::
SetTimeScale( float scale )
{
    m_TimeScale = scale;
}
