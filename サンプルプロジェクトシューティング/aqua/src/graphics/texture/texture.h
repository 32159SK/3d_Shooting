
/*!
 *  @file       texture.h
 *  @brief      2Dテクスチャクラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "texture_resource\texture_resource.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CTexture
     *
     *  @brief      テクスチャクラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CTexture
    {
    public:
        /*!
         *  @brief      コンストラクタ
         */
        CTexture( void );

        /*!
         *  @brief      コピーコンストラクタ
         *
         *  @param[in]  texture     テクスチャクラス
         */
        CTexture( const CTexture& texture );

        /*!
         *  @brief      デストラクタ
         */
        ~CTexture( void ) = default;

        /*!
         *  @brief      テクスチャの読み込み
         *
         *  @param[in]  file_name   ファイル名
         */
        void    Load( const std::string& file_name );

        /*!
         *  @brief      テクスチャの解放
         */
        void    Unload( void );

        /*!
         *  @brief      テクスチャのリソースハンドル取得
         *
         *  @return     テクスチャのリソースハンドル取得
         */
        int     GetResourceHandle( void ) const
        {
            if (!m_TextureResource) return AQUA_UNUSED_HANDLE;

            return m_TextureResource->GetResourceHandle();
        }

        /*!
         *  @brief      テクスチャの横幅取得
         *
         *  @return     テクスチャの横幅
         */
        int     GetWidth(void) const
        {
            if (!m_TextureResource) return 0;

            return m_TextureResource->GetWidth();
        }

        /*!
         *  @brief      テクスチャの縦幅取得
         *
         *  @return     テクスチャの縦幅
         */
        int     GetHeight( void ) const
        {
            if (!m_TextureResource) return 0;

            return m_TextureResource->GetHeight();
        }

        /*!
         *  @brief      テクスチャの読み込みチェック
         *
         *  @retval     true    読み込み済み
         *  @retval     false   読み込まれていない
         */
        bool    IsEnable( void ) const
        {
            if (!m_TextureResource) return false;

            return m_TextureResource->IsEnable();
        }


        /*!
         *  @brief      代入演算子のオーバーロード
         *
         *  @param[in]  texture     テクスチャクラス
         */
        CTexture&   operator=( const CTexture& texture );

    private:
        /*!
         *  @brief      テクスチャの生成
         *
         *  @param[in]  width           横幅
         *  @param[in]  height          縦幅
         *  @param[in]  alpha_channel   アルファチャンネル
         */
        void    Create( int width, int height, bool alpha_channel );

        /*!
         *  @brief      テクスチャの解放
         */
        void    Delete( void );

        /*!
         *  @brief      CSurfaceクラスをフレンド登録
         */
        friend class CSurface;

        //! テクスチャリソースクラス
        core::CTextureResource*     m_TextureResource;
    };
}
