
/*!
 *  @file       effect2D.cpp
 *  @brief      Effekseer�p3D�G�t�F�N�g
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "effect2D.h"
#include "..\..\debug\debug.h"

 /*
  *  �R���X�g���N�^
  */
aqua::CEffect2D::
CEffect2D(void)
    : position(aqua::CVector2::ZERO)
    , scale(aqua::CVector2::ONE)
    , rotation(0.0f)
    , color(aqua::CColor::WHITE)
    , m_PlayingEffectHandle(AQUA_UNUSED_HANDLE)
    , m_PlaySpeed(1.0f)
{
}

/*
 *  ����
 */
void
aqua::CEffect2D::
Create(const std::string& file_name)
{
    Delete();

    m_Effekseer.Load(file_name);
}

/*
 *  ���
 */
void
aqua::CEffect2D::
Delete(void)
{
    // �Đ����x�𓙔{�ɖ߂�
    m_PlaySpeed = 1.0f;

    if(m_PlayingEffectHandle != AQUA_UNUSED_HANDLE)
        StopEffekseer2DEffect(m_PlayingEffectHandle);

    m_PlayingEffectHandle = AQUA_UNUSED_HANDLE;

    m_Effekseer.Unload();
}

/*
 *  �X�V
 */
void
aqua::CEffect2D::
Update(void)
{
    // �G�t�F�N�g���Đ�����Ă��Ȃ�
    if (IsEffekseer2DEffectPlaying(m_PlayingEffectHandle) == AQUA_DX_ERROR)
        return;

    // �\���ʒu��ݒ�
    SetPosPlayingEffekseer2DEffect(m_PlayingEffectHandle, position.x, position.y, 0.0f);

    // �g�嗦��ݒ�
    SetScalePlayingEffekseer2DEffect(m_PlayingEffectHandle, scale.x, scale.y, 1.0f );

    // ��]�l��ݒ�
    SetRotationPlayingEffekseer2DEffect(m_PlayingEffectHandle, 0.0f, rotation, 0.0f);

    // �F�ݒ�
    SetColorPlayingEffekseer2DEffect(m_PlayingEffectHandle, color.red, color.green, color.blue, color.alpha);

#ifdef AQUA_DEBUG
    if (IsEffekseer2DEffectPlaying(m_PlayingEffectHandle) == AQUA_DX_ERROR)
        return;

    // DTS�̑��x�����ɑΉ�
    SetSpeedPlayingEffekseer2DEffect(m_PlayingEffectHandle, m_PlaySpeed * core::CVisualDebugger::GetInstance().GetDebugDeltaTimeScale());
#endif
}

/*
 *  �`��
 */
void
aqua::CEffect2D::
Draw(void)
{
    // ��\���ݒ�
    if (!visible) return;

    // �G�t�F�N�g���Đ�����Ă��Ȃ�
    if (IsEffekseer2DEffectPlaying(m_PlayingEffectHandle) == AQUA_DX_ERROR)
        return;

    DrawEffekseer2D_Begin();

    DrawEffekseer2D_Draw(m_PlayingEffectHandle);

    DrawEffekseer2D_End();
}

/*
 *  �Đ�
 */
void
aqua::CEffect2D::
Play(void)
{
    if (m_PlayingEffectHandle != AQUA_UNUSED_HANDLE)
        Stop();

    // �G�t�F�N�g�Đ�
    m_PlayingEffectHandle = PlayEffekseer2DEffect(m_Effekseer.GetResourceHandle());
}

/*
 *  ��~
 */
void
aqua::CEffect2D::
Stop(void)
{
    if (m_PlayingEffectHandle != AQUA_UNUSED_HANDLE)
        return;

    // �G�t�F�N�g�̒�~
    StopEffekseer2DEffect(m_PlayingEffectHandle);

    m_PlayingEffectHandle = AQUA_UNUSED_HANDLE;
}

/*
 *  �G�t�F�N�g�I�����m
 */
bool
aqua::CEffect2D::
Finished(void)
{
    return IsEffekseer2DEffectPlaying(m_PlayingEffectHandle);
}

/*
 *  �Đ����̃G�t�F�N�g�̍Đ����x�擾
 */
float
aqua::CEffect2D::
GetPlayingSpeed(void)
{
    return m_PlaySpeed;
}

/*
 *  �Đ����̃G�t�F�N�g�̍Đ����x�ݒ�
 */
void
aqua::CEffect2D::
SetPlayingSpeed(float speed)
{
    // �G�t�F�N�g���Đ�����Ă��Ȃ�
    if (IsEffekseer2DEffectPlaying(m_PlayingEffectHandle) == AQUA_DX_ERROR)
        return;

    m_PlaySpeed = speed;

    // �Đ����x��ݒ�
    SetSpeedPlayingEffekseer2DEffect(m_PlayingEffectHandle, m_PlaySpeed);
}

/*
 *  ���\�[�X�n���h���擾
 */
int
aqua::CEffect2D::
GetResourceHandle( void ) const
{
    return m_Effekseer.GetResourceHandle( );
}
