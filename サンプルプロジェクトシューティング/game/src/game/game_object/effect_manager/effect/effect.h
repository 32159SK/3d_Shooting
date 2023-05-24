
/*!
 *  @file       effect.h
 *  @brief      エフェクト
 *  @author     Kazuto Shimazaki
 *  @date       2021/12/02
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
  *  @date       2021/12/02
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
     */
    virtual void    Initialize(EFFECT_ID id, const aqua::CVector3& position, std::string effect_name, std::string se_name);


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

    aqua::CVector3      m_Position;

private:
    /*!
     *  @brief      初期化<br>
     *              使用禁止
     */
    void    Initialize(void) override;

    static const std::string    m_effect_category;  //! エフェクトカテゴリー

};
