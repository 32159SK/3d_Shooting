
/*!
 *  @file       effect.h
 *  @brief      エフェクト
 *  @author     Kazuto Shimazaki
 *  @date       2023/06/19
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include <game/game_object/effect_manager/effect/effect_id.h>

 /*!
  *  @class      IEffect
  *
  *  @brief      エフェクトクラス
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/06/19
  *
  *  @version    1.0
  */
class IEffect
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     *  @param[in]  object_name     オブジェクト名
     */
    IEffect(aqua::IGameObject* parent, const std::string& object_name);

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    位置
     *  @param[in]  effect_name エフェクト名
     *  @param[in]  se_name     SE名
     *  @param[in]  rotate      回転値
     *  @param[in]  scale       拡大率
     */
    virtual void    Initialize(const aqua::CVector3& position, std::string effect_name, float rotate = 0.0f, float scale = 5.0f);


    /*!
     *  @brief      更新
     */
    virtual void    Update(void);

    /*!
     *  @brief      描画
     */
    virtual void    Draw(void);

    /*!
     *  @brief      解放
     */
    virtual void    Finalize(void);

protected:

    aqua::CVector3      m_Position; // 描画位置

private:
    /*!
     *  @brief      初期化<br>
     *              使用禁止
     */
    void    Initialize(void) override;

    static const std::string    m_effect_category;  //! エフェクトカテゴリー
};
