
/*!
 *  @file       controller.h
 *  @brief      XINPUT入力管理
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DXLib.h>
#include "..\..\utility\utility.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @brief      aqua::controller名前空間
     */
    namespace controller
    {
        /*!
         *  @brief      デバイスID
         */
        enum class DEVICE_ID
        {
            //! 1Pジョイパッド
            P1,
            //! 2Pジョイパッド
            P2,
            //! 3Pジョイパッド
            P3,
            //! 4Pジョイパッド
            P4,

            //! 最大デバイス数
            MAX
        };

        /*!
         *  @brief      ボタンID
         */
        enum class BUTTON_ID
        {
            //! ボタン上
            UP              = XINPUT_BUTTON_DPAD_UP,
            //! ボタン下
            DOWN            = XINPUT_BUTTON_DPAD_DOWN,
            //! ボタン左
            LEFT            = XINPUT_BUTTON_DPAD_LEFT,
            //! ボタン右
            RIGHT           = XINPUT_BUTTON_DPAD_RIGHT,
            //! STARTボタン
            START           = XINPUT_BUTTON_START,
            //! BACKボタン
            BACK            = XINPUT_BUTTON_BACK,
            //! 左スティック押し込み
            LEFT_THUMB      = XINPUT_BUTTON_LEFT_THUMB,
            //! 右スティック押し込み
            RIGHT_THUMB     = XINPUT_BUTTON_RIGHT_THUMB,
            //! LBボタン
            LEFT_SHOULDER   = XINPUT_BUTTON_LEFT_SHOULDER,
            //! RBボタン
            RIGHT_SHOULDER  = XINPUT_BUTTON_RIGHT_SHOULDER,
            //! Aボタン
            A               = XINPUT_BUTTON_A,
            //! Bボタン
            B               = XINPUT_BUTTON_B,
            //! Xボタン
            X               = XINPUT_BUTTON_X,
            //! Yボタン
            Y               = XINPUT_BUTTON_Y
        };

        /*!
         *  @brief      アナログスティック方向ID
         */
        enum class STICK_DIRECTION
        {
            //! 左方向
            LEFT,
            //! 右方向
            RIGHT,
            //! 上方向
            UP,
            //! 下方向
            DOWN
        };
    }

    /*!
     *  @brief      aqua::core名前空間
     */
    namespace core
    {
        /*!
         *  @class      CController
         *
         *  @brief      コントローラー(XINPUT)入力管理クラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CController
        {
        public:
            /*!
             *  @brief      インスタンスの取得
             *
             *  @return     インスタンスへの参照
             */
            static CController&    GetInstance( void );

            /*!
             *  @brief      初期化
             */
            void            Initialize( void );

            /*!
             *  @brief      入力情報更新
             */
            void            Update( void );

            /*!
             *  @brief      解放
             */
            void            Finalize( void );

            /*!
             *  @brief      ボタン判定
             *
             *  @param[in]  device      デバイスID
             *  @param[in]  button      ボタンID
             *
             *  @return     入力状態
             *  @retval     true    押されている
             *  @retval     false   押されていない
             */
            bool            Button( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button );

            /*!
             *  @brief      トリガー判定
             *
             *  @param[in]  device      デバイスID
             *  @param[in]  button      ボタンID
             *
             *  @return     入力状態
             *  @retval     true    押された瞬間
             *  @retval     false   押されていないか、押され続けている
             */
            bool            Trigger( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button );

            /*!
             *  @brief      リリース判定
             *
             *  @param[in]  device      デバイスID
             *  @param[in]  button      ボタンID
             *
             *  @return     入力状態
             *  @retval     true    離された瞬間
             *  @retval     false   押されていないか、押され続けている
             */
            bool            Released( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button );

            /*!
             *  @brief      トリガー判定
             *              左アナログスティック
             *
             *  @param[in]  device      デバイスID
             *  @param[in]  direction   方向ID
             *
             *  @return     入力状態
             *  @retval     true    押された瞬間
             *  @retval     false   押されていないか、押され続けている
             */
            bool            TriggerAnalogStickLeft( aqua::controller::DEVICE_ID device, aqua::controller::STICK_DIRECTION direction );

            /*!
             *  @brief      トリガー判定
             *              右アナログスティック
             *
             *  @param[in]  device      デバイスID
             *  @param[in]  direction   方向ID
             *
             *  @return     入力状態
             *  @retval     true    押された瞬間
             *  @retval     false   押されていないか、押され続けている
             */
            bool            TriggerAnalogStickRight( aqua::controller::DEVICE_ID device, aqua::controller::STICK_DIRECTION direction );

            /*!
             *  @brief      左アナログスティック取得
             *
             *  @param[in]  device      デバイスID
             *
             *  @return     左アナログスティックの状態(-1.0f～1.0f)
             */
            aqua::CVector2  GetAnalogStickLeft( aqua::controller::DEVICE_ID device );

            /*!
             *  @brief      右アナログスティック取得
             *
             *  @param[in]  device      デバイスID
             *
             *  @return     右アナログスティックの状態(-1.0f～1.0f)
             */
            aqua::CVector2  GetAnalogStickRight( aqua::controller::DEVICE_ID device );

            /*!
             *  @brief      左トリガー取得
             *
             *  @param[in]  device      デバイスID
             *
             *  @return     左トリガーの状態(0.0f～1.0f)
             */
            float           GetTriggerLeft( aqua::controller::DEVICE_ID device );

            /*!
             *  @brief      右トリガー取得
             *
             *  @param[in]  device      デバイスID
             *
             *  @return     右トリガーの状態(0.0f～1.0f)
             */
            float           GetTriggerRight( aqua::controller::DEVICE_ID device );

            /*!
             *  @brief      バイブレーションの開始
             *
             *  @param[in]  device      デバイスID
             *  @param[in]  power       振動の強さ(0～1000)
             *  @param[in]  time        振動する時間(秒単位)
             */
            void            StartVibration( aqua::controller::DEVICE_ID device, int power, float time );

            /*!
             *  @brief      接続数取得
             *
             *  @return     接続数
             */
            int             GetConnectCount( void );

        private:
            /*!
             *  @brief      コンストラクタ
             */
            CController( void );

            /*!
             *  @brief      コピーコンストラクタ
             *
             *  @param[in]  rhs コピーオブジェクト
             */
            CController( const CController& rhs );

            /*!
             *  @brief      デストラクタ
             */
            ~CController( void ) = default;

            /*!
             *  @brief      代入演算子
             *
             *  @param[in]  rhs 代入オブジェクト
             *
             *  @return     自身のオブジェクト
             */
            CController& operator=( const CController& rhs );

            //! ジョイパッドの最大接続数
            static const int    m_max_xcontroller_device;
            //! アナログスティック入力の限界値
            static const int    m_limit_cant_analog;
            //! トリガー入力の最大値
            static const int    m_max_trigger;
            //! アナログスティックの無効範囲
            static const int    m_analog_dead_zone;
            //! XINPUTの入力状態
            XINPUT_STATE*       m_XInputState;
            //! 1フレーム前の入力状態
            XINPUT_STATE*       m_PrevXInputState;
        };
    }
}
