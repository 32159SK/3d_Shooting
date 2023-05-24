
/*!
 *  @file       hit_effect.h
 *  @brief      ヒットエフェクト
 *  @author     Kazuto Shimazaki
 *  @date       2021/12/02
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "..\effect.h"

 /*!
  *  @class      CHitEffect
  *
  *  @brief      ヒットエフェクトクラス
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2021/12/02
  *
  *  @version    1.0
  */
class CHitEffect
    : public IEffect
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親のオブジェクト
     */
    CHitEffect(IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CHitEffect(void) = default;

    ///*!
    // *  @brief      初期化
    // *
    // *  @param[in]  position    位置
    // */
    //void    Initialize(const aqua::CVector2& position, const aqua::CVector2& player_size, std::string effect_name, std::string se_name) override;


private:

};
