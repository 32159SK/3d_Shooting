
/*!
 *  @file       video_manager.h
 *  @brief      ビデオ管理クラス
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
        class CVideoResource;

        /*!
         *  @class      CVideoManager
         *
         *  @brief      ビデオ管理クラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CVideoManager
        {
        public:
            /*!
             *  @brief      インスタンスの取得
             *
             *  @return     インスタンスへの参照
             */
            static CVideoManager&   GetInstance( void );

            /*!
             *  @brief      ビデオの読み込み
             *
             *  @param[in]  file_name   ファイル名
             *
             *  @return     ビデオリソースクラス
             */
            CVideoResource*         Load( const std::string& file_name );

            /*!
             *  @brief      ビデオの解放
             *
             *  @param[in]  sound   テクスチャリソースクラス
             */
            void                    Unload( CVideoResource* video );

            /*!
             *  @brief      ビデオの検索
             *
             *  @param[in]  file_name   ファイル名
             *
             *  @return     ビデオリソースクラス
             */
            CVideoResource*         Find( const std::string& file_name );

            /*!
             *  @brief      ビデオリストのクリア
             */
            void                    Clear( void );

        private:
            /*!
             *  @brief      コンストラクタ
             */
            CVideoManager( void );

            /*!
             *  @brief      コピーコンストラクタ
             *
             *  @param[in]  rhs コピーオブジェクト
             */
            CVideoManager( const CVideoManager& rhs );

            /*!
             *  @brief      デストラクタ
             */
            ~CVideoManager( void ) = default;

            /*!
             *  @brief      代入演算子
             *
             *  @param[in]  rhs 代入オブジェクト
             *
             *  @return     自身のオブジェクト
             */
            CVideoManager&    operator=( const CVideoManager& rhs );

            /*!
             *  @brief      ビデオリソースリスト
             */
            typedef std::list<CVideoResource*>  VIDEO_RESOURCE_LIST;

            //! ビデオリソースリスト
            VIDEO_RESOURCE_LIST     m_VideoResourceList;
        };
    }
}
