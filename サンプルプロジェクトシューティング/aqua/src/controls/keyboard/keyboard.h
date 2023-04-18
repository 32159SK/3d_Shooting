
/*!
 *  @file       keyboard.h
 *  @brief      �L�[�{�[�h���͊Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DXLib.h>

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @brief      aqua::keyboard���O���
     */
    namespace keyboard
    {
        /*!
         *  @brief      �L�[ID<br>
         *              �L�[�{�[�h����Ŏg�p�\�ȃL�[ID
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
            //! Ctrl(����)
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
            //SEMICOLON     = 0x27, // ;(�Z�~�R����)
            //APOSTROPHE    = 0x28, // '(�V���O���N�H�[�e�[�V����)
            //GRAVE         = 0x29, // `
            //! Shift(����)
            LSHIFT        = 0x2A,
            //! '\'(�o�b�N�X���b�V���܂��͉~�}�[�N)
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
            //COMMA         = 0x33, // ,(�J���})
            //PERILD        = 0x34, // .(�s���I�h)
            //SLASH         = 0x35, // '/'(�X���b�V��)
            //RSHIFT        = 0x36, // �V�t�g(�E��)
            //MULTIPLY      = 0x37, // *(NumPad)
            //LMENU         = 0x38, // Alt(����)
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
            //KANA          = 0x70, // �J�i
            //CONVERT       = 0x79, // �ϊ�
            //NOCONVERT     = 0x7B, // ���ϊ�
            //YEN           = 0x7D, // '\'
            //NUMPADEQUALS  = 0x8D, // =(NumPad)
            //CIRCUMFLEX    = 0x90, // ^(�n�b�g)
            //AT            = 0x91, // @(�A�b�g�}�[�N)
            //COLON         = 0x92, // :(�R����)
            //UNDERLINE     = 0x93, // _(�A���_�[���C��)
            //KANJI         = 0x94, // ����
            //STOP          = 0x95, // Stop
            //AX            = 0x96, // JapanAX
            //UNLABELED     = 0x97, // J3100
            //! Enter(NumPad)
            NUMPADENTER   = 0x9C,
            //! Ctrl(�E��)
            RCONTROL      = 0x9D,
            //NUMPADCOMMA   = 0xB3, // ,(NumPad)
            //DIVIDE        = 0xB5, // /(NumPad)
            //SYSRQ         = 0xB7, // SysRq
            //RMENU         = 0xB8, // Alt(�E��)
            //PAUSE         = 0xC5, // Pause
            //HOME          = 0xC7, // Home
            //! ��
            UP            = 0xC8,
            //PRIOR         = 0xC9, // PageUp
            //! ��
            LEFT          = 0xCB,
            //! ��
            RIGHT         = 0xCD,
            //END           = 0xCF, // End
            //! ��
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
     *  @brief      aqua::core���O���
     */
    namespace core
    {
        /*!
         *  @class      CKeyboard
         *
         *  @brief      �L�[�{�[�h���͊Ǘ��N���X
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
             *  @brief      �C���X�^���X�̎擾
             *
             *  @return     �C���X�^���X�ւ̎Q��
             */
            static CKeyboard&   GetInstance( void );

            /*!
             *  @brief      ������
             */
            void    Initialize( void );

            /*!
             *  @brief      ���͏��X�V
             */
            void    Update( void );

            /*!
             *  @brief      ���
             *              �L�[�{�[�h�f�o�C�X���������B
             */
            void    Finalize( void );

            /*!
             *  @brief      �{�^������
             *
             *  @param[in]  key     �L�[ID
             *
             *  @return     ���͏��
             *  @retval     true    ������Ă���
             *  @retval     false   ������Ă��Ȃ�
             */
            bool            Button( aqua::keyboard::KEY_ID key );

            /*!
             *  @brief      �g���K�[����
             *
             *  @param[in]  key     �L�[ID
             *
             *  @return     ���͏��
             *  @retval     true    �����ꂽ�u��
             *  @retval     false   ������Ă��Ȃ����A�����ꑱ���Ă���
             */
            bool            Trigger( aqua::keyboard::KEY_ID key );

            /*!
             *  @brief      �����[�X����
             *
             *  @param[in]  key     �L�[ID
             *
             *  @return     ���͏��
             *  @retval     true    �����ꂽ�u��
             *  @retval     false   ������Ă��Ȃ����A�����ꑱ���Ă���
             */
            bool            Released( aqua::keyboard::KEY_ID key );

        private:
            /*!
             *  @brief      �R���X�g���N�^
             */
            CKeyboard( void );

            /*!
             *  @brief      �R�s�[�R���X�g���N�^
             *
             *  @param[in]  rhs �R�s�[�I�u�W�F�N�g
             */
            CKeyboard( const CKeyboard& rhs );

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CKeyboard( void ) = default;

            /*!
             *  @brief      ������Z�q
             *
             *  @param[in]  rhs ����I�u�W�F�N�g
             *
             *  @return     ���g�̃I�u�W�F�N�g
             */
            CKeyboard& operator=( const CKeyboard& rhs );

            //! �L�[�̍ő吔
            static const unsigned int   m_max_input_key;
            //! �L�[�{�[�h�̏��
            char*                       m_KeyState;
            //! 1�t���[���O�̃L�[�{�[�h�̏��
            char*                       m_PrevKeyState;
        };
    }
}
