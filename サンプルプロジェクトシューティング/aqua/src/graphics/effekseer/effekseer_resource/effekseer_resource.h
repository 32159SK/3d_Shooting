
/*!
 *  @file       effekseer_resource.h
 *  @brief      Effekseerリソース
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "..\..\..\resources\resources.h"

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
         *  @class      CEffekseerResource
         *
         *  @brief      Effekseerリソースクラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CEffekseerResource
            : public core::IResourceObject
        {
        public:
            /*!
             *  @brief      コンストラクタ
             */
            CEffekseerResource( void );

            /*!
             *  @brief      デストラクタ
             */
            ~CEffekseerResource( void ) = default;

            /*!
             *  @brief      Effekseerの読み込み
             *
             *  @param[in]  file_name   ファイル名
             */
            void        Load( const std::string& file_name );

            /*!
             *  @brief      テクスチャの解放
             */
            void        Unload( void );

        };
    }
}
