
/*!
 *  @file       fmf_loader.h
 *  @brief      FMFローダー
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <string>

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CFMFLoader
     *
     *  @brief      FMFローダークラス
     * 
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CFMFLoader
    {
    public:
        /*!
         *  @brief      コンストラクタ
         */
        CFMFLoader( void );

        /*!
         *  @brief      デストラクタ
         */
        ~CFMFLoader( void ) = default;

        /*!
         *  @brief      FMFファイル読み込み
         *
         *  @param[in]  file_name   ファイル名
         */
        void            Load( const std::string& file_name );

        /*!
         *  @brief      解放
         */
        void            Unload( void );

        /*!
         *  @brief      データ部のサイズ取得
         *
         *  @return     データ部のサイズ
         */
        int             GetSize( void );

        /*!
         *  @brief      レイヤー数取得
         *
         *  @return     レイヤー数
         */
        int             GetLayerCount( void );

        /*!
         *  @brief      マップの幅取得
         *
         *  @return     マップの幅
         */
        int             GetMapWidth( void );

        /*!
         *  @brief      マップの高さ取得
         *
         *  @return     マップの高さ
         */
        int             GetMapHeight( void );

        /*!
         *  @brief      チップの幅取得
         *
         *  @return     チップの幅
         */
        int             GetChipWidth( void );

        /*!
         *  @brief      チップの高さ取得
         *
         *  @return     チップの高さ
         */
        int             GetChipHeight( void );

        /*!
         *  @brief      データ部取得
         *
         *  @return     データ部
         */
        unsigned char*  GetData( void );

        /*!
         *  @brief      1レイヤー辺りのサイズ取得
         *
         *  @return     1レイヤー辺りのサイズ
         */
        int             GetLayerSize( void );

        /*!
         *  @brief      レイヤー別データ取得
         *
         *  @return     レイヤーID
         */
        unsigned char*  GetLayerData( int layer_id );

        /*!
         *  @brief      横に並んでいるチップの数
         *              ビットに合わせて数が変わる
         *              8bitの場合、16個
         *              16bitの場合、255個
         *
         *  @return     横に並んでいるチップの数
         */
        int             GetChipLineCount( void );

    private:
        /*!
         *  @class      FMF_HEADER
         *
         *  @brief      FMFヘッダ構造体
         * 
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        struct FMF_HEADER
        {
            //! "FMF_"
            unsigned char identifer[4];
            //! ヘッダを除くマップデータのサイズ
            unsigned int  size;
            //! マップの幅(チップ数)
            unsigned int  mapWidth;
            //! マップの高さ(チップ数)
            unsigned int  mapHeight;
            //! チップの幅(ピクセル単位)
            unsigned char chipWidth;
            //! チップの高さ(ピクセル単位)
            unsigned char chipHeight;
            //! レイヤー数
            unsigned char layerCount;
            //! チップのビット数(8か16)
            unsigned char bitCount;
        };

        //! ヘッダ情報
        FMF_HEADER      m_Header;
        //! データ部
        unsigned char*  m_Data;
        //! チップの並んでいる数
        int             m_ChipLineCount;
    };
}
