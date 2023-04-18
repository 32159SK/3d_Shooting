
/*!
*  @file       video_player.cpp
*  @brief      �r�f�I�v���C���[
*  @author     Kazuya Maruyama
*  @date       2021/03/10
*  @version    7.17
*
*  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
*/

#include <DxLib.h>
#include "video_player.h"
#include "..\..\framework\framework.h"
#include "..\..\utility\memory\memory.h"

/*
 *  �R���X�g���N�^
 */
aqua::CVideoPlayer::
CVideoPlayer( void )
    : m_PlayFlag( false )
    , position( CVector2::ZERO )
{
}

/*
 *  �ǂݍ���
 */
void
aqua::CVideoPlayer::
Create( const std::string& file_name )
{
    Delete( );

    m_Video.Load( file_name );
}

/*
 *  ���
 */
void
aqua::CVideoPlayer::
Delete( void )
{
    m_Video.Unload( );
}

/*
 *  �`��
 */
void
aqua::CVideoPlayer::
Draw( void )
{
    // �r�f�I���ǂݍ��܂�Ă��Ȃ���Ε`�悵�Ȃ�
    if( !m_Video.IsEnable( ) ) return;

    // ��\���̎��͕`�悵�Ȃ�
    if( !visible ) return;

    // �`��
    DrawExtendGraph( (int)position.x, (int)position.y, aqua::core::CFramework::GetInstance( ).GetWindowWidth( ), aqua::core::CFramework::GetInstance( ).GetWindowHeight( ), m_Video.GetResourceHandle( ), FALSE ) ;
}

/*
 *  �Đ�
 */
void
aqua::CVideoPlayer::
Play( void )
{
    if( m_PlayFlag ) return;

    m_PlayFlag = true;

    PlayMovieToGraph( m_Video.GetResourceHandle( ) );
}

/*
 *  ��~
 */
void
aqua::CVideoPlayer::
Stop( void )
{
    if( !m_PlayFlag ) return;

    m_PlayFlag = false;

    // ��ʂ��ꎞ��~
    PauseMovieToGraph( m_Video.GetResourceHandle( ) );

    // ����̍Đ��ʒu��擪�ɖ߂�
    SeekMovieToGraph(m_Video.GetResourceHandle(), 0);
}

/*
 *  �ꎞ��~
 */
void
aqua::CVideoPlayer::
Pause(void)
{
    if (!m_PlayFlag) return;

    m_PlayFlag = false;

    // ��ʂ��ꎞ��~
    PauseMovieToGraph(m_Video.GetResourceHandle());
}

/*
 *  �I������
 */
bool
aqua::CVideoPlayer::
Finished( void )
{
    if( !m_PlayFlag ) return true;

    return ( !GetMovieStateToGraph( m_Video.GetResourceHandle( ) ) );
}

/*
 *  ���\�[�X�n���h���擾
 */
int
aqua::CVideoPlayer::
GetResourceHandle( void ) const
{
    return m_Video.GetResourceHandle( );
}
