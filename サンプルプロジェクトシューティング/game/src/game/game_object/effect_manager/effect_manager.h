
/*!
 *  @file       effect_manager.h
 *  @brief      エフェクト管理
 *  @author     Kazuto Shimazaki
 *  @date       2023/06/19
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "effect\effect.h"
#include "effect\effect_id.h"

 /*!
  *  @class      CEffectManager
  *
  *  @brief      エフェクト管理クラス
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/06/19
  *
  *  @version    1.0
  */
class CEffectManager
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     */
    CEffectManager(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CEffectManager(void) = default;

    /*!
     *  @brief      エフェクト生成
     *
     *  @param[in]  id          エフェクトID
     *  @param[in]  position    位置
     *  @param[in]  rotate      回転値
     *  @param[in]  scale       拡大率
     */
    void        Create(EFFECT_ID id, const aqua::CVector3& position, float rotate = 0.0f, float scale = 5.0f);

    /*!
     *  @brief      エフェクト生成しポインタを渡す
     *
     *  @param[in]  id          エフェクトID
     *  @param[in]  position    位置
     *  @param[in]  rotate      回転値
     *  @param[in]  scale       拡大率
     */
    aqua::CEffect3D* CreateGetEffect(EFFECT_ID id, const aqua::CVector3& position, float rotate = 0.0f, float scale = 5.0f);

    /*!
     *  @brief      更新
     */
    void        Update(void)override;

    /*!
     *  @brief      描画
     */
    void        Draw(void)override;

    /*!
     *  @brief      解放
     */
    void        Finalize(void)override;

private:
    static const std::string    m_effect_file_names[];   // エフェクトファイルパス
};
