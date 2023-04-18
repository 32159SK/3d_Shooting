
/*!
 *  @file       csv_loader.cpp
 *  @brief      CSVローダー
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
 *  コンストラクタ
 */
aqua::CCSVLoader::
CCSVLoader( void )
    : m_Cols( 0 )
    , m_Rows( 0 )
{
    m_Data.clear( );
}

/*
 *  CSVファイル読み込み
 */
void
aqua::CCSVLoader::
Load( const std::string& file_name )
{
    // 念のため解放する
    Unload( );

    // ファイルを開く
    std::ifstream ifs( file_name );

    AQUA_ASSERT( !ifs.fail( ), file_name + "の読み込みに失敗しました。" );

    std::string line;

    // 行を取得
    while( getline( ifs, line ) )
    {
        std::istringstream stream( line );

        std::string field;

        // カンマ区切りで項目を取得
        while( getline( stream, field, ',' ) )
            m_Data.push_back( field );

        // 縦に並んでいる数をカウント
        ++m_Rows;
    }

    // 横に並んでいる数を算出
    m_Cols = (int)m_Data.size( ) / m_Rows;
}

/*
 *  解放
 */
void
aqua::CCSVLoader::
Unload( void )
{
    m_Data.clear( );

    m_Cols = m_Rows = 0;
}

/*
 *  横に並んでいる数を取得
 */
int
aqua::CCSVLoader::
GetCols( void )
{
    return m_Cols;
}

/*
 *  縦に並んでいる数を取得
 */
int
aqua::CCSVLoader::
GetRows( void )
{
    return m_Rows;
}

/*
 *  データ数を取得
 */
int
aqua::CCSVLoader::
GetDataCount( void )
{
    return (int)m_Data.size( );
}

/*
 *  指定されたデータを文字列で取得
 */
std::string
aqua::CCSVLoader::
GetString( int rows, int cols )
{
    return m_Data[( rows * m_Cols ) + cols];
}

/*
 *  指定されたデータを整数に変換して取得
 */
int
aqua::CCSVLoader::
GetInteger( int rows, int cols )
{
    return stoi( m_Data[( rows * m_Cols ) + cols] );
}

/*
 *  指定されたデータを実数に変換して取得
 */
float
aqua::CCSVLoader::
GetFloat( int rows, int cols )
{
    return stof( m_Data[( rows * m_Cols ) + cols] );
}
