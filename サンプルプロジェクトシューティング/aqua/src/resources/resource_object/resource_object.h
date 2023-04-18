
/*!
 *  @file       resource_object.h
 *  @brief      リソースオブジェクト用インターフェース
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <string>

/*!
 *  @brief      使用していないハンドル値
 */
#define AQUA_UNUSED_HANDLE      ( -1 )

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
         *  @brief      リソースタイプ
         */
        enum class RESOURCE_TYPE
        {
            //! ダミー
            DUMMY,
            //! 読み込んだテクスチャ
            LOAD_TEXTURE,
            //! 読み込んだマスクテクスチャ
            LOAD_MASK_TEXTURE,
            //! 読み込んだサウンド
            LOAD_SOUND,
            //! 読み込んだメッシュ
            LOAD_MODEL,
            //! 読み込んだモーション
            LOAD_MOTION,
            //! 読み込んだシェーダプログラム
            LOAD_SHADER,
            //! 読み込んだビデオ
            LOAD_VIDEO,
            //! 読み込んだMMDカメラ
            LOAD_MMD_CAMERA,
            //! 読み込んだEffekseer
            LOAD_EFFEKSEER,
            //! 生成したテクスチャ
            CREATE_TEXTURE,
            //! 生成したフォント
            CREATE_FONT,
            //! 生成したディレクショナルライト
            CREATE_DIRECTIONAL_LIGHT
        };

        /*!
         *  @class      IResourceObject
         *
         *  @brief      リソースオブジェクト用インターフェイスクラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class IResourceObject
        {
        public:
            /*!
             *  @brief      コンストラクタ
             */
            IResourceObject( void );

            /*!
             *  @brief      コンストラクタ
             *
             *  @param[in]  type    リソースタイプ
             */
            IResourceObject( RESOURCE_TYPE type );

            /*!
             *  @brief      コンストラクタ
             *
             *  @param[in]  type    リソースタイプ
             *  @param[in]  name    リソース名
             */
            IResourceObject( RESOURCE_TYPE type, const std::string& name );

            /*!
             *  @brief      デストラクタ
             */
            virtual ~IResourceObject( void ) = default;

            /*!
             *  @brief      リソースタイプ取得
             *
             *  @return     リソースタイプ
             */
            RESOURCE_TYPE   GetResourceType(void) const { return m_ResourceType; }

            /*!
             *  @biref      リソースタイプ設定
             *
             *  @param[in]  type    リソースタイプ
             */
            void            SetResourceType(RESOURCE_TYPE type) { m_ResourceType = type; }

            /*!
             *  @brief      リソースハンドル取得
             *
             *  @return     リソースハンドル
             */
            int             GetResourceHandle(void) const { return m_ResourceHandle; }

            /*!
             *  @brief      リソースファイル名取得
             *
             *  @return     リソースファイル名
             */
            std::string     GetResourceName(void) const { return m_ResourceName; }

            /*!
             *  @biref      リソースファイル名設定
             *
             *  @param[in]  file_name   リソースファイル名
             */
            void            SetResourceName(const std::string& file_name) { m_ResourceName = file_name; }

            /*!
             *  @brief      参照カウンタ加算
             *
             *  @return     現在の参照カウント値
             */
            int             AddReference(void) { return (++m_ReferenceCount); }

            /*!
             *  @brief      参照カウンタ減算
             *
             *  @return     現在の参照カウント値
             */
            int             RemoveReference(void) { return (--m_ReferenceCount <= 0 ? 0 : m_ReferenceCount); }

            /*!
             *  @brief      利用可能か調べる
             *
             *  @retval     true    利用可能
             *  @retval     false   利用不可能
             */
            bool            IsEnable(void) const { return m_Enabel; }

        protected:
            //! リソースタイプ
            RESOURCE_TYPE   m_ResourceType;
            //! リソースファイル名
            std::string     m_ResourceName;
            //! リソースハンドル
            int             m_ResourceHandle;
            //! 参照カウント
            int             m_ReferenceCount;
            //! 利用可能フラグ
            bool            m_Enabel;
        };
    }
}
