
/*!
 *  @file       sound_manager.h
 *  @brief      サウンド管理クラス
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
        class CSoundResource;

        /*!
         *  @class      CSoundManager
         *
         *  @brief      サウンド管理クラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CSoundManager
        {
        public:
            /*!
             *  @brief      インスタンスの取得
             *
             *  @return     インスタンスへの参照
             */
            static CSoundManager&   GetInstance( void );

            /*!
             *  @brief      サウンドの読み込み
             *
             *  @param[in]  file_name       ファイル名
             *  @param[in]  buffer_count    SE多重再生用バッファ数
             *
             *  @return     サウンドリソースクラス
             */
            CSoundResource*         Load( const std::string& file_name, int buffer_count );

            /*!
             *  @brief      サウンドの解放
             *
             *  @param[in]  sound   テクスチャリソースクラス
             */
            void                    Unload( CSoundResource* sound );

            /*!
             *  @brief      更新
             */
            void                    Update( void );

            /*!
             *  @brief      サウンドの検索
             *
             *  @param[in]  file_name   ファイル名
             *
             *  @return     サウンドリソースクラス
             */
            CSoundResource*         Find( const std::string& file_name );

            /*!
             *  @brief      サウンドリストのクリア
             */
            void                    Clear( void );

        private:
            /*!
             *  @brief      コンストラクタ
             */
            CSoundManager( void );

            /*!
             *  @brief      コピーコンストラクタ
             *
             *  @param[in]  rhs コピーオブジェクト
             */
            CSoundManager( const CSoundManager& rhs );

            /*!
             *  @brief      デストラクタ
             */
            ~CSoundManager( void ) = default;

            /*!
             *  @brief      代入演算子
             *
             *  @param[in]  rhs 代入オブジェクト
             *
             *  @return     自身のオブジェクト
             */
            CSoundManager&    operator=( const CSoundManager& rhs );

            /*!
             *  @brief      サウンドリソースリスト
             */
            typedef std::list<CSoundResource*>  SOUND_RESOURCE_LIST;

            //! サウンドリソースリスト
            SOUND_RESOURCE_LIST     m_SoundResourceList;
        };
    }
}
