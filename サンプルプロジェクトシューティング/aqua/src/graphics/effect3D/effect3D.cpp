
/*!
 *  @file       effect3D.cpp
 *  @brief      Effekseer�p3D�G�t�F�N�g
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "effect3D.h"
#include "..\..\debug\debug.h"

 /*
  *  �R���X�g���N�^
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
 *  ����
 */
void
aqua::CEffect3D::
Create(const std::string& file_name)
{
    Delete();

    m_Effekseer.Load(file_name);
}

/*
 *  ���
 */
void
aqua::CEffect3D::
Delete(void)
{
    // �Đ����x�𓙔{�ɖ߂�
    m_PlaySpeed = 1.0f;

    if (m_PlayingEffectHandle != AQUA_UNUSED_HANDLE)
        StopEffekseer3DEffect(m_PlayingEffectHandle);

    m_PlayingEffectHandle = AQUA_UNUSED_HANDLE;

    m_Effekseer.Unload();
}

/*
 *  �X�V
 */
void
aqua::CEffect3D::
Update(void)
{
    // �G�t�F�N�g���Đ�����Ă��Ȃ�
    if (IsEffekseer3DEffectPlaying(m_PlayingEffectHandle) == AQUA_DX_ERROR)
        return;

    // �\���ʒu��ݒ�
    SetPosPlayingEffekseer3DEffect(m_PlayingEffectHandle, position.x, position.y, position.z);

    // �g�嗦��ݒ�
    SetScalePlayingEffekseer3DEffect(m_PlayingEffectHandle, scale.x, scale.y, scale.z);

    // ��]�l��ݒ�
    SetRotationPlayingEffekseer3DEffect(m_PlayingEffectHandle, rotation.x, rotation.y, rotation.z);

    // �F�ݒ�
    SetColorPlayingEffekseer3DEffect(m_PlayingEffectHandle, color.red, color.green, color.blue, color.alpha);

#ifdef AQUA_DEBUG
    if (IsEffekseer3DEffectPlaying(m_PlayingEffectHandle) == AQUA_DX_ERROR)
        return;

    // DTS�̑��x�����ɑΉ�
    SetSpeedPlayingEffekseer3DEffect(m_PlayingEffectHandle, m_PlaySpeed * core::CVisualDebugger::GetInstance().GetDebugDeltaTimeScale());
#endif
}

/*
 *  �`��
 */
void
aqua::CEffect3D::
Draw(void)
{
    // ��\���ݒ�
    if (!visible) return;

    // �G�t�F�N�g���Đ�����Ă��Ȃ�
    if (IsEffekseer3DEffectPlaying(m_PlayingEffectHandle) == AQUA_DX_ERROR)
        return;

    DrawEffekseer3D_Begin();

    DrawEffekseer3D_Draw(m_PlayingEffectHandle);

    DrawEffekseer3D_End();
}

/*
 *  �Đ�
 */
void
aqua::CEffect3D::
Play(void)
{
    if (m_PlayingEffectHandle != AQUA_UNUSED_HANDLE)
        Stop();

    // �G�t�F�N�g�Đ�
    m_PlayingEffectHandle = PlayEffekseer3DEffect(m_Effekseer.GetResourceHandle());
}

/*
 *  ��~
 */
void
aqua::CEffect3D::
Stop(void)
{
    if (m_PlayingEffectHandle != AQUA_UNUSED_HANDLE)
        return;

    // �G�t�F�N�g�̒�~
    StopEffekseer3DEffect(m_PlayingEffectHandle);

    m_PlayingEffectHandle = AQUA_UNUSED_HANDLE;
}

/*
 *  �G�t�F�N�g�I�����m
 */
bool
aqua::CEffect3D::
Finished(void)
{
    return IsEffekseer3DEffectPlaying(m_PlayingEffectHandle);
}

/*
 *  �Đ����̃G�t�F�N�g�̍Đ����x�擾
 */
float
aqua::CEffect3D::
GetPlayingSpeed(void)
{
    return m_PlaySpeed;
}

/*
 *  �Đ����̃G�t�F�N�g�̍Đ����x�ݒ�
 */
void
aqua::CEffect3D::
SetPlayingSpeed(float speed)
{
    // �G�t�F�N�g���Đ�����Ă��Ȃ�
    if (IsEffekseer3DEffectPlaying(m_PlayingEffectHandle) == AQUA_DX_ERROR)
        return;

    m_PlaySpeed = speed;

    // �Đ����x��ݒ�
    SetSpeedPlayingEffekseer3DEffect(m_PlayingEffectHandle, m_PlaySpeed);
}

/*
 *  ���\�[�X�n���h���擾
 */
int
aqua::CEffect3D::
GetResourceHandle(void) const
{
    return m_Effekseer.GetResourceHandle();
}
