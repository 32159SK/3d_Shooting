
/*!
 *  @file       font.h
 *  @brief      フォントクラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "font_resource\font_resource.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CFont
     *
     *  @brief      フォントクラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CFont
    {
    public:
        /*!
         *  @brief      コンストラクタ
         */
        CFont( void );

        /*!
         *  @brief      コピーコンストラクタ
         *
         *  @param[in]  font    フォントクラス
         */
        CFont( const CFont& font );

        /*!
         *  @brief      デストラクタ
         */
        ~CFont( void ) = default;

        /*!
         *  @brief      フォントの読み込み
         *
         *  @param[in]  size        フォントサイズ
         *  @param[in]  edge_bold   エッジの太さ
         *  @param[in]  famiry_id   フォント名ID
         */
        void                Create( int size, int edge_bold, bool anti_aliasing, aqua::FONT_FAMILY_ID family_id );

        /*!
         *  @brief      フォントの解放
         */
        void                Delete( void );

        /*!
         *  @brief      フォントのリソースハンドル取得
         *
         *  @return     フォントのリソースハンドル
         */
        int                 GetResourceHandle(void) const
        {
            if (!m_FontResource) return AQUA_UNUSED_HANDLE;

            return m_FontResource->GetResourceHandle();
        }

        /*!
         *  @brief      フォントの高さ取得
         *
         *  @return     フォントの高さ
         */
        int                 GetHeight(void) const
        {
            if (!m_FontResource) return AQUA_UNUSED_HANDLE;

            return m_FontResource->GetHeight();
        }

        /*!
         *  @brief      フォントの生成チェック
         *
         *  @retval     true    生成済み
         *  @retval     false   生成されていない
         */
        bool                IsEnable(void) const
        {
            if (!m_FontResource) return false;

            return m_FontResource->IsEnable();
        }

        /*!
         *  @brief      代入演算子のオーバーロード
         *
         *  @param[in]  mesh     フォントクラス
         */
        CFont&              operator=( const aqua::CFont& font );

    private:
        //! フォントリソースクラス
        core::CFontResource*       m_FontResource;
    };
}
