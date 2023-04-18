#pragma once

#include "../../../resources/resources.h"


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
         *  @class      CModelResource
         *
         *  @brief      モデルリソースクラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2023/04/13
         *
         *  @version    7.17
         */
        class CModelResource
            : public IResourceObject
        {
            /*!
             *  @brief      コンストラクタ
             */
            CModelResource(void);

            /*!
             *  @brief      デストラクタ
             */
            ~CModelResource(void) = default;

            /*!
             *  @brief      モデルの読み込み
             *
             *  @param[in]  file_name   ファイル名
             */
            void        Load(const std::string& file_name);

            /*!
             *  @brief      モデルの複製
             *
             *  @param[in]  model   複製するモデル
             */
            void        Duplicate(const CModelResource* model);

            /*!
             *  @brief      モデルの解放
             */
            void        Unload(void);

            /*!
             *  @brief      総アニメーション数
             */
            int         GetTotalAnimeNum(void);

        private:

            friend class CModel;
            friend class CModelManager;

            int     m_TotalAnimeNum;
        };


    }
}