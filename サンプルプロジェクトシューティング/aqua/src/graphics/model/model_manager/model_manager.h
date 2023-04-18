
/*!
 *  @file       model_manager.h
 *  @brief      モデル管理クラス
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/13
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
        class CModelResource;

        /*!
         *  @class      CModelManager
         *
         *  @brief      モデル管理クラス
         *
         *  @author     Kazuto Shimazaki
         *
         *  @date       2023/04/13
         *
         *  @version    7.17
         */
        class CModelManager
        {
        public:
            /*!
             *  @brief      インスタンスの取得
             *
             *  @return     インスタンスへの参照
             */
            static CModelManager& GetInstance(void);

            /*!
             *  @brief      モデルの読み込み
             *
             *  @param[in]  file_name   ファイル名
             *
             *  @return     モデルリソースクラス
             */
            CModelResource* Load(const std::string& file_name);

            /*!
             *  @brief      モデルの解放
             *
             *  @param[in]  model     モデルリソースクラス
             */
            void                    Unload(CModelResource* model);

            /*!
             *  @brief      モデルの生成
             *
             *  @param[in]  alpha_channel   アルファチャンネル
             */
            CModelResource* Create(bool alpha_channel);

            /*!
             *  @brief      モデルの解放
             */
            void                    Delete(CModelResource* model);

            /*!
             *  @brief      モデルの検索
             *
             *  @param[in]  file_name   ファイル名
             *
             *  @return     モデルリソースクラス
             */
            CModelResource* Find(const std::string& file_name);

            /*!
             *  @brief      モデルリストのクリア
             */
            void                    Clear(void);

        private:
            /*!
             *  @brief      コンストラクタ
             */
            CModelManager(void);

            /*!
             *  @brief      コピーコンストラクタ
             *
             *  @param[in]  rhs コピーオブジェクト
             */
            CModelManager(const CModelManager& rhs);

            /*!
             *  @brief      デストラクタ
             */
            ~CModelManager(void) = default;

            /*!
             *  @brief      代入演算子
             *
             *  @param[in]  rhs 代入オブジェクト
             *
             *  @return     自身のオブジェクト
             */
            CModelManager& operator=(const CModelManager& rhs);

            /*!
             *  @brief      モデルリソースリスト
             */
            typedef std::list<CModelResource*> MODEL_LIST;

            //! モデルリソースリスト
            MODEL_LIST          m_ModelList;
        };
    }
}
