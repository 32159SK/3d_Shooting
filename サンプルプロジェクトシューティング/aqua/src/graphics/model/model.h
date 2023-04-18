
/*!
 *  @file       model.h
 *  @brief      3Dモデルクラス
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/13
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "model_resource\model_resource.h"
#include "../draw_object/draw_object.h"
#include "../../mathematics/mathematics.h"

 /*!
  *  @brief      aqua名前空間
  */
namespace aqua
{
    /*!
     *  @class      CModel
     *
     *  @brief      モデルクラス
     *
     *  @author     Kazuto Shimazaki
     *
     *  @date       2023/04/13
     *
     *  @version    7.17
     */
    class CModel
        :   public core::IDrawObject , public CCollision
    {
    public:

        CVector3        position;

        CVector3        scale;

        CVector3        rotation;

        /*!
         *  @brief      コンストラクタ
         */
        CModel(void);

        /*!
         *  @brief      コピーコンストラクタ
         *
         *  @param[in]  model     テクスチャクラス
         */
        CModel(const CModel& model);

        /*!
         *  @brief      デストラクタ
         */
        ~CModel(void) = default;

        /*!
         *  @brief      モデルの読み込み
         *
         *  @param[in]  file_name   ファイル名
         */
        void    Load(const std::string& file_name);

        /*!
         *  @brief      モデルの解放
         */
        void    Unload(void);

        /*!
         *  @brief      描画
         */
        void    Draw(void);


        /*!
         *  @brief      モデルのリソースハンドル取得
         *
         *  @return     モデルのリソースハンドル取得
         */
        int     GetResourceHandle(void) const
        {
            if (!m_ModelResource) return AQUA_UNUSED_HANDLE;

            return m_ModelResource->GetResourceHandle();
        }


        /*!
         *  @brief      モデルの読み込みチェック
         *
         *  @retval     true    読み込み済み
         *  @retval     false   読み込まれていない
         */
        bool    IsEnable(void) const
        {
            if (!m_ModelResource) return false;

            return m_ModelResource->IsEnable();
        }


        /*!
         *  @brief      代入演算子のオーバーロード
         *
         *  @param[in]  model     テクスチャクラス
         */
        CModel& operator=(const CModel& model);

    private:        

        /*!
         *  @brief      モデルの生成
         *
         *  @param[in]  width           横幅
         *  @param[in]  height          縦幅
         *  @param[in]  alpha_channel   アルファチャンネル
         */
        void    Create(bool alpha_channel);

        /*!
         *  @brief      モデルの解放
         */
        void    Delete(void);

        /*!
         *  @brief      CSurfaceクラスをフレンド登録
         */
        friend class CSurface;

        //! テクスチャリソースクラス
        core::CModelResource* m_ModelResource;
    };
}
