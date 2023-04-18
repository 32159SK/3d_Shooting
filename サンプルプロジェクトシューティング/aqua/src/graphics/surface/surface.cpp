
/*!
 *  @file       surface.cpp
 *  @brief      �T�[�t�F�C�X�N���X
 *  @author     Kazuya Maruyama
 *  @date       2018/12/19
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include <DxLib.h>
#include "surface.h"
#include "..\..\debug\debug.h"
#include "..\..\utility\memory\memory.h"

/*
 *  �R���X�g���N�^
 */
aqua::CSurface::
CSurface( void )
{
}

/*
 *  �T�[�t�F�C�X�쐬
 */
void
aqua::CSurface::
Create( int width, int height, bool alpha_channel )
{
    m_Texture.Create( width, height, alpha_channel );
}

/*
 *  �T�[�t�F�C�X���
 */
void
aqua::CSurface::
Delete( void )
{
    m_Texture.Delete( );
}

/*
 *  �T�[�t�F�C�X�ւ̕`��J�n
 */
void
aqua::CSurface::
Begin( void )
{
    if( !m_Texture.IsEnable( ) )
        return;

    // ���������T�[�t�F�C�X�ɏ�������
    SetDrawScreen( m_Texture.GetResourceHandle( ) );
}

/*
 *  �T�[�t�F�C�X�ւ̕`��I��
 */
void
aqua::CSurface::
End( void )
{
    // �������ݐ���o�b�N�o�b�t�@�ɖ߂�
    SetDrawScreen( DX_SCREEN_BACK );
}

/*
 *  �`���̃X�N���[�����T�[�t�F�C�X�ɃR�s�[
 */
void
aqua::CSurface::
CopyDrawScreen( void )
{
    if( !m_Texture.IsEnable( ) )
        return;

    // �`���̃X�N���[�����T�[�t�F�C�X�ɃR�s�[
    GetDrawScreenGraph( 0, 0, m_Texture.GetWidth( ), m_Texture.GetHeight( ), m_Texture.GetResourceHandle( ) );
}

/*
 *  �e�N�X�`���̎擾
 */
aqua::CTexture
aqua::CSurface::
GetTexture( void )
{
    return m_Texture;
}

/*
 *  ���\�[�X�̓ǂݍ���(���g�p)
 */
void
aqua::CSurface::
Load( const std::string& file_name )
{
    (void)file_name;
}

/*
 *  ���\�[�X�̉��(���g�p)
 */
void
aqua::CSurface::
Unload( void )
{
}
