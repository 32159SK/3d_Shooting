
/*!
 *  @file       effekseer_manager.h
 *  @brief      Effekseer管理クラス
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
        class CEffekseerResource;

        /*!
         *  @class      CEffekseerManager
         *
         *  @brief      Effekseer管理クラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CEffekseerManager
        {
        public:
            /*!
             *  @brief      インスタンスの取得
             *
             *  @return     インスタンスへの参照
             */
            static CEffekseerManager& GetInstance( void );

            /*!
             *  @brief      Effekseerの読み込み
             *
             *  @param[in]  file_name   ファイル名
             *
             *  @return     Effekseerリソースクラス
             */
            CEffekseerResource*     Load( const std::string& file_name );

            /*!
             *  @brief      Effekseerの解放
             *
             *  @param[in]  effect     Effekseerリソースクラス
             */
            void                    Unload( CEffekseerResource* effect );

            /*!
             *  @brief      Effekseerの検索
             *
             *  @param[in]  file_name   ファイル名
             *
             *  @return     Effekseerリソースクラス
             */
            CEffekseerResource*     Find( const std::string& file_name );

            /*!
             *  @brief      Effekseerリストのクリア
             */
            void                    Clear( void );

        private:
            /*!
             *  @brief      コンストラクタ
             */
            CEffekseerManager( void );

            /*!
             *  @brief      コピーコンストラクタ
             *
             *  @param[in]  rhs コピーオブジェクト
             */
            CEffekseerManager( const CEffekseerManager& rhs );

            /*!
             *  @brief      デストラクタ
             */
            ~CEffekseerManager( void ) = default;

            /*!
             *  @brief      代入演算子
             *
             *  @param[in]  rhs 代入オブジェクト
             *
             *  @return     自身のオブジェクト
             */
            CEffekseerManager&    operator=( const CEffekseerManager& rhs );

            /*!
             *  @brief      Effekseerリソースリスト
             */
            typedef std::list<CEffekseerResource*> EFFEKSEER_LIST;

            //! Effekseerリソースリスト
            EFFEKSEER_LIST  m_EffekseerList;
        };
    }
}
