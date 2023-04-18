
/*!
 *  @file       color.h
 *  @brief      色
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

/*!
 *  @brief  aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CColor
     *
     *  @brief      色クラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CColor
    {
    public:
        /*!
         *  @brief      コンストラクタ
         */
        CColor( void );

        /*!
         *  @brief      コンストラクタ<br>
         *              ARGB(32bit)
         *
         *  @param[in]  color   ARGB色
         */
        CColor( unsigned int color );

        /*!
         *  @brief      コンストラクタ<br>
         *              各値0～255
         *
         *  @param[in]  a   アルファ値
         *  @param[in]  r   レッド値
         *  @param[in]  g   グリーン値
         *  @param[in]  b   ブルー値
         */
        CColor( unsigned char a, unsigned char r, unsigned char g, unsigned char b );

        /*!
         *  @brief      デストラクタ
         */
        ~CColor(void) = default;

        /*!
         *  @brief      代入演算子
         *
         *  @param[in]  color   カラー(ARGB32bit)
         *
         *  @return     カラークラス
         */
        CColor&         operator=( unsigned int color );

        /*!
         *  @brief      代入演算子
         *
         *  @param[in]  color   カラークラス
         *
         *  @return     カラークラス
         */
        CColor&         operator=( const CColor& color );

        /*!
         *  @brief      色の取得
         *
         *  @return     ARGB(32bit)
         */
        unsigned int    GetColor( void ) const;

        /*!
         *  @brief      デバッグログに値を表示する
         */
        void            DebugLog(void);

        /*!
         *  @brief      色相環から色を取得
         *
         *  @param[in]  hue         色相
         *  @param[in]  saturation  彩度
         *  @param[in]  brightness  明度
         *
         *  @return     色
         */
        static unsigned int    ChangeHSVToColor(float hue, float saturation, float brightness);

        /*!
         *  @brief      整数を元に色相環から色を取得
         *
         *  @param[in]  step    節目となる値
         *  @param[in]  number  カラーに変換する数値
         *
         *  @return     色
         */
        static unsigned int    ChangeNumberToColor(int step, int number);

        //! カラーの最大値
        static const unsigned char  MAX_COLOR;
        //! ホワイト
        static const CColor         WHITE;
        //! ブラック
        static const CColor         BLACK;
        //! レッド
        static const CColor         RED;
        //! グリーン
        static const CColor         GREEN;
        //! ブルー
        static const CColor         BLUE;
        //! シアン
        static const CColor         CYAN;
        //! マゼンタ
        static const CColor         MAGENTA;
        //! イエロー
        static const CColor         YELLOW;
        //! アルファ値
        unsigned char               alpha;
        //! レッド値
        unsigned char               red;
        //! グリーン値
        unsigned char               green;
        //! ブルー値
        unsigned char               blue;
    };
}
