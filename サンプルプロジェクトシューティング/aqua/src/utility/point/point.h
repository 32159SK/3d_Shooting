
/*!
 *  @file       point.h
 *  @brief      点クラス
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
     *  @class      CPoint
     *
     *  @brief      点クラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CPoint
    {
    public:
        //! X成分
        int     x;
        //! Y成分
        int     y;

        /*!
         *  @brief      コンストラクタ
         */
        CPoint( void );

        /*!
         *  @brief      コンストラクタ
         *
         *  @param[in]  point    点クラス
         */
        CPoint( const CPoint& point );

        /*!
         *  @brief      コンストラクタ
         *
         *  @param[in]  x   X成分
         *  @param[in]  y   Y成分
         */
        CPoint( int x, int y );

        /*!
         *  @brief      デストラクタ
         */
        ~CPoint( void ) = default;

        /*!
         *  @brief      デバッグログに値を表示する
         */
        void    DebugLog( void );

        //! 要素がすべて0
        static const CPoint  ZERO;
    };
}
