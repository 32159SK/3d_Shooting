
/*!
 *  @file       effect3D.cpp
 *  @brief      Effekseer用3Dエフェクト
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "effect3D.h"
#include "..\..\debug\debug.h"

 /*
  *  コンストラクタ
  */
aqua::CEffect3D::
CEffect3D(void)
    : position(aqua::CVector3::ZERO)
    , scale(aqua::CVector3::ONE)
    , rotation(aqua::CVector3::ZERO)
    , color(aqua::CColor::WHITE)
    , m_PlayingEffectHandle(AQUA_UNUSED_HANDLE)
    , m_PlaySpeed(1.0f)
{
}

/*
 *  生成
 */
void
aqua::CEffect3D::
Create(const std::string& file_name)
{
    Delete();

    m_Effekseer.Load(file_name);
}

/*
 *  解放
 */
void
aqua::CEffect3D::
Delete(void)
{
    // 再生速度を等倍に戻す
    m_PlaySpeed = 1.0f;

    if (m_PlayingEffectHandle != AQUA_UNUSED_HANDLE)
        StopEffekseer3DEffect(m_PlayingEffectHandle);

    m_PlayingEffectHandle = AQUA_UNUSED_HANDLE;

    m_Effekseer.Unload();
}

/*
 *  更新
 */
void
aqua::CEffect3D::
Update(void)
{
    // エフェクトが再生されていない
    if (IsEffekseer3DEffectPlaying(m_PlayingEffectHandle) == AQUA_DX_ERROR)
        return;

    // 表示位置を設定
    SetPosPlayingEffekseer3DEffect(m_PlayingEffectHandle, position.x, position.y, position.z);

    // 拡大率を設定
    SetScalePlayingEffekseer3DEffect(m_PlayingEffectHandle, scale.x, scale.y, scale.z);

    // 回転値を設定
    SetRotationPlayingEffekseer3DEffect(m_PlayingEffectHandle, rotation.x, rotation.y, rotation.z);

    // 色設定
    SetColorPlayingEffekseer3DEffect(m_PlayingEffectHandle, color.red, color.green, color.blue, color.alpha);

#ifdef AQUA_DEBUG
    if (IsEffekseer3DEffectPlaying(m_PlayingEffectHandle) == AQUA_DX_ERROR)
        return;

    // DTSの速度調整に対応
    SetSpeedPlayingEffekseer3DEffect(m_PlayingEffectHandle, m_PlaySpeed * core::CVisualDebugger::GetInstance().GetDebugDeltaTimeScale());
#endif
}

/*
 *  描画
 */
void
aqua::CEffect3D::
Draw(void)
{
    // 非表示設定
    if (!visible) return;

    // エフェクトが再生されていない
    if (IsEffekseer3DEffectPlaying(m_PlayingEffectHandle) == AQUA_DX_ERROR)
        return;

    DrawEffekseer3D_Begin();

    DrawEffekseer3D_Draw(m_PlayingEffectHandle);

    DrawEffekseer3D_End();
}

/*
 *  再生
 */
void
aqua::CEffect3D::
Play(void)
{
    if (m_PlayingEffectHandle != AQUA_UNUSED_HANDLE)
        Stop();

    // エフェクト再生
    m_PlayingEffectHandle = PlayEffekseer3DEffect(m_Effekseer.GetResourceHandle());
}

/*
 *  停止
 */
void
aqua::CEffect3D::
Stop(void)
{
    if (m_PlayingEffectHandle != AQUA_UNUSED_HANDLE)
        return;

    // エフェクトの停止
    StopEffekseer3DEffect(m_PlayingEffectHandle);

    m_PlayingEffectHandle = AQUA_UNUSED_HANDLE;
}

/*
 *  エフェクト終了検知
 */
bool
aqua::CEffect3D::
Finished(void)
{
    return IsEffekseer3DEffectPlaying(m_PlayingEffectHandle);
}

/*
 *  再生中のエフェクトの再生速度取得
 */
float
aqua::CEffect3D::
GetPlayingSpeed(void)
{
    return m_PlaySpeed;
}

/*
 *  再生中のエフェクトの再生速度設定
 */
void
aqua::CEffect3D::
SetPlayingSpeed(float speed)
{
    // エフェクトが再生されていない
    if (IsEffekseer3DEffectPlaying(m_PlayingEffectHandle) == AQUA_DX_ERROR)
        return;

    m_PlaySpeed = speed;

    // 再生速度を設定
    SetSpeedPlayingEffekseer3DEffect(m_PlayingEffectHandle, m_PlaySpeed);
}

/*
 *  リソースハンドル取得
 */
int
aqua::CEffect3D::
GetResourceHandle(void) const
{
    return m_Effekseer.GetResourceHandle();
}
