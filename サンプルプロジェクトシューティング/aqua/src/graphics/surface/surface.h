
/*!
 *  @file       surface.h
 *  @brief      サーフェイスクラス
 *  @author     Kazuya Maruyama
 *  @date       2018/12/19
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "..\texture\texture.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CSurface
     *
     *  @brief      サーフェイスクラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2018/12/19
     *
     *  @version    7.17
     */
    class CSurface
    {
    public:
        /*!
         *  @brief  コンストラクタ
         */
        CSurface( void );

        /*!
         *  @brief  デストラクタ
         */
        ~CSurface( void ) = default;

        /*!
         *  @brief  サーフェイス作成
         *
         *  @param[in]  width           横幅
         *  @param[in]  height          縦幅
         *  @param[in]  alpha_channel   アルファチャンネルの使用
         */
        void    Create( int width, int height, bool alpha_channel = false );

        /*!
         *  @brief  サーフェイス解放
         */
        void    Delete( void );

        /*!
         *  @brief  サーフェイスへの描画開始
         */
        void    Begin( void );

        /*!
         *  @brief  サーフェイスへの描画終了
         */
        void    End( void );

        /*!
         *  @brief  描画先のスクリーンをサーフェイスにコピーする
         */
        void    CopyDrawScreen( void );

        /*!
         *  @brief  テクスチャの取得
         *
         *  @return テクスチャ
         */
        CTexture    GetTexture( void );

    private:
        /*!
         *  @brief  リソースの読み込み(未使用)
         *
         *  @param[in]  file_name   ファイル名
         */
        void    Load( const std::string& file_name );

        /*!
         *  @brief  リソースの解放(未使用)
         */
        void    Unload( void );

        /*!
         *  @brief  スプライトクラスをフレンド登録
         */
        friend class CSprite;

        //! テクスチャクラス
        aqua::CTexture  m_Texture;
    };
}
