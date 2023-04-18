
/*!
 *  @file       framework.h
 *  @brief      フレームワーク
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <windows.h>
#include <string>
#include "..\debug\debug.h"
#include "..\game_object\game_object.h"

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
         *  @brief  ウィンドウプロシージャ登録用関数ポインタ
         */
        typedef int (*WINDOW_PROC)( HWND hWnd, unsigned int msg, unsigned int wParam, unsigned int lParam );

        /*!
         *  @class      CFramework
         *
         *  @brief      ゲームフレームワーククラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         *
         *  @note       シングルトンパターン
         */
        class CFramework
        {
        public:
            /*!
             *  @brief      インスタンスの取得
             *
             *  @return     インスタンスへの参照
             */
            static CFramework&  GetInstance( void );

            /*!
             *  @brief      初期化
             *
             *  @param[in]  instance_handle     インスタンスハンドル
             *  @param[in]  game                ゲームクラス
             */
            void                Initialize( HINSTANCE instance_handle, IGameObject* game );

            /*!
             *  @brief      更新
             */
            void                Update( void );

            /*!
             *  @brief      解放
             */
            void                Finalize( void );

            /*!
             *  @brief      リセット
             */
            void                Reset( void );

            /*!
             *  @brief      インスタンスハンドルの取得
             *
             *  @return     インスタンスハンドル
             */
            HINSTANCE           GetInstanceHandle(void) const { return m_hInstance; }

            /*!
             *  @brief      ウィンドウハンドルの取得
             *
             *  @return     ウィンドウハンドル
             */
            HWND                GetWindowHandle(void) const { return m_hWindow; }

            /*!
             *  @brief      ウィンドウの横幅取得
             *
             *  @return     ウィンドウの横幅
             */
            unsigned int        GetWindowWidth(void) const { return m_width; }

            /*!
             *  @brief      ウィンドウの縦幅取得
             *
             *  @return     ウィンドウの縦幅
             */
            unsigned int        GetWindowHeight(void) const { return m_height; }

            /*!
             *  @brief      デルタタイム取得
             *              デルタタイムは前回の更新からどれくらいの時間が経過したかの値
             *
             *  @return     デルタタイム
             */
            float               GetDeltaTime(void) const;

            /*!
             *  @brief      デルタタイム(タイムスケールなし)取得
             *              デルタタイムは前回の更新からどれくらいの時間が経過したかの値
             *
             *  @return     デルタタイム
             */
            float               GetUnscaledDeltaTime(void) const { return m_DeltaTime; }

            /*!
             *  @brief      デルタタイム倍率取得
             *
             *  @return     デルタタイム倍率
             */
            float               GetDeltaTimeScale(void) const;

            /*!
             *  @brief      デルタタイム倍率設定
             *
             *  @param[in]  scale   デルタタイム倍率
             */
            void                SetDeltaTimeScale(float scale) { m_DeltaTimeScale = scale; }

            /*!
             *  @brief      現在のFPS取得
             *
             *  @return     現在のFPS
             */
            float               GetFPS(void) const { return m_Fps; }

            /*!
             *  @brief      フレームレートの設定
             *
             *  @param[int] frame_rate  フレームレート
             */
            void                SetFrameRate(int frame_rate) { m_FrameRate = frame_rate; }

            /*!
             *  @brief      ゲームオブジェクトの検索
             *
             *  @param[in]  name    オブジェクト名
             *
             *  @return     検索オブジェクト<br>
             *              見つからなかった場合はnullptr
             */
            IGameObject*        FindGameObject( const std::string& name );

            /*!
             *  @brief      ゲームオブジェクトの検索
             *
             *  @param[in]  func    検索条件メソッド
             *
             *  @return     検索オブジェクト<br>
             *              見つからなかった場合はnullptr
             */
            IGameObject*        FindGameObject( aqua::FIND_METHOD func );

        private:
            /*!
             *  @brief      コンストラクタ
             */
            CFramework( void );

            /*!
             *  @brief      コピーコンストラクタ
             *
             *  @param[in]  rhs コピーオブジェクト
             */
            CFramework( const CFramework& rhs );

            /*!
             *  @brief      デストラクタ
             */
            ~CFramework( void ) = default;

            /*!
             *  @brief      代入演算子
             *
             *  @param[in]  rhs 代入オブジェクト
             *
             *  @return     自身のオブジェクト
             */
            CFramework&         operator=( const CFramework& rhs );

            /*!
             *  @brief      更新するフレームカウントの計算
             */
            void                CalcFrameCount( void );

            /*!
             *  @brief      更新フレームの同期
             */
            void                FrameSync( void );

            /*!
             *  @brief      ゲームプロセス
             */
            void                GameProcess( void );

            /*!
             *  @brief      スクリーンショットの撮影
             */
            void                ScreenShot( void );

            //! クラスネーム
            static const char*          m_class_name;
            //! 標準ウインドウの横幅
            static const unsigned int   m_width;
            //! 標準ウインドウの縦幅
            static const unsigned int   m_height;
            //! カラービット
            static const int            m_color_bit;
            //! 1ミリ秒
            static const float          m_one_millisecond;
            //! 最大デルタタイム
            static const float          m_max_delta_time;
            //! 初期のデルタタイムスケール
            static const float          m_default_delta_time_scale;
            //! デフォルトのフレームレート
            static const int            m_default_frame_rate;
            //! 平均を計算するフレームの数
            static const int            m_calc_frame_count;
            //! Effekseerで使用するパーティクルの最大数
            static const int            m_max_effekseer_particle;
            //! インスタンスハンドル
            HINSTANCE                   m_hInstance;
            //! ウィンドウハンドル
            HWND                        m_hWindow;
            //! ウィンドウモード切替フラグ
            bool                        m_WindowMode;
            //! ゲームオブジェクトルートノード
            IGameObject*                m_GameNode;
            //! フレームレート
            int                         m_FrameRate;
            //! 現在のFPS
            float                       m_Fps;
            //! フレームカウント
            int                         m_FrameCount;
            //! フレーム計測開始時間
            int                         m_StartTime;
            //! 1フレーム前の時間
            int                         m_PrevTime;
            //! ゲーム更新用デルタタイム
            float                       m_DeltaTime;
            //! デルタタイム倍率
            float                       m_DeltaTimeScale;
        };
    }
}
