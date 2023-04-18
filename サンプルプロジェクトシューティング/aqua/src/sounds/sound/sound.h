
/*!
 *  @file       sound.h
 *  @brief      サウンド管理
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "sound_resource\sound_resource.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CSound
     *
     *  @brief      サウンドクラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CSound
    {
    public:
        /*!
         *  @brief      コンストラクタ
         */
        CSound( void );

        /*!
         *  @brief      コピーコンストラクタ
         *
         *  @param[in]  sound   サウンドクラス
         */
        CSound( const CSound& sound );

        /*!
         *  @brief      デストラクタ
         */
        ~CSound( void ) = default;

        /*!
         *  @brief      サウンドの読み込み
         *
         *  @param[in]  file_name       ファイル名
         *  @param[in]  buffer_count    SE多重再生バッファ数
         */
        void        Load( const std::string& file_name, int buffer_count );

        /*!
         *  @brief      サウンドの解放
         */
        void        Unload( void );

        /*!
         *  @brief      現在の再生時間を取得
         *
         *  @return     現在の再生時間(秒単位)
         */
        float       GetCurrentPlayTime(void)
        {
            if (!m_SoundResource) return 0.0f;

            return m_SoundResource->GetCurrentPlayTime();
        }

        /*!
         *  @brief      総再生時間を取得
         *
         *  @return     総再生時間(秒単位)
         */
        float       GetTotalTime(void)
        {
            if (!m_SoundResource) return 0.0f;

            return m_SoundResource->GetTotalTime();
        }

        /*!
         *  @brief      サウンドのリソースハンドル取得
         *
         *  @return     サウンドのリソースハンドル取得
         */
        int         GetResourceHandle( void ) const
        {
            if (!m_SoundResource) return AQUA_UNUSED_HANDLE;

            return m_SoundResource->GetResourceHandle();
        }

        /*!
         *  @brief      ソフトウェアサウンドハンドル取得
         *
         *  @return     ソフトウェアサウンドハンドル
         */
        int         GetSoftSoundHandle(void) const
        {
            if (!m_SoundResource) return AQUA_UNUSED_HANDLE;

            return m_SoundResource->GetSoftSoundHandle();
        }

        /*!
         *  @brief      利用可能か調べる
         *
         *  @retval     true    利用可能
         *  @retval     false   利用不可能
         */
        bool        IsEnable(void) const
        {
            if (m_SoundResource)
                return m_SoundResource->IsEnable();

            return false;
        }

        /*!
         *  @brief      代入演算子のオーバーロード
         *
         *  @param[in]  sound   サウンドクラス
         */
        CSound&     operator=( const CSound& sound );

    private:
        //! サウンドリソースクラス
        core::CSoundResource*   m_SoundResource;
    };
}
