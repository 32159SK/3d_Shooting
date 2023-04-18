
/*!
 *  @file       effect2D.h
 *  @brief      Effekseer用2Dエフェクト
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "..\draw_object\draw_object.h"
#include "..\..\mathematics\mathematics.h"
#include ".\..\color\color.h"
#include "..\effekseer\effekseer.h"

 /*!
  *  @brief      aqua名前空間
  */
namespace aqua
{
    /*!
     *  @class      CEffect2D
     *
     *  @brief      Effekseer用2Dエフェクトクラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CEffect2D
        : public aqua::core::IDrawObject
    {
    public:
        //! 表示位置
        aqua::CVector2  position;
        //! 拡大率
        aqua::CVector2  scale;
        //! 回転値(ラジアン)
        float           rotation;
        //! 色
        aqua::CColor    color;

        /*!
         *  @brief  コンストラクタ
         */
        CEffect2D(void);

        /*!
         *  @brief  デストラクタ
         */
        ~CEffect2D(void) = default;

        /*!
         *  @brief  生成
         *
         *  @param[in]  file_name   ファイル名
         */
        void    Create(const std::string& file_name);

        /*!
         *  @brief  解放
         */
        void    Delete(void);

        /*!
         *  @brief  更新
         */
        void    Update(void);

        /*!
         *  @brief  描画
         */
        void    Draw(void);

        /*!
         *  @brief  再生
         */
        void    Play(void);

        /*!
         *  @brief  停止
         */
        void    Stop(void);

        /*!
         *  @brief  エフェクト終了検知
         *
         *  @retval true    エフェクト再生終了
         *  @retval false   エフェクト再生中
         */
        bool    Finished(void);

        /*!
         *  @brief  再生中のエフェクトの再生速度取得
         *
         *  @return 再生速度
         */
        float   GetPlayingSpeed(void);

        /*!
         *  @brief  再生中のエフェクトの再生速度設定
         *
         *  @param[in]  speed   再生速度
         */
        void    SetPlayingSpeed(float speed);

        /*!
         *  @brief  リソースハンドル取得
         *
         *  @return リソースハンドル
         */
        int     GetResourceHandle( void ) const;

    private:
        //! Effekseerリソース
        CEffekseer  m_Effekseer;
        //! 再生中のエフェクトハンドル
        int         m_PlayingEffectHandle;
        //! 再生速度
        float       m_PlaySpeed;
    };
}
