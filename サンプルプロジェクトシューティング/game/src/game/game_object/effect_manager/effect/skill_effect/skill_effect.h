
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
class CSkillEffect
    : public IEffect
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親のオブジェクト
     */
    CSkillEffect(IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CSkillEffect(void) = default;

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    位置
     */
    void    Initialize(EFFECT_ID id, const aqua::CVector3& position, std::string effect_name, std::string se_name)override;



private:

};
