
/*!
 *  @file       timer.h
 *  @brief      タイマークラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

/*!
 *  @brief  aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CTimer
     *
     *  @brief      タイマークラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CTimer
    {
    public:
        /*!
         *  @brief      コンストラクタ
         */
        CTimer( void );

        /*!
         *  @brief      デストラクタ
         */
        ~CTimer( void ) = default;

        /*!
         *  @brief      初期化
         *
         *  @param[in]  limit   計測時間(秒)
         */
        void    Setup( float limit );

        /*!
         *  @brief      初期化
         *
         *  @param[in]  limit   計測時間(秒)
         *  @param[in]  scale   タイムスケール(1.0fが等速)
         */
        void    Setup( float limit, float scale );

        /*!
         *  @brief      更新
         */
        void    Update( void );

        /*!
         *  @brief      リセット
         */
        void    Reset( void );

        /*!
         *  @brief      終了判定
         *
         *  @return     指定した時間を経過した
         *  @retval     true    経過した
         *  @retval     false   経過していない
         */
        bool    Finished( void ) const;

        /*!
         *  @brief      現在の経過時間を取得
         *
         *  @return     現在の経過時間
         */
        float   GetTime( void ) const;

        /*!
         *  @brief      指定した限界時間を取得
         *
         *  @return     指定した限界時間時間
         */
        float   GetLimit( void ) const;

        /*!
         *  @brief      時間を設定
         *
         *  @param[in]  time   時間(秒)
         */
        void    SetTime(float time);

        /*!
         *  @brief      計測時間を設定
         *
         *  @param[in]  limit   計測時間(秒)
         */
        void    SetLimit( float limit );

        /*!
         *  @brief      タイムスケールを取得
         *
         *  @return     タイムスケール
         */
        float   GetTimeScale( void ) const;

        /*!
         *  @brief      タイムスケールを設定
         *
         *  @param[in]  scale   タイムスケール(1.0fが等速)
         */
        void    SetTimeScale( float scale );

    private:
        //! 初期タイムスケール
        static const float  m_default_time_scale;
        //! 現在の時間
        float               m_CurrentTime;
        //! 設定時間
        float               m_LimitTime;
        //! タイムスケール
        float               m_TimeScale;
    };
}
