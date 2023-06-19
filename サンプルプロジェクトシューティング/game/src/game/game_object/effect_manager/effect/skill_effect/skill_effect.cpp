
/*!
 *  @file       hit_effect.cpp
 *  @brief      ヒットエフェクト
 *  @author     Kazuto Shimazaki
 *  @date       2021/12/02
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "skill_effect.h"

 /*
  *  コンストラクタ
  */
CSkillEffect::
CSkillEffect(aqua::IGameObject* parent)
    : IEffect(parent, "SkillEffect")
{
}


/*
 *  初期化
 */
void 
CSkillEffect::Initialize(const aqua::CVector3& position, std::string effect_name, std::string se_name)
{
}


