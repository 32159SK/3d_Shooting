
/*!
 *  @file       texture_manager.h
 *  @brief      テクスチャ管理クラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <list>
#include <string>

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
        class CTextureResource;

        /*!
         *  @class      CTextureManager
         *
         *  @brief      テクスチャ管理クラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CTextureManager
        {
        public:
            /*!
             *  @brief      インスタンスの取得
             *
             *  @return     インスタンスへの参照
             */
            static CTextureManager& GetInstance( void );

            /*!
             *  @brief      テクスチャの読み込み
             *
             *  @param[in]  file_name   ファイル名
             *
             *  @return     テクスチャリソースクラス
             */
            CTextureResource*       Load( const std::string& file_name );

            /*!
             *  @brief      テクスチャの解放
             *
             *  @param[in]  texture     テクスチャリソースクラス
             */
            void                    Unload( CTextureResource* texture );

            /*!
             *  @brief      テクスチャの生成
             *
             *  @param[in]  width           横幅
             *  @param[in]  height          縦幅
             *  @param[in]  alpha_channel   アルファチャンネル
             */
            CTextureResource*       Create( int width, int height, bool alpha_channel );

            /*!
             *  @brief      テクスチャの解放
             */
            void                    Delete( CTextureResource* texture );

            /*!
             *  @brief      テクスチャの検索
             *
             *  @param[in]  file_name   ファイル名
             *
             *  @return     テクスチャリソースクラス
             */
            CTextureResource*       Find( const std::string& file_name );

            /*!
             *  @brief      テクスチャリストのクリア
             */
            void                    Clear( void );

        private:
            /*!
             *  @brief      コンストラクタ
             */
            CTextureManager( void );

            /*!
             *  @brief      コピーコンストラクタ
             *
             *  @param[in]  rhs コピーオブジェクト
             */
            CTextureManager( const CTextureManager& rhs );

            /*!
             *  @brief      デストラクタ
             */
            ~CTextureManager( void ) = default;

            /*!
             *  @brief      代入演算子
             *
             *  @param[in]  rhs 代入オブジェクト
             *
             *  @return     自身のオブジェクト
             */
            CTextureManager&    operator=( const CTextureManager& rhs );

            /*!
             *  @brief      テクスチャリソースリスト
             */
            typedef std::list<CTextureResource*> TEXTURE_LIST;

            //! テクスチャリソースリスト
            TEXTURE_LIST    m_TextureList;
        };
    }
}
