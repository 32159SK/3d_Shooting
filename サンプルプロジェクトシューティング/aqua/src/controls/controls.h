
/*!
 *  @file       controls.h
 *  @brief      入力判定
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "keyboard\keyboard.h"
#include "mouse\mouse.h"
#include "controller\controller.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @brief      aqua::keyboard名前空間
     */
    namespace keyboard
    {
        /*!
         *  @brief      入力判定
         *              連続した入力判定
         *
         *  @param[in]  key     キーID
         *
         *  @return     入力状態
         *  @retval     true    入力されている
         *  @retval     false   入力されていない
         */
        bool            Button( aqua::keyboard::KEY_ID key );

        /*!
         *  @brief      入力判定
         *              押した瞬間を判定
         *
         *  @param[in]  key     キーID
         *
         *  @return     入力状態
         *  @retval     true    押された
         *  @retval     false   押されていないか、押し続けている
         */
        bool            Trigger( aqua::keyboard::KEY_ID key );

        /*!
         *  @brief      入力判定
         *              離された瞬間を判定
         *
         *  @param[in]  key     キーID
         *
         *  @return     入力状態
         *  @retval     true    離された
         *  @retval     false   離されていない
         */
        bool            Released( aqua::keyboard::KEY_ID key );
    }

    /*!
     *  @brief      aqua::mouse名前空間
     */
    namespace mouse
    {
        /*!
         *  @brief      マウス座標取得
         *
         *  @return     マウス座標
         */
        aqua::CPoint    GetCursorPos(void);

        /*!
         *  @brief      マウスの移動量取得
         *
         *  @return     マウスの移動量
         */
        aqua::CPoint    GetCursorMovement(void);

        /*!
         *  @brief      マウスボタン判定
         *              連続した入力判定
         *
         *  @param[in]  button  マウスボタンID
         *
         *  @return     入力状態
         *  @retval     true    入力されている
         *  @retval     false   入力されていない
         */
        bool            Button(aqua::mouse::BUTTON_ID button);

        /*!
         *  @brief      マウスボタン判定
         *              押された瞬間を判定
         *
         *  @param[in]  button  マウスボタンID
         *
         *  @return     入力状態
         *  @retval     true    押された
         *  @retval     false   押されていないか、押し続けている
         */
        bool            Trigger(aqua::mouse::BUTTON_ID button);

        /*!
         *  @brief      マウスボタン判定
         *              離された瞬間を判定
         *
         *  @param[in]  button  マウスボタンID
         *
         *  @return     入力状態
         *  @retval     true    離された
         *  @retval     false   離されていない
         */
        bool            Released(aqua::mouse::BUTTON_ID button);

        /*!
         *  @brief      ホイール値取得
         *
         *  @return     ホール値取得
         *  @retval     正の数     奥にホイールされた
         *  @retval     負の数     手前にホイールされた
         */
        int             GetWheel(void);
    }

    /*!
     *  @brief      aqua::controller名前空間
     */
    namespace controller
    {
        /*!
         *  @brief      入力判定
         *              連続した入力判定
         *
         *  @param[in]  device  デバイスID
         *  @param[in]  button  ボタンID
         *
         *  @return     入力状態
         *  @retval     true    入力されている
         *  @retval     false   入力されていない
         */
        bool            Button( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button );

        /*!
         *  @brief      入力判定
         *              押した瞬間を判定
         *
         *  @param[in]  device  デバイスID
         *  @param[in]  button  ボタンID
         *
         *  @return     入力状態
         *  @retval     true    押された
         *  @retval     false   押されていないか、押し続けている
         */
        bool            Trigger( aqua::controller::DEVICE_ID device, aqua::controller::BUTTON_ID button );

        /*!
         *  @brief      入力判定
         *              離された瞬間を判定
         *
         *  @param[in]  device  デバイスID
         *  @param[in]  button  ボタンID
         *
         *  @return     入力状態
         *  @retval     true    離された
         *  @retval     false   離されていない
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
         *  @param[in]  device  デバイスID
         *
         *  @return     左アナログスティックの状態
         */
        aqua::CVector2  GetAnalogStickLeft( aqua::controller::DEVICE_ID device );

        /*!
         *  @brief      右アナログスティック取得
         *
         *  @param[in]  device  デバイスID
         *
         *  @return     右アナログスティックの状態
         */
        aqua::CVector2  GetAnalogStickRight( aqua::controller::DEVICE_ID device );

        /*!
         *  @brief      左トリガー取得
         *
         *  @param[in]  device      デバイスID
         *
         *  @return     左トリガーの状態
         */
        float           GetTriggerLeft( aqua::controller::DEVICE_ID device );

        /*!
         *  @brief      右トリガー取得
         *
         *  @param[in]  device      デバイスID
         *
         *  @return     右トリガーの状態
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
         *  @brief      接続台数取得
         *
         *  @return     接続台数
         */
        int             GetConnectCount( void );
    }
}
