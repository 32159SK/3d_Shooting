
/*!
 *  @file       fmf_loader.cpp
 *  @brief      FMF���[�_�[
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "fmf_loader.h"
#include "..\..\debug\debug.h"
#include "..\memory\memory.h"

/*
 *  �R���X�g���N�^
 */
aqua::CFMFLoader::CFMFLoader( void )
    : m_Data( nullptr )
    , m_ChipLineCount( 0 )
{
    memset( &m_Header, 0, sizeof( m_Header ) );
}

/*
 *  FMF�t�@�C���ǂݍ���
 */
void
aqua::CFMFLoader::
Load( const std::string& file_name )
{
    // �O�̂��߉������
    Unload( );

    FILE* fp = nullptr;

    // �t�@�C�����J��
    fopen_s( &fp, file_name.c_str( ), "rb" );

    AQUA_ASSERT( fp, file_name + "�̓ǂݍ��݂Ɏ��s���܂����B" );

    // �w�b�_���ǂݍ���
    fread( &m_Header, sizeof( m_Header ), 1, fp );

    // �f�[�^���p�o�b�t�@����
    m_Data = AQUA_NEW unsigned char[m_Header.size];

    // �f�[�^���ǂݍ���
    fread( m_Data, m_Header.size, 1, fp );

    // �t�@�C�������
    fclose( fp );

    m_ChipLineCount = ( m_Header.bitCount ? 16 : 255 );
}

/*
 *  ���
 */
void
aqua::CFMFLoader::
Unload( void )
{
    // �f�[�^�������
    AQUA_SAFE_DELETE_ARRAY( m_Data );

    // �w�b�_�����N���A
    memset( &m_Header, 0, sizeof( m_Header ) );
}

/*
 *  �f�[�^���̃T�C�Y�擾
 */
int
aqua::CFMFLoader::
GetSize( void )
{
    return m_Header.size;
}

/*
 *  ���C���[���擾
 */
int
aqua::CFMFLoader::
GetLayerCount( void )
{
    return m_Header.layerCount;
}

/*
 *  �}�b�v�̕��擾
 */
int
aqua::CFMFLoader::
GetMapWidth( void )
{
    return m_Header.mapWidth;
}

/*
 *  �}�b�v�̍����擾
 */
int
aqua::CFMFLoader::
GetMapHeight( void )
{
    return m_Header.mapHeight;
}

/*
 *  �`�b�v�̕��擾
 */
int
aqua::CFMFLoader::
GetChipWidth( void )
{
    return m_Header.chipWidth;
}

/*
 *  �`�b�v�̍����擾
 */
int
aqua::CFMFLoader::
GetChipHeight( void )
{
    return m_Header.chipHeight;
}

/*
 *  �f�[�^���擾
 */
unsigned char*
aqua::CFMFLoader::
GetData( void )
{
    return m_Data;
}

/*
 *  1���C���[�ӂ�̃T�C�Y
 */
int
aqua::CFMFLoader::
GetLayerSize( void )
{
    return m_Header.mapWidth * m_Header.mapHeight * ( m_Header.bitCount / 8 );
}

/*
 *  ���C���[�ʃf�[�^���擾
 */
unsigned char*
aqua::CFMFLoader::
GetLayerData( int layer_id )
{
    // 1���C���[�ӂ�̃T�C�Y
    int layer_size = GetLayerSize( );

    return m_Data + ( layer_id * layer_size );
}

/*
 *  ���ɕ���ł���`�b�v�̐�
 */
int
aqua::CFMFLoader::
GetChipLineCount( void )
{
    return m_ChipLineCount;
}
