
/*!
 *  @file       timer.cpp
 *  @brief      タイマークラス
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
 *  コンストラクタ
 */
aqua::CTimer::
CTimer( void )
    : m_CurrentTime( 0.0f )
    , m_LimitTime( 0.0f )
    , m_TimeScale( m_default_time_scale )
{
}

/*
 *  初期化
 */
void
aqua::CTimer::
Setup( float limit )
{
    Setup( limit, m_default_time_scale );
}

/*
 *  初期化
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
 *  更新
 */
void
aqua::CTimer::
Update( void )
{
    m_CurrentTime += aqua::core::CFramework::GetInstance( ).GetDeltaTime( ) * m_TimeScale;
}

/*
 *  リセット
 */
void
aqua::CTimer::
Reset( void )
{
    m_CurrentTime = 0.0f;
}

/*
 *  終了判定
 */
bool
aqua::CTimer::
Finished( void ) const
{
    return ( m_CurrentTime >= m_LimitTime );
}

/*
 *  現在の経過時間を取得
 */
float
aqua::CTimer::
GetTime( void ) const
{
    return m_CurrentTime;
}

/*
 *  指定した限界時間を取得
 */
float
aqua::CTimer::
GetLimit( void ) const
{
    return m_LimitTime;
}

/*
 *  時間を設定
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
 *  計測時間を設定
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
 *  タイムスケールを取得
 */
float
aqua::CTimer::
GetTimeScale( void ) const
{
    return m_TimeScale;
}

/*
 *  タイムスケールを設定
 */
void
aqua::CTimer::
SetTimeScale( float scale )
{
    m_TimeScale = scale;
}
