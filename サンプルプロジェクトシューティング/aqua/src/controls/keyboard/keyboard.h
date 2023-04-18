
/*!
 *  @file       keyboard.h
 *  @brief      キーボード入力管理
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DXLib.h>

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
         *  @brief      キーID<br>
         *              キーボード判定で使用可能なキーID
         */
        enum class KEY_ID
        {
            //! Dummy
            DUMMY         = 0x00,
            //! Escape
            ESCAPE        = 0x01,
            //! 1
            ONE           = 0x02,
            //! 2
            TWO           = 0x03,
            //! 3
            THREE         = 0x04,
            //! 4
            FOUR          = 0x05,
            //! 5
            FIVE          = 0x06,
            //! 6
            SIX           = 0x07,
            //! 7
            SEVEN         = 0x08,
            //! 8
            EIGHT         = 0x09,
            //! 9
            NINE          = 0x0A,
            //! 0
            ZERO          = 0x0B,
            //MINUS         = 0x0C, // -
            //EQUALS        = 0x0D, // =
            //! BackSpace
            BACK          = 0x0E,
            //! Tab
            TAB           = 0x0F,
            //! Q
            Q             = 0x10,
            //! W
            W             = 0x11,
            //! E
            E             = 0x12,
            //! R
            R             = 0x13,
            //! T
            T             = 0x14,
            //! Y
            Y             = 0x15,
            //! U
            U             = 0x16,
            //! I
            I             = 0x17,
            //! O
            O             = 0x18,
            //! P
            P             = 0x19,
            //LBRACKET      = 0x1A, // [
            //RBRACKET      = 0x1B, // ]
            //! Enter
            RETURN        = 0x1C,
            //! Ctrl(左側)
            LCONTROL      = 0x1D,
            //! A
            A             = 0x1E,
            //! S
            S             = 0x1F,
            //! D
            D             = 0x20,
            //! F
            F             = 0x21,
            //! G
            G             = 0x22,
            //! H
            H             = 0x23,
            //! J
            J             = 0x24,
            //! K
            K             = 0x25,
            //! L
            L             = 0x26,
            //SEMICOLON     = 0x27, // ;(セミコロン)
            //APOSTROPHE    = 0x28, // '(シングルクォーテーション)
            //GRAVE         = 0x29, // `
            //! Shift(左側)
            LSHIFT        = 0x2A,
            //! '\'(バックスラッシュまたは円マーク)
            BACKSLASH     = 0x2B,
            //! Z
            Z             = 0x2C,
            //! X
            X             = 0x2D,
            //! C
            C             = 0x2E,
            //! V
            V             = 0x2F,
            //! B
            B             = 0x30,
            //! N
            N             = 0x31,
            //! M
            M             = 0x32,
            //COMMA         = 0x33, // ,(カンマ)
            //PERILD        = 0x34, // .(ピリオド)
            //SLASH         = 0x35, // '/'(スラッシュ)
            //RSHIFT        = 0x36, // シフト(右側)
            //MULTIPLY      = 0x37, // *(NumPad)
            //LMENU         = 0x38, // Alt(左側)
            //! Space
            SPACE         = 0x39,
            //CAPIRAL       = 0x3A, // CapsLock
            //! F1
            F1            = 0x3B,
            //! F2
            F2            = 0x3C,
            //! F3
            F3            = 0x3D,
            //! F4
            F4            = 0x3E,
            //! F5
            F5            = 0x3F,
            //! F6
            F6            = 0x40,
            //! F7
            F7            = 0x41,
            //! F8
            F8            = 0x42,
            //! F9
            F9            = 0x43,
            //! F10
            F10           = 0x44,
            //NUMLOCK       = 0x45, // NumLock
            //SCROLL        = 0x46, // ScrollLock
            //! 7(NumPad)
            NUMPAD7       = 0x47,
            //! 8(NumPad)
            NUMPAD8       = 0x48,
            //! 9(NumPad)
            NUMPAD9       = 0x49,
            //! -(NumPad)
            SUBTRACT      = 0x4A,
            //! 4(NumPad)
            NUMPAD4       = 0x4B,
            //! 5(NumPad)
            NUMPAD5       = 0x4C,
            //! 6(NumPad)
            NUMPAD6       = 0x4D,
            //! +(NumPad)
            ADD           = 0x4E,
            //! 1(NumPad)
            NUMPAD1       = 0x4F,
            //! 2(NumPad)
            NUMPAD2       = 0x50,
            //! 3(NumPad)
            NUMPAD3       = 0x51,
            //! 0(NumPad)
            NUMPAD0       = 0x52,
            //! .(NumPad)
            NUMPADDECIMAL = 0x53,
            //! F11
            F11           = 0x57,
            //! F12
            F12           = 0x58,
            //F13           = 0x64,// F13
            //F14           = 0x65,// F14
            //F15           = 0x66,// F15
            //KANA          = 0x70, // カナ
            //CONVERT       = 0x79, // 変換
            //NOCONVERT     = 0x7B, // 無変換
            //YEN           = 0x7D, // '\'
            //NUMPADEQUALS  = 0x8D, // =(NumPad)
            //CIRCUMFLEX    = 0x90, // ^(ハット)
            //AT            = 0x91, // @(アットマーク)
            //COLON         = 0x92, // :(コロン)
            //UNDERLINE     = 0x93, // _(アンダーライン)
            //KANJI         = 0x94, // 漢字
            //STOP          = 0x95, // Stop
            //AX            = 0x96, // JapanAX
            //UNLABELED     = 0x97, // J3100
            //! Enter(NumPad)
            NUMPADENTER   = 0x9C,
            //! Ctrl(右側)
            RCONTROL      = 0x9D,
            //NUMPADCOMMA   = 0xB3, // ,(NumPad)
            //DIVIDE        = 0xB5, // /(NumPad)
            //SYSRQ         = 0xB7, // SysRq
            //RMENU         = 0xB8, // Alt(右側)
            //PAUSE         = 0xC5, // Pause
            //HOME          = 0xC7, // Home
            //! ↑
            UP            = 0xC8,
            //PRIOR         = 0xC9, // PageUp
            //! ←
            LEFT          = 0xCB,
            //! →
            RIGHT         = 0xCD,
            //END           = 0xCF, // End
            //! ↓
            DOWN          = 0xD0,
            //NEXT          = 0xD1, // PageDown
            //INSERT        = 0xD2, // Insert
            //DELETE        = 0xD3, // Delete
            //LWIN          = 0xDB, // Windows
            //RWIN          = 0xDC, // Windows
            //APPS          = 0xDD, // Menu
            //POWER         = 0xDE, // Power
            //SLEEP         = 0xDE, // Windows
        };
    }

    /*!
     *  @brief      aqua::core名前空間
     */
    namespace core
    {
        /*!
         *  @class      CKeyboard
         *
         *  @brief      キーボード入力管理クラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CKeyboard
        {
        public:
            /*!
             *  @brief      インスタンスの取得
             *
             *  @return     インスタンスへの参照
             */
            static CKeyboard&   GetInstance( void );

            /*!
             *  @brief      初期化
             */
            void    Initialize( void );

            /*!
             *  @brief      入力情報更新
             */
            void    Update( void );

            /*!
             *  @brief      解放
             *              キーボードデバイスを解放する。
             */
            void    Finalize( void );

            /*!
             *  @brief      ボタン判定
             *
             *  @param[in]  key     キーID
             *
             *  @return     入力状態
             *  @retval     true    押されている
             *  @retval     false   押されていない
             */
            bool            Button( aqua::keyboard::KEY_ID key );

            /*!
             *  @brief      トリガー判定
             *
             *  @param[in]  key     キーID
             *
             *  @return     入力状態
             *  @retval     true    押された瞬間
             *  @retval     false   押されていないか、押され続けている
             */
            bool            Trigger( aqua::keyboard::KEY_ID key );

            /*!
             *  @brief      リリース判定
             *
             *  @param[in]  key     キーID
             *
             *  @return     入力状態
             *  @retval     true    離された瞬間
             *  @retval     false   押されていないか、押され続けている
             */
            bool            Released( aqua::keyboard::KEY_ID key );

        private:
            /*!
             *  @brief      コンストラクタ
             */
            CKeyboard( void );

            /*!
             *  @brief      コピーコンストラクタ
             *
             *  @param[in]  rhs コピーオブジェクト
             */
            CKeyboard( const CKeyboard& rhs );

            /*!
             *  @brief      デストラクタ
             */
            ~CKeyboard( void ) = default;

            /*!
             *  @brief      代入演算子
             *
             *  @param[in]  rhs 代入オブジェクト
             *
             *  @return     自身のオブジェクト
             */
            CKeyboard& operator=( const CKeyboard& rhs );

            //! キーの最大数
            static const unsigned int   m_max_input_key;
            //! キーボードの状態
            char*                       m_KeyState;
            //! 1フレーム前のキーボードの状態
            char*                       m_PrevKeyState;
        };
    }
}
