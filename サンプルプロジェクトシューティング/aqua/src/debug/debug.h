
/*!
 *  @file       debug.h
 *  @brief      デバッグ
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>
#include <string>
#include <list>

#ifdef  _DEBUG
/*!
 *  @brief  デバッグ実行時マクロ<br>
 *          このマクロが有効な時、Debug用プロセスでプログラムを実行します。
 */
#define AQUA_DEBUG

#else
/*!
 *  @brief  リリリース実行時マクロ<br>
 *          このマクロが有効な時、Release用プロセスでプログラムを実行します。
 */
#define AQUA_RELEASE

#endif

/*!
 *  @brief      DXLibエラー値
 */
#define AQUA_DX_ERROR   ( -1 )


#ifdef  AQUA_DEBUG

/*!
 *  @brief      アサート処理
 *              ゲーム画面出力用
 *
 *  @param[in]  x       条件式
 *  @param[in]  message エラーメッセージ
 */
#define AQUA_ASSERT( x, message )       aqua::core::CVisualDebugger::GetInstance( ).VisualAssert( ( x ), ( message ), __FILE__, __LINE__ )

/*!
 *  @brief      アサート処理
 *              ゲーム画面出力用
 *
 *  @param[in]  x       条件式
 *  @param[in]  message エラーメッセージ
 */
#define AQUA_DX_ASSERT( x, message )    aqua::core::CVisualDebugger::GetInstance( ).VisualAssert( ( x ) != AQUA_DX_ERROR, ( message ), __FILE__, __LINE__ )

/*!
 *  @brief      デバッグログの表示
 *              ゲーム画面出力・ファイルへの書き出し
 *
 *  @param[in]  text    メッセージ
 */
#define AQUA_DEBUG_LOG( text )          aqua::core::CVisualDebugger::GetInstance( ).DebugLog( ( text ) )

#else

#define AQUA_ASSERT( x, type )
#define AQUA_DX_ASSERT( x, type )
#define AQUA_DEBUG_LOG( text )

#endif

#ifdef AQUA_DEBUG

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
        *  @class      CVisualDebugger
        *
        *  @brief      ビジュアルデバッガークラス
        *
        *  @author     Kazuya Maruyama
        *
        *  @date       2021/03/10
        *
        *  @version    7.17
        */
        class CVisualDebugger
        {
        public:
            /*!
             *  @brief      インスタンスの取得
             *
             *  @return     インスタンスへの参照
             */
            static CVisualDebugger&  GetInstance( void );

            /*!
             *  @brief      初期化
             */
            void    Initialize( void );

            /*!
             *  @brief      更新
             */
            void    Update( void );

            /*!
             *  @brief      描画
             */
            void    Draw( void );

            /*!
             *  @brief      解放
             */
            void    Finalize( void );

            /*!
             *  @brief      アサート処理
             *              ゲーム画面出力用
             *
             *  @param[in]  result      条件や結果を渡す。falseになるとアサートが発生する
             *  @param[in]  message     エラーメッセージ
             *  @param[in]  file        ファイル名
             *  @param[in]  line        行番号
             */
            void    VisualAssert( bool result, const std::string& message, const std::string& file, int line );

            /*!
             *  @brief      デバッグログの表示
             *              ゲーム画面出力用
             *
             *  @param[in]  text         テキスト
             */
            void    DebugLog( const std::string& text );

            /*!
             *  @brief      ポーズフラグ取得
             *
             *  @retval     true    ポーズ中
             *  @retval     false   ポーズ中でない
             */
            bool    GetDebugPauseFlag( void );

            /*!
             *  @brief      デバッグ用デルタタイムスケール取得
             *
             *  @return     デバッグ用デルタタイムスケール
             */
            float   GetDebugDeltaTimeScale( void ) const;

        private:
            /*!
             *  @brief      コンストラクタ
             */
            CVisualDebugger( void );

            /*!
             *  @brief      デストラクタ
             */
            ~CVisualDebugger( void ) = default;

            /*!
             *  @brief      コピーコンストラクタ
             *
             *  @param[in]  rhs コピーオブジェクト
             */
            CVisualDebugger( const CVisualDebugger& rhs );

            /*!
             *  @brief      代入演算子
             *
             *  @param[in]  rhs 代入オブジェクト
             *
             *  @return     自身のオブジェクト
             */
            CVisualDebugger&    operator=( const CVisualDebugger& rhs );

            /*!
             *  @brief  デバッグログ用リスト型
             */
            typedef std::list<std::string> DEBUG_LOG_LIST;

            //! 背景色
            static const unsigned int   m_background_color;
            //! 文字色
            static const unsigned int   m_message_color;
            //! デバッグログファイル名
            static const char*          m_debug_log_file_name;
            //! デバッグログを表示する数
            static const int            m_max_show_debug_log;
            //! デバッグフォントの色
            static const unsigned int   m_debug_text_color;
            //! デバッグフォントの枠の色
            static const unsigned int   m_debug_text_edge_color;
            //! デバッグコマンド数
            static const int            m_max_debug_command;
            //! デバッグコマンド表示位置
            static const int            m_debug_command_width;
            //! デバッグコマンド名
            static const char*          m_debug_command_names[];
            //! 初期のデルタタイムスケール
            static const float          m_default_delta_time_scale;
            //! 最小のデルタタイムスケール
            static const float          m_min_delta_time_scale;
            //! 最大のデルタタイムスケール
            static const float          m_max_delta_time_scale;
            //! デルタタイムスケールの変更値
            static const float          m_change_delta_time_scale;
            //! デルタタイムスケール入力間隔
            static const int            m_delta_time_scale_input_interval;
            //! FPSの表示フラグ
            bool                        m_ShowDebugFPS;
            //! デバッグヘルプ表示フラグ
            bool                        m_ShowDebugHelp;
            //! デバッグログ表示フラグ
            bool                        m_ShowDebugLog;
            //! デバッグ用ポーズフラグ
            bool                        m_DebugPauseFlag;
            //! デバッグ用デルタタイム倍率
            float                       m_DebugDeltaTimeScale;
            //! デバッグログリスト
            DEBUG_LOG_LIST              m_DebugLogList;
            //! デバッグログ書き出し用ファイル
            FILE*                       m_DebugLogFile;
            //! デルタタイムスケール入力時間
            int                         m_DeltaTimeScaleInputTime;
        };
    }
}

#endif
