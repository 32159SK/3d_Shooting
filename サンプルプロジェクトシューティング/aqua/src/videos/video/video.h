
/*!
 *  @file       video.h
 *  @brief      ビデオ管理
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "video_resource\video_resource.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CVideo
     *
     *  @brief      ビデオクラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CVideo
    {
    public:
        /*!
         *  @brief      コンストラクタ
         */
        CVideo( void );

        /*!
         *  @brief      コピーコンストラクタ
         *
         *  @param[in]  video   ビデオクラス
         */
        CVideo( const CVideo& video );

        /*!
         *  @brief      デストラクタ
         */
        ~CVideo( void ) = default;

        /*!
         *  @brief      ビデオの読み込み
         *
         *  @param[in]  file_name   ファイル名
         */
        void        Load( const std::string& file_name );

        /*!
         *  @brief      ビデオの解放
         */
        void        Unload( void );

        /*!
         *  @brief      ビデオのリソースハンドル取得
         *
         *  @return     ビデオのリソースハンドル取得
         */
        int         GetResourceHandle( void ) const
        {
            if (!m_VideoResource) return AQUA_UNUSED_HANDLE;

            return m_VideoResource->GetResourceHandle();
        }

        /*!
         *  @brief      ビデオの読み込みチェック
         *
         *  @retval     true    読み込み済み
         *  @retval     false   読み込まれていない
         */
        bool        IsEnable( void ) const
        {
            if (!m_VideoResource) return false;

            return m_VideoResource->IsEnable();
        }


        /*!
         *  @brief      代入演算子のオーバーロード
         *
         *  @param[in]  video   ビデオクラス
         */
        CVideo&     operator=( const CVideo& video );

    private:
        //! ビデオリソースクラス
        core::CVideoResource*   m_VideoResource;
    };
}
