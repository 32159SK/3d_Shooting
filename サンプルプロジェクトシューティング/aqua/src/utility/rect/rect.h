
/*!
 *  @file       rect.h
 *  @brief      矩形クラス
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
     *  @class      CRect
     *
     *  @brief      矩形クラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CRect
    {
    public:
        //! 左端
        int     left;
        //! 上端
        int     top;
        //! 右端
        int     right;
        //! 下端
        int     bottom;

        /*!
         *  @brief      コンストラクタ
         */
        CRect( void );

        /*!
         *  @brief      コンストラクタ
         *
         *  @param[in]  rect    矩形クラス
         */
        CRect( const CRect& rect );

        /*!
         *  @brief      コンストラクタ
         *
         *  @param[in]  left    左側
         *  @param[in]  top     上側
         *  @param[in]  right   右側
         *  @param[in]  bottom  下側
         */
        CRect( int left, int top, int right, int bottom );

        /*!
         *  @brief      デストラクタ
         */
        ~CRect( void ) = default;

        /*!
         *  @brief      矩形の幅を取得
         *
         *  @return     矩形の幅
         */
        int     GetWidth( void ) const;

        /*!
         *  @brief      矩形の高さを取得
         *
         *  @return     矩形の高さ
         */
        int     GetHeight( void ) const;

        /*!
         *  @brief      デバッグログに値を表示する
         */
        void    DebugLog( void );

        //! 要素がすべて0
        static const CRect  ZERO;
    };
}
