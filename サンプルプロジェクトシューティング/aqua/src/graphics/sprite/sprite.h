
/*!
 *  @file       sprite.h
 *  @brief      テクスチャ描画クラス
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
#include "..\graphic_filter\graphic_filter.h"
#include "..\texture\texture.h"
#include "..\surface\surface.h"
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
     *  @class      CSprite
     *
     *  @brief      テクスチャ描画クラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CSprite
        : public aqua::core::IDrawObject
    {
    public:
        //! 位置
        aqua::CVector2      position;
        //! 色
        aqua::CColor        color;
        //! 描画範囲
        aqua::CRect         rect;
        //! 拡縮・回転の基準点
        aqua::CVector2      anchor;
        //! 拡大率
        aqua::CVector2      scale;
        //! 回転値
        float               rotation;
        //! アルファブレンドモード
        aqua::ALPHABLEND    blend_mode;

        /*!
         *  @brief      コンストラクタ
         */
        CSprite( void );

        /*!
         *  @brief      デストラクタ
         */
        ~CSprite( void ) = default;

        /*!
         *  @brief      生成
         *
         *  @param[in]  file_name   テクスチャファイル名
         */
        void    Create( const std::string& file_name );

        /*!
         *  @brief      生成
         *
         *  @param[in]  surface     サーフェイスクラス
         */
        void    Create( const CSurface& surface );

        /*!
         *  @brief      解放
         */
        void    Delete( void );

        /*!
         *  @brief      描画
         */
        void    Draw( void );

        /*!
         *  @brief      ガウスフィルターの適用
         *
         *  @param[in]  pixel_width     8, 16, 32のいずれか
         *  @param[in]  param           100で1px分の幅
         */
        void    ApplyGaussFilter( int pixel_width, int param );

        /*!
         *  @brief      グラフィックフィルターの解除
         */
        void    UnsetGraphicFilter( void );

        /*!
         *  @brief      テクスチャの幅取得
         *
         *  @return     テクスチャの幅
         */
        int     GetTextureWidth(void) const { return m_Texture.GetWidth(); }

        /*!
         *  @brief      テクスチャの高さ取得
         *
         *  @return     テクスチャの高さ
         */
        int     GetTextureHeight(void) const { return m_Texture.GetHeight(); }

        /*!
         *  @brief      リソースハンドル取得
         *
         *  @return     リソースハンドル
         */
        int     GetResourceHandle(void) const { return m_Texture.GetResourceHandle(); }

    private:
        //! テクスチャ
        aqua::CTexture          m_Texture;
        //! グラフィックフィルター
        aqua::GRAPHIC_FILTER    m_GraphicFilter;
        //! ガウスフィルター用ピクセル幅
        int                     m_GaussFilterPixelWitdh;
        //! ガウスフィルター用パラメータ
        int                     m_GaussFilterParam;
    };
}
