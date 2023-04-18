
/*!
 *  @file       texture_resource.h
 *  @brief      テクスチャリソース
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "..\..\..\resources\resources.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @brief      aqua::core名前空間
     */
    namespace core
    {
        /*!
         *  @class      CTextureResource
         *
         *  @brief      テクスチャリソースクラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CTextureResource
            : public core::IResourceObject
        {
        public:
            /*!
             *  @brief      コンストラクタ
             */
            CTextureResource( void );

            /*!
             *  @brief      デストラクタ
             */
            ~CTextureResource( void ) = default;

            /*!
             *  @brief      テクスチャの読み込み
             *
             *  @param[in]  file_name   ファイル名
             */
            void        Load( const std::string& file_name );

            /*!
             *  @brief      テクスチャの解放
             */
            void        Unload( void );

            /*!
             *  @brief      テクスチャの横幅取得
             *
             *  @return     テクスチャの横幅
             */
            int         GetWidth(void) const { return m_Width; }

            /*!
             *  @brief      テクスチャの縦幅取得
             *
             *  @return     テクスチャの縦幅
             */
            int         GetHeight(void) const { return m_Height; }

        private:
            /*!
             *  @brief      クラスをフレンド登録
             */
            friend class CTexture;
            friend class CTextureManager;

            /*!
             *  @brief      テクスチャの生成
             *
             *  @param[in]  width           横幅
             *  @param[in]  height          縦幅
             *  @param[in]  alpha_channel   アルファチャンネル
             */
            void        Create( int width, int height, bool alpha_channel );

            /*!
             *  @brief      テクスチャの解放
             */
            void        Delete( void );

            //! 透過色(マゼンタ : 0xffff00ff)
            static const unsigned int   m_transparent_color;
            //! テクスチャの幅
            int                         m_Width;
            //! テクスチャの高さ
            int                         m_Height;
        };
    }
}
