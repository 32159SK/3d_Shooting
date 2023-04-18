
/*!
 *  @file       animation_sprite.h
 *  @brief      アニメーション付きスプライトクラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>
#include <vector>
#include <string>
#include "..\alphablend\alphablend.h"
#include "..\texture\texture.h"
#include "..\surface\surface.h"
#include "..\draw_object\draw_object.h"
#include "..\..\mathematics\mathematics.h"
#include "..\color\color.h"
#include "..\..\utility\utility.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CAnimationSprite
     *
     *  @brief      アニメーション付きスプライトクラス
     *
     *  @details    JSON形式のファイル(.ass)を読み込み、<br>
     *              スプライトのアニメーションを再生します。<br>
     *              アニメーションはassファイル内で定義したキー名を指定します。<br>
     *              ループ再生しないアニメーションでは再生終了を検知することも可能です。
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CAnimationSprite
        : public aqua::core::IDrawObject
    {
    public:
        //! 位置
        aqua::CVector2      position;
        //! 色
        aqua::CColor        color;
        //! 拡縮・回転の基準点
        aqua::CVector2      anchor;
        //! 拡大率
        aqua::CVector2      scale;
        //! 回転値(ラジアン)
        float               rotation;
        //! アルファブレンドモード
        aqua::ALPHABLEND    blend_mode;

        /*!
         *  @brief      コンストラクタ
         */
        CAnimationSprite( void );

        /*!
         *  @brief      デストラクタ
         */
        ~CAnimationSprite(void) = default;

        /*!
         *  @brief      生成
         *
         *  @param[in]  file_name   アニメーション用ファイル名(.ass)
         */
        void    Create( const std::string& file_name );

        /*!
         *  @brief      生成
         *
         *  @param[in]  file_name   アニメーション用ファイル名(.ass)
         *  @param[in]  anime_name  アニメーション名
         */
        void    Create( const std::string& file_name, const std::string& anime_name );

        /*!
         *  @brief      生成
         *
         *  @param[in]  file_name   アニメーション用ファイル名(.ass)
         *  @param[in]  anime_id    アニメーションID
         */
        void    Create( const std::string& file_name, int anime_id );

        /*!
         *  @brief      解放
         */
        void    Delete( void );

        /*!
         *  @brief      更新
         */
        void    Update( );

        /*!
         *  @brief      描画
         */
        void    Draw( void );

        /*!
         *  @brief      アニメーションの変更
         *
         *  @param[in]  anime_name  アニメーション名
         */
        void    Change( const std::string& anime_name );

        /*!
         *  @brief      アニメーションの変更
         *
         *  @param[in]  anime_id    アニメーションID
         */
        void    Change( int anime_id );

        /*!
         *  @brief      アニメーションの再生
         *              カレントフレームから再生する
         */
        void    Play( void );

        /*!
         *  @brief      アニメーションの停止
         */
        void    Stop( void );

        /*!
         *  @brief      アニメーションのリセット
         *              アニメーションフレームをリセットし0にする
         */
        void    ResetAnimationFrame( void );

        /*!
         *  @brief      アニメーション終了検知
         *
         *  @retval     true    アニメーション終了
         *  @retval     false   アニメーション継続
         */
        bool    Finished( void );

        /*!
         *  @brief      現在再生しているアニメーション番号取得
         *
         *  @return     再生中のアニメーション番号
         */
        int             GetCurrentAnimationID(void) const { return m_CurrentAnimeID; }

        /*!
         *  @brief      現在再生しているアニメーション名取得
         *
         *  @return     アニメーション名
         */
        std::string     GetAnimationName( void );

        /*!
         *  @brief      アニメーション数の取得
         *
         *  @return     アニメーション数
         */
        int             GetAnimationCount( void ) const;

        /*!
         *  @brief      テクスチャの幅取得
         *
         *  @return     テクスチャの幅
         */
        int             GetTextureWidth(void) const { return m_Texture.GetWidth(); }

        /*!
         *  @brief      テクスチャの高さ取得
         *
         *  @return     テクスチャの高さ
         */
        int             GetTextureHeight(void) const { return m_Texture.GetHeight(); }
 
       /*!
        *  @brief      フレームの幅取得
        *
        *  @return     フレームの幅
        */
        int             GetFrameWidth(void) const { return m_FrameWidth; }

       /*!
        *  @brief      フレームの高さ取得
        *
        *  @return     フレームの高さ
        */
        int             GetFrameHeight(void) const { return m_FrameHeight; }

        /*!
         *  @brief      アニメーションの再生速度率取得
         *
         *  @return     アニメーションの再生速度率
         */
        float           GetPlayRate(void) const { return m_PlaySpeedRate; }

        /*!
         *  @brief      アニメーションの再生速度率設定
         *
         *  @param[in]  rate    アニメーションの再生速度率
         */
        void            SetPlayRate(float rate) { m_PlaySpeedRate = rate; }

        /*!
         *  @brief      現在のアニメーションフレーム取得
         *
         *  @return     現在のアニメーションフレーム
         */
        float           GetCurrentAnimationFrame(void) const { return m_CurrentFrame; }

        /*!
         *  @brief      アニメーションフレーム設定
         *
         *  @param[in]  frame   アニメーションフレーム
         */
        void            SetAnimationFrame(float frame) { m_CurrentFrame = frame; }

        /*!
         *  @brief      リソースハンドル取得
         *
         *  @return     リソースハンドル
         */
        int             GetResourceHandle(void) const { return m_Texture.GetResourceHandle(); }

    private:
        /*!
         *  @brief      ASSファイルの読み込みと解析
         *
         *  @param[in]  file_name   アニメーション用ファイル名(.ass)
         */
        void    LoadASS( const std::string& file_name );

        /*!
         *  @brief      アニメーション名をアニメーションIDに変換
         *
         *  @param[in]  anime_name  アニメーション名
         *
         *  @return     アニメーションID
         */
        int     ConvertAnimationNameToAnimationID( const std::string& anime_name );

        /*!
         *  @brief      アニメーションデータ構造体
         */
        struct ANIMATION_DATA
        {
            //! アニメーション名
            std::string         name;
            //! フレームデータ
            std::vector<int>    frames;
            //! 更新間隔(秒単位)
            float               interval;
            //! ループフラグ
            bool                loop;
        };

        /*!
         *  @brief      アニメーションデータリスト
         */
        typedef std::vector<ANIMATION_DATA> ANIMATION_LIST;

        /*!
         *  @brief      アニメーションスプライトキーID
         */
        enum class ASS_KEY
        {
            //! 使用するファイル名
            FILE,
            //! フレームオブジェクト
            FRAME,
            //! フレームの幅
            WIDTH,
            //! フレームの高さ
            HEIGHT,
            //! 横に並んでいるフレームの数
            COLS,
            //! 縦に並んでいるフレームの数
            ROWS,
            //! アニメーションオブジェクト
            ANIMATIONS,
            //! アニメーションで使用するフレーム番号
            FRAMES,
            //! アニメーション更新間隔(秒単位)
            INTERVAL,
            //! アニメーションループフラグ
            LOOP,

            //! ASSキーの数
            MAX
        };

        //! キー名
        static const char*          m_key_names[(int)ASS_KEY::MAX];
        //! 1秒
        static const float          m_second;
        //! ダミーID
        static const int            m_dummy_anime_id;
        //! ファイル名
        std::string                 m_FileName;
        //! 1フレームの幅
        int                         m_FrameWidth;
        //! 1フレームの高さ
        int                         m_FrameHeight;
        //! 横に並んでいるフレームの数
        int                         m_FrameCols;
        //! 縦に並んでいるフレームの数
        int                         m_FrameRows;
        //! アニメーションリスト
        ANIMATION_LIST              m_AnimationList;
        //! 現在のアニメーションID
        int                         m_CurrentAnimeID;
        //! 現在のアニメーションフレーム
        float                       m_CurrentFrame;
        //! 現在のアニメーション更新速度
        float                       m_CurrentAnimeFPS;
        //! テクスチャ
        aqua::CTexture              m_Texture;
        //! テクスチャの読み込み範囲
        aqua::CRect                 m_Rect;
        //! アニメーション停止フラグ
        bool                        m_StopFlag;
        //! アニメーションの再生速度率
        float                       m_PlaySpeedRate;
    };
}
