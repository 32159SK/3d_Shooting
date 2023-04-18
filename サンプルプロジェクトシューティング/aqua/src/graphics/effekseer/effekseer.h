
/*!
 *  @file       effekseer.h
 *  @brief      Effekseerクラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "effekseer_resource\effekseer_resource.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CEffekseer
     *
     *  @brief      Effekseerクラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CEffekseer
    {
    public:
        /*!
         *  @brief      コンストラクタ
         */
        CEffekseer( void );

        /*!
         *  @brief      コピーコンストラクタ
         *
         *  @param[in]  effect     Effekseerクラス
         */
        CEffekseer( const CEffekseer& effect );

        /*!
         *  @brief      デストラクタ
         */
        ~CEffekseer( void ) = default;

        /*!
         *  @brief      Effekseerの読み込み
         *
         *  @param[in]  file_name   ファイル名
         */
        void    Load( const std::string& file_name );

        /*!
         *  @brief      Effekseerの解放
         */
        void    Unload( void );

        /*!
         *  @brief      Effekseerのリソースハンドル取得
         *
         *  @return     Effekseerのリソースハンドル取得
         */
        int     GetResourceHandle( void ) const
        {
            if (!m_EffekseerResource) return AQUA_UNUSED_HANDLE;

            return m_EffekseerResource->GetResourceHandle();
        }

        /*!
         *  @brief      Effekseerの読み込みチェック
         *
         *  @retval     true    読み込み済み
         *  @retval     false   読み込まれていない
         */
        bool    IsEnable( void ) const
        {
            // リソースがない
            if (!m_EffekseerResource) return false;

            // 読み込まれていない
            return m_EffekseerResource->IsEnable();
        }

        /*!
         *  @brief      代入演算子のオーバーロード
         *
         *  @param[in]  effect     Effekseerクラス
         */
        CEffekseer&   operator=( const CEffekseer& effect );

    private:
        //! Effekseerリソースクラス
        core::CEffekseerResource*   m_EffekseerResource;
    };
}
