
/*!
 *  @file       label.h
 *  @brief      文字列描画クラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>
#include <string>
#include "..\alphablend\alphablend.h"
#include "..\font\font.h"
#include "..\draw_object\draw_object.h"
#include "..\..\mathematics\mathematics.h"
#include "..\color\color.h"
#include "..\..\utility\utility.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CLabel
     *
     *  @brief      文字列描画クラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CLabel
        : public aqua::core::IDrawObject
    {
    public:
        //! テキスト
        std::string         text;
        //! 位置
        aqua::CVector2      position;
        //! 文字色
        aqua::CColor        color;
        //! エッジの色(alphaはcolorの値に影響される)
        aqua::CColor        edge_color;
        //! アルファブレンドモード
        aqua::ALPHABLEND    blend_mode;

        /*!
         *  @brief      コンストラクタ
         */
        CLabel( void );

        /*!
         *  @brief      デストラクタ
         */
        ~CLabel( void ) = default;

        /*!
         *  @brief      生成
         *
         *  @param[in]  size    サイズ
         */
        void    Create( int size );

        /*!
         *  @brief      生成
         *
         *  @param[in]  size_id     サイズID
         *  @param[in]  edge_bold   エッジの太さエッジの太さ(0 = エッジなし)
         */
        void    Create( int size, int edge_bold );

        /*!
          *  @brief      生成
          *
          *  @param[in]  size_id     サイズID
          *  @param[in]  edge_bold   エッジの太さエッジの太さ(0 = エッジなし)
          *  @param[in]  anti_aliasing   フォント名ID
          */
        void    Create( int size, int edge_bold, bool anti_aliasing );

        /*!
         *  @brief      生成
         *
         *  @param[in]  size_id     サイズID
         *  @param[in]  edge_bold   エッジの太さエッジの太さ(0 = エッジなし)
         *  @param[in]  family_id   フォント名ID
         */
        void    Create( int size, int edge_bold, bool anti_aliasing, aqua::FONT_FAMILY_ID family_id );

        /*!
         *  @brief      描画
         */
        void    Draw( void );

        /*!
         *  @brief      削除
         */
        void    Delete( void );

        /*!
         *  @brief      文字列幅の取得
         *
         *  @return     描画する文字列の横幅
         */
        int     GetTextWidth( void ) const;

        /*!
         *  @brief      フォントの高さ取得
         *
         *  @return     フォントの高さ
         */
        int     GetFontHeight( void ) const;

        /*!
         *  @brief      リソースハンドル取得
         *
         *  @return     リソースハンドル
         */
        int     GetResourceHandle( void ) const;


    private:
        //! フォントクラス
        aqua::CFont     m_Font;
    };
}
