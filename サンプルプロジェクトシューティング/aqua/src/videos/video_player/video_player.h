
/*!
 *  @file       video_player.h
 *  @brief      ビデオプレイヤー
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <string>
#include "..\..\graphics\draw_object\draw_object.h"
#include "..\..\graphics\..\mathematics\mathematics.h"
#include "..\video\video.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CVideoPlayer
     *
     *  @brief      ビデオプレイヤークラス<br>
     *              avi形式・mpg形式に対応
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CVideoPlayer
        : public aqua::core::IDrawObject
    {
    public:
        //! 位置
        aqua::CVector2      position;

        /*!
         *  @brief      コンストラクタ
         */
        CVideoPlayer( void );

        /*!
         *  @brief      デストラクタ
         */
        ~CVideoPlayer( void ) = default;

        /*!
         *  @brief      再生用バッファ作成
         *
         *  @param[in]  file_name   ファイル名
         */
        void            Create( const std::string& file_name );

        /*!
         *  @brief      再生バッファの解放
         */
        void            Delete( void );

        /*!
         *  @brief      描画
         */
        void            Draw( void );

        /*!
         *  @brief      再生
         */
        void            Play( void );

        /*!
         *  @brief      停止
         */
        void            Stop( void );

        /*!
         *  @brief      一時停止
         */
        void            Pause(void);

        /*!
         *  @brief      終了判定
         */
        bool            Finished( void );

        /*!
         *  @brief      リソースハンドル取得
         *
         *  @return     リソースハンドル
         */
        int             GetResourceHandle( void ) const;

    private:
        //! ビデオクラス
        CVideo      m_Video;
        //! 再生フラグ
        bool        m_PlayFlag;
    };
}
