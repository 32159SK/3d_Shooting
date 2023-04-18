
/*!
 *  @file       sound_resource.h
 *  @brief      サウンドリソースファイル
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <windows.h>
#include <string>
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
         *  @class      CSoundResource
         *
         *  @brief      サウンドリソースクラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CSoundResource
            : public core::IResourceObject
        {
        public:
            /*!
             *  @brief      コンストラクタ
             */
            CSoundResource( void );

            /*!
             *  @brief      デストラクタ
             */
            ~CSoundResource( void ) = default;

            /*!
             *  @brief      サウンドファイル読み込み
             *
             *  @param[in]  file_name   ファイル名
             *  @param[in]  count       SE多重再生用バッファの数
             */
            void            Load( const std::string& file_name, int buffer_count );

            /*!
             *  @brief      解放
             */
            void            Unload( void );

            /*!
             *  @brief      現在の再生時間を取得
             *
             *  @return     現在の再生時間(秒単位)
             */
            float           GetCurrentPlayTime( void );

            /*!
             *  @brief      総再生時間を取得
             *
             *  @return     総再生時間(秒単位)
             */
            float           GetTotalTime( void );

            /*!
             *  @brief      周波数を取得
             *
             *  @return     周波数(ヘルツ単位)
             */
            int             GetFrequency( void );

            /*!
             *  @brief      初期の周波数を取得
             *
             *  @return     周波数(ヘルツ単位)
             */
            int             GetDefaultFrequency( void );

            /*!
             *  @brief      周波数を設定
             *
             *  @param[in]  frequency   周波数(ヘルツ単位:44.10KHzの場合は44100)
             */
            void            SetFrequency( int frequency );

            /*!
             *  @brief      ソフトウェアサウンドハンドル取得
             *
             *  @return     ソフトウェアサウンドハンドル
             */
            int             GetSoftSoundHandle( void );


        private:
            //! ロードするバッファの最大数
            static const int    m_max_load_buffer;
            //! 初期の周波数
            int                 m_DefaultFrequency;
            //! ソフトウェアサウンドハンドル
            int                 m_SoftSoundHandle;
        };
    }
}
