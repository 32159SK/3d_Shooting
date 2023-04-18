
/*!
 *  @file       font_manager.h
 *  @brief      フォント管理クラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <list>
#include <string>
#include "..\font_resource\font_resource.h"

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
         *  @class      CFontManager
         *
         *  @brief      フォント管理クラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CFontManager
        {
        public:
            /*!
             *  @brief      インスタンスの取得
             *
             *  @return     インスタンスへの参照
             */
            static CFontManager&   GetInstance( void );

            /*!
             *  @brief      フォントの生成
             *
             *  @param[in]  size        サイズ
             *  @param[in]  edge_bold   エッジの太さ(0 = エッジなし)
             *  @param[in]  family_id   フォント名ID
             *
             *  @return     フォントリソースクラス
             */
            CFontResource*  Create(int size, int edge_bold, bool anti_aliasing, aqua::FONT_FAMILY_ID family_id);

            /*!
             *  @brief      フォントの解放
             *
             *  @param[in]  font    フォントリソースクラス
             */
            void            Delete( core::CFontResource* font );

            /*!
             *  @brief      フォントの検索
             *
             *  @param[in]  size_id     サイズID
             *  @param[in]  edge_bold   エッジの太さ(0 = エッジなし)
             *  @param[in]  family_id   フォント名ID
             *
             *  @return     フォントリソースクラス
             */
            CFontResource*  Find( int size, int edge_bold, aqua::FONT_FAMILY_ID family_id );

            /*!
             *  @brief      フォントリストのクリア
             */
            void            Clear( void );

        private:
            /*!
             *  @brief      コンストラクタ
             */
            CFontManager( void );

            /*!
             *  @brief      コピーコンストラクタ
             *
             *  @param[in]  rhs コピーオブジェクト
             */
            CFontManager( const CFontManager& rhs );

            /*!
             *  @brief      デストラクタ
             */
            ~CFontManager( void ) = default;

            /*!
             *  @brief      代入演算子
             *
             *  @param[in]  rhs 代入オブジェクト
             *
             *  @return     自身のオブジェクト
             */
            CFontManager&    operator=( const CFontManager& rhs );

            /*!
             *  @brief      フォントリソースリスト
             */
            typedef std::list<CFontResource*> FONT_LIST;

            //! フォントリソースリスト
            FONT_LIST      m_FontList;
        };
    }
}
