
/*!
 *  @file       mouse.h
 *  @brief      マウス入力管理
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
     *  @brief      aqua::mouse名前空間
     */
    namespace mouse
    {
        /*!
         *  @brief      マウスボタンID<br>
         *              クリック判定で使用可能なボタンID
         */
        enum class BUTTON_ID
        {
            //! 左ボタン
            LEFT    = MOUSE_INPUT_LEFT,
            //! 右ボタン
            RIGHT   = MOUSE_INPUT_RIGHT,
            //! 中ボタン
            MIDDLE  = MOUSE_INPUT_MIDDLE
        };
    }

    /*!
     *  @brief      aqua::core名前空間
     */
    namespace core
    {
        /*!
         *  @class      CMouse
         *
         *  @brief      マウス入力管理クラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CMouse
        {
        public:
            /*!
             *  @brief      インスタンスの取得
             *
             *  @return     インスタンスへの参照
             */
            static CMouse&   GetInstance(void);

            /*!
             *  @brief      初期化
             */
            void    Initialize(void);

            /*!
             *  @brief      入力情報更新
             */
            void    Update(void);

            /*!
             *  @brief      ボタン判定
             *
             *  @param[in]  button  マウスボタンID
             *
             *  @return     入力状態
             *  @retval     true    押されている
             *  @retval     false   押されていない
             */
            bool            Button(aqua::mouse::BUTTON_ID button);

            /*!
             *  @brief      トリガー判定
             *
             *  @param[in]  button  マウスボタンID
             *
             *  @return     入力状態
             *  @retval     true    押された瞬間
             *  @retval     false   押されていないか、押され続けている
             */
            bool            Trigger(aqua::mouse::BUTTON_ID button);

            /*!
             *  @brief      リリース判定
             *
             *  @param[in]  button  マウスボタンID
             *
             *  @return     入力状態
             *  @retval     true    離された瞬間
             *  @retval     false   押されていないか、押され続けている
             */
            bool            Released(aqua::mouse::BUTTON_ID button);

            /*!
             *  @brief      マウスカーソルの位置取得
             *
             *  @return     マウスカーソルの位置
             */
            aqua::CPoint    GetCursorPos(void);

            /*!
             *  @brief      マウスカーソルの移動量取得
             *
             *  @return     マウスカーソルの移動量
             */
            aqua::CPoint    GetCursorMovement(void);

            /*!
             *  @brief      マウスホイール値取得
             *
             *  @return     ホイール値
             *  @retval     正の数     奥にホイールされた
             *  @retval     負の数     手前にホイールされた
             *  @retval     0          ホイールされていない
             */
            int             GetWheel(void);

        private:
            /*!
             *  @brief      コンストラクタ
             */
            CMouse(void);

            /*!
             *  @brief      コピーコンストラクタ
             *
             *  @param[in]  rhs コピーオブジェクト
             */
            CMouse(const CMouse& rhs);

            /*!
             *  @brief      デストラクタ
             */
            ~CMouse(void) = default;

            /*!
             *  @brief      代入演算子
             *
             *  @param[in]  rhs 代入オブジェクト
             *
             *  @return     自身のオブジェクト
             */
            CMouse& operator=(const CMouse& rhs);

            //! マウスの入力状態
            int         m_MouseState;
            //! 前のマウスの入力状態
            int         m_PrevMouseState;
            //! カーソル位置
            CPoint      m_CursorPos;
            //! 前のカーソル位置
            CPoint      m_PrevCursorPos;
        };
    }
}
