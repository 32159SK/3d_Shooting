
/*!
 *  @file       flag.h
 *  @brief      フラグ管理
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
     *  @class      CFlag
     *
     *  @brief      フラグクラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CFlag
    {
    public:
        /*!
         *  @brief      コンストラクタ
         */
        CFlag(void) : m_Flag(0) { }

        /*!
         *  @brief      デストラクタ
         */
        ~CFlag( void ) = default;

        /*!
         *  @brief      フラグの取得
         *
         *  @return     フラグ
         */
        unsigned int    GetFlag(void) const { return m_Flag; }

        /*!
         *  @brief      フラグの設定
         *
         *  @param[in]  flag    設定するフラグ
         */
        void            SetFlag(unsigned int flag) { m_Flag = flag; }

        /*!
         *  @brief      フラグ追加
         *
         *  @param[in]  flag    追加するフラグ
         */
        void            Add(unsigned int flag) { m_Flag |= flag; }

        /*!
         *  @brief      フラグ削除
         *
         *  @param[in]  flag    削除するフラグ
         */
        void            Del(unsigned int flag) { m_Flag &= ~flag; }

        /*!
         *  @brief      フラグのクリア
         */
        void            Clear(void) { m_Flag = 0; }

        /*!
         *  @brief      フラグの比較
         *
         *  @param[in]  flag    比較フラグ
         *
         *  @return     フラグとの比較結果
         *  @retval     true    フラグが立っている
         *  @retval     false   フラグが立っていない
         */
        bool            IsFlag(unsigned int flag) { return (m_Flag & flag); }

    private:
        //! フラグ
        unsigned int    m_Flag;
    };
}
