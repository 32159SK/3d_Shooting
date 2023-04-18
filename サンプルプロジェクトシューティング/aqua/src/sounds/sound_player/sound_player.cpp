
/*!
 *  @file       sound_player.cpp
 *  @brief      �T�E���h�v���C���[
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include <DxLib.h>
#include "sound_player.h"
#include "..\sound\sound_manager\sound_manager.h"
#include "..\..\utility\memory\memory.h"

const int   aqua::CSoundPlayer::m_max_volume    =  255;
const int   aqua::CSoundPlayer::m_min_volume    =    0;

/*
 *  �R���X�g���N�^
 */
aqua::CSoundPlayer::
CSoundPlayer( void )
    : m_LoopFlag( false )
{
}

/*
 *  �Đ��p�o�b�t�@�쐬
 */
void
aqua::CSoundPlayer::
Create( const std::string& file_name, bool loop, int buffer_count )
{
    m_LoopFlag = loop;

    // ���[�v�Đ��Ȃ�o�b�t�@��1������������
    if( m_LoopFlag ) buffer_count = 1;

    m_Sound.Load( file_name, buffer_count );

    //SetFrequencySoundMem(44100 * 2, m_Sound.GetResourceHandle());
}

/*
 *  �Đ��p�o�b�t�@�쐬
 */
void
aqua::CSoundPlayer::
Create( const aqua::CSound& sound )
{
    m_Sound = sound;
}

/*
 *  ���
 */
void
aqua::CSoundPlayer::
Delete( void )
{
    m_Sound.Unload( );
}

/*
 *  �Đ�
 */
void
aqua::CSoundPlayer::
Play( void )
{
    if( m_Sound.IsEnable( ) )
        PlaySoundMem( m_Sound.GetResourceHandle( ), ( m_LoopFlag ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK ) );
}

/*
 *  ��~
 */
void
aqua::CSoundPlayer::
Stop( void )
{
    if( m_Sound.IsEnable( ) )
        StopSoundMem( m_Sound.GetResourceHandle( ) );
}

/*
 *  ���o�����čĐ�
 */
void
aqua::CSoundPlayer::
ReStart( void )
{
    Stop( );
    Play( );
}

/*
 *  ���݂̍Đ����Ԃ��擾
 */
float
aqua::CSoundPlayer::
GetCurrentPlayTime( void )
{
    return m_Sound.GetCurrentPlayTime( );
}

/*
 *  ���Đ����Ԃ��擾
 */
float
aqua::CSoundPlayer::
GetTotalTime( void )
{
    return m_Sound.GetTotalTime( );
}

/*
 *  �Đ��������ׂ�
 */
bool
aqua::CSoundPlayer::
IsPlaying()
{
    return CheckSoundMem(m_Sound.GetResourceHandle());
}

/*
 *  �{�����[���ݒ�
 */
void
aqua::CSoundPlayer::
SetVolume( int volume )
{
    // �ŏ��`�F�b�N
    if( volume < m_min_volume )
        volume = m_min_volume;

    // �ő�`�F�b�N
    if( volume > m_max_volume )
        volume = m_max_volume;

    ChangeVolumeSoundMem( volume, m_Sound.GetResourceHandle( ) );
}

/*
 *  ���\�[�X�n���h���擾
 */
int
aqua::CSoundPlayer::
GetResourceHandle( void ) const
{
    return m_Sound.GetResourceHandle( );
}

/*
 *  �\�t�g�E�F�A�T�E���h�n���h���擾
 */
int
aqua::CSoundPlayer::
GetSoftSoundHandle( void ) const
{
    return m_Sound.GetSoftSoundHandle( );
}
