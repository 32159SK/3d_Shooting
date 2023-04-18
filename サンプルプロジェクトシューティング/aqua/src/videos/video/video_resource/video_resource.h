
/*!
 *  @file       video_resource.h
 *  @brief      ビデオリソースファイル
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <windows.h>
#include <string>
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
         *  @class      CVideoResource
         *
         *  @brief      ビデオリソースクラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CVideoResource
            : public core::IResourceObject
        {
        public:
            /*!
             *  @brief      コンストラクタ
             */
            CVideoResource( void );

            /*!
             *  @brief      デストラクタ
             */
            ~CVideoResource( void ) = default;

            /*!
             *  @brief      ビデオファイル読み込み
             *
             *  @param[in]  file_name   ファイル名
             */
            void            Load( const std::string& file_name );

            /*!
             *  @brief      解放
             */
            void            Unload( void );
        };
    }
}
