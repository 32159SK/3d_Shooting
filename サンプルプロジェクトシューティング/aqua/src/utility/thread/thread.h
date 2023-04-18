
/*!
 *  @file       thread.h
 *  @brief      スレッド管理
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <windows.h>

/*!
 *  @brief  aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      IThread
     *
     *  @brief      スレッドベースクラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class IThread
    {
    public:
        /*!
         *  @brief      コンストラクタ
         */
        IThread( void );

        /*!
         *  @brief      デストラクタ
         */
        virtual ~IThread( void );

        /*!
         *  @brief      スレッドで行う処理の実行<br>
         *              必ずオーバーライドして実装
         */
        virtual void    Run( void ) = 0;

        /*!
         *  @brief      スレッド実行開始
         */
        virtual void    Start( void );

        /*!
         *  @brief      スレッド停止(強制停止)
         */
        virtual void    Stop( void );

        /*!
         *  @brief      スレッド停止と待機<br>
         *              スレッドが停止するまで待機する
         */
        virtual void    StopAndWait( void );

        /*!
         *  @brief      スレッドの起動チェック
         *
         *  @retval     true    起動している
         *  @retval     false   起動していない
         */
        virtual bool    IsRunning( void ) const;

        /*!
         *  @brief      スレッドの有効状態チェック
         *
         *  @retval     true    有効
         *  @retval     false   無効
         */
        virtual bool    IsValid( void ) const;

    protected:
        /*!
         *  @brief      一定時間スレッドを停止する
         *
         *  @param[in]  milliseconds    停止時間(ミリ秒)
         */
        virtual void    Sleep( unsigned int milliseconds );

        /*!
         *  @brief      スレッドコールバック関数
         */
        static unsigned int __stdcall ThreadCallback( void* p );

        //! スレッドハンドル
        HANDLE          m_ThreadHandle;
        //! イベントハンドル
        HANDLE          m_EventHandle;
        //! スレッド停止フラグ
        volatile bool   m_StopFlag;
    };
}
