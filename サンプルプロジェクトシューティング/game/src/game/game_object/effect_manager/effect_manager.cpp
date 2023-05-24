
/*!
 *  @file       effect_manager.cpp
 *  @brief      エフェクト管理
 *  @author     kazuto shimazaki
 *  @date       2023/05/23
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "effect_manager.h"
#include "effect/hit_effect/hit_effect.h"

 /*
  *  コンストラクタ
  */
CEffectManager::
CEffectManager(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "EffectManager")
{
}

/*
 *  生成
 */
void
CEffectManager::
Create(EFFECT_ID id, const aqua::CVector3& position, std::string effect_name, std::string se_name)
{
    IEffect* effect = nullptr;

    switch (id)
    {
    case EFFECT_ID::HIT:        effect = aqua::CreateGameObject<CHitEffect>(this);      break;
    //case EFFECT_ID::SKILL:    effect = aqua::CreateGameObject<CBarrierEffect>(this);  break;
    }

}
