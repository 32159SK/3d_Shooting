
/*!
 *  @file       csv_loader.cpp
 *  @brief      CSV���[�_�[
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "csv_loader.h"
#include "..\..\debug\debug.h"
#include <fstream>
#include <sstream>

/*
 *  �R���X�g���N�^
 */
aqua::CCSVLoader::
CCSVLoader( void )
    : m_Cols( 0 )
    , m_Rows( 0 )
{
    m_Data.clear( );
}

/*
 *  CSV�t�@�C���ǂݍ���
 */
void
aqua::CCSVLoader::
Load( const std::string& file_name )
{
    // �O�̂��߉������
    Unload( );

    // �t�@�C�����J��
    std::ifstream ifs( file_name );

    AQUA_ASSERT( !ifs.fail( ), file_name + "�̓ǂݍ��݂Ɏ��s���܂����B" );

    std::string line;

    // �s���擾
    while( getline( ifs, line ) )
    {
        std::istringstream stream( line );

        std::string field;

        // �J���}��؂�ō��ڂ��擾
        while( getline( stream, field, ',' ) )
            m_Data.push_back( field );

        // �c�ɕ���ł��鐔���J�E���g
        ++m_Rows;
    }

    // ���ɕ���ł��鐔���Z�o
    m_Cols = (int)m_Data.size( ) / m_Rows;
}

/*
 *  ���
 */
void
aqua::CCSVLoader::
Unload( void )
{
    m_Data.clear( );

    m_Cols = m_Rows = 0;
}

/*
 *  ���ɕ���ł��鐔���擾
 */
int
aqua::CCSVLoader::
GetCols( void )
{
    return m_Cols;
}

/*
 *  �c�ɕ���ł��鐔���擾
 */
int
aqua::CCSVLoader::
GetRows( void )
{
    return m_Rows;
}

/*
 *  �f�[�^�����擾
 */
int
aqua::CCSVLoader::
GetDataCount( void )
{
    return (int)m_Data.size( );
}

/*
 *  �w�肳�ꂽ�f�[�^�𕶎���Ŏ擾
 */
std::string
aqua::CCSVLoader::
GetString( int rows, int cols )
{
    return m_Data[( rows * m_Cols ) + cols];
}

/*
 *  �w�肳�ꂽ�f�[�^�𐮐��ɕϊ����Ď擾
 */
int
aqua::CCSVLoader::
GetInteger( int rows, int cols )
{
    return stoi( m_Data[( rows * m_Cols ) + cols] );
}

/*
 *  �w�肳�ꂽ�f�[�^�������ɕϊ����Ď擾
 */
float
aqua::CCSVLoader::
GetFloat( int rows, int cols )
{
    return stof( m_Data[( rows * m_Cols ) + cols] );
}
