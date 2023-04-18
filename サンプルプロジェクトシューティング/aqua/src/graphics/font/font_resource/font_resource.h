
/*!
 *  @file       font_resource.h
 *  @brief      フォントリソース
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
     *  @brief      フォント名ID
     */
    enum class FONT_FAMILY_ID
    {
        //! メイリオ
        MEIRIO,
        //! MSゴシック
        MS_GOTHIC,
        //! MS明朝
        MS_MINCHO,
        //! HG行書体
        HG_GYOUSYO,
        //! HG創英角ﾎﾟｯﾌﾟ体
        HG_SOUEIKAKUPOP,
        //! 游ゴシック
        YU_GOTHIC,
        //! 游明朝
        YU_MINCHO,

        //! フォント名ID数
        MAX
    };

    /*!
     *  @brief      aqua::core名前空間
     */
    namespace core
    {
        /*!
         *  @class      CFontResource
         *
         *  @brief      フォントリソースクラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CFontResource
            : public core::IResourceObject
        {
        public:
            /*!
             *  @brief      コンストラクタ
             */
            CFontResource( void );

            /*!
             *  @brief      デストラクタ
             */
            ~CFontResource( void ) = default;

            /*!
             *  @brief      フォントの生成
             *
             *  @param[in]  size        フォントサイズ
             *  @param[in]  edge_bold   エッジの太さ(0 = エッジなし)
             *  @param[in]  famiry_id   フォント名ID
             */
            void        Create(int size, int edge_bold, bool anti_aliasing, FONT_FAMILY_ID famiry_id);

            /*!
             *  @brief      フォントの削除
             */
            void        Delete( void );

            /*!
             *  @brief      フォントの高さ取得
             */
            int         GetHeight(void) const { return m_FontSize; }

            /*!
             *  @brief      フォントの比較
             *
             *  @param[in]  font    フォントリソースクラス
             *
             *  @retval     true    同じフォントデータ
             *  @retval     false   違うフォントデータ
             */
            bool        CheckFont( core::CFontResource* font );

            /*!
             *  @brief      フォントの比較
             *
             *  @param[in]  size     フォントサイズID
             *  @param[in]  edge_bold   エッジの太さ
             *  @param[in]  famiry_id   フォント名ID
             *
             *  @retval     true    同じフォントデータ
             *  @retval     false   違うフォントデータ
             */
            bool        CheckFont( int size, int edge_bold, FONT_FAMILY_ID famiry_id );

        private:
            /*!
             *  @brief      使用禁止
             */
            void        Load( const std::string& file_name );

            /*!
             *  @brief      使用禁止
             */
            void        Unload( void );

            //! フォント名テーブル
            static const std::string    m_font_family_table[(int)FONT_FAMILY_ID::MAX];
            //! 初期フォントサイズ
            static const int            m_default_font_size;
            //! フォントサイズ
            int                         m_FontSize;
            //! エッジの太さ
            int                         m_EdgeBold;
            //! フォント名ID
            FONT_FAMILY_ID              m_FontFamilyID;
        };
    }
}
