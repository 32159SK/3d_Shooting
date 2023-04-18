
/*!
 *  @file       sound_player.h
 *  @brief      サウンドプレイヤー
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <string>
#include "..\sound\sound.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CSoundPlayer
     *
     *  @brief      サウンドプレイヤークラス<br>
     *              wav形式・mp3形式・ogg形式・opus形式に対応
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CSoundPlayer
    {
    public:
        /*!
         *  @brief      コンストラクタ
         */
        CSoundPlayer( void );

        /*!
         *  @brief      デストラクタ
         */
        ~CSoundPlayer( void ) = default;

        /*!
         *  @brief      再生用バッファ作成
         *
         *  @param[in]  file_name       ファイル名
         *  @param[in]  loop            ループ設定
         *  @param[in]  buffer_count    SE多重再生用バッファ数(ループ再生設定の場合は1になる)
         */
        void            Create( const std::string& file_name, bool loop = false, int buffer_count = 3 );

        /*!
         *  @brief      再生用バッファ作成
         *
         *  @param[in]  sound   サウンドクラス
         */
        void            Create( const aqua::CSound& sound );

        /*!
         *  @brief      再生バッファの解放
         */
        void            Delete( void );

        /*!
         *  @brief      再生
         */
        void            Play( void );

        /*!
         *  @brief      停止
         */
        void            Stop( void );

        /*!
         *  @brief      頭から再生しなおす
         */
        void            ReStart(void);

        /*!
         *  @brief      現在の再生時間を取得
         *
         *  @return     現在の再生時間(秒単位)
         */
        float           GetCurrentPlayTime(void);

        /*!
         *  @brief      総再生時間を取得
         *
         *  @return     総再生時間(秒単位)
         */
        float           GetTotalTime(void);

        /*!
         *  @brief      再生中か調べる
         *
         *  @retval     true    再生中
         *  @retval     false   再生していない
         */
        bool            IsPlaying(void);

        /*!
         *  @brief      ボリューム設定<br>
         *              0～255の整数で指定
         *
         *  @param[in]  volume  ボリューム
         */
        void            SetVolume( int volume );

        /*!
         *  @brief      リソースハンドル取得
         *
         *  @return     リソースハンドル
         */
        int             GetResourceHandle( void ) const;

        /*!
         *  @brief      ソフトウェアサウンドハンドル取得
         *
         *  @return     ソフトウェアサウンドハンドル
         */
        int             GetSoftSoundHandle( void ) const;

    private:
        //! 最大音量
        static const int    m_max_volume;
        //! 最小音量
        static const int    m_min_volume;
        //! サウンドクラス
        CSound              m_Sound;
        //! ループ再生フラグ
        bool                m_LoopFlag;
    };
}
