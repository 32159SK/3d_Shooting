
/*!
 *  @file       csv_loader.h
 *  @brief      CSVローダー
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <vector>
#include <string>

/*!
 *  @brief  aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CCSVLoader
     *
     *  @brief      CSVローダークラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CCSVLoader
    {
    public:
        /*!
         *  @brief      コンストラクタ
         */
        CCSVLoader(void);

        /*!
         *  @brief      デストラクタ
         */
        ~CCSVLoader(void) = default;

        /*!
         *  @brief      FMFファイル読み込み
         *
         *  @param[in]  file_name   ファイル名
         */
        void        Load(const std::string& file_name);

        /*!
         *  @brief      解放
         */
        void        Unload(void);

        /*!
         *  @brief      横に並んでいる数を取得
         *
         *  @return     横に並んでいる数
         */
        int         GetCols(void);

        /*!
         *  @brief      縦に並んでいる数を取得
         *
         *  @return     縦に並んでいる数
         */
        int         GetRows(void);

        /*!
         *  @brief      データ数を取得
         *
         *  @return     データ数
         */
        int         GetDataCount(void);

        /*!
         *  @brief      指定されたデータを文字列で取得
         *
         *  @param[in]  rows    縦
         *  @param[in]  cols    横
         *
         *  @return     指定されたデータの文字列
         */
        std::string GetString(int rows, int cols);

       /*!
        *  @brief      指定されたデータを整数に変換して取得
        *
        *  @param[in]  rows    縦
        *  @param[in]  cols    横
        *
        *  @return     指定されたデータ(整数)
        */
        int         GetInteger(int rows, int cols);

       /*!
        *  @brief      指定されたデータを実数に変換して取得
        *
        *  @param[in]  rows    縦
        *  @param[in]  cols    横
        *
        *  @return     指定されたデータ(実数)
        */
        float       GetFloat(int rows, int cols);

    private:
        /*!
         *  @brief      CSVデータリスト
         */
        typedef std::vector<std::string>    CSV_DATA;

        //! データ
        CSV_DATA    m_Data;
        //! 横に並んでいるデータの個数
        int         m_Cols;
        //! 縦に並んでいるデータの個数
        int         m_Rows;
    };
}
