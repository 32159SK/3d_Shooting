
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
#include "effect/normal_effect/normal_effect.h"

const std::string CEffectManager::m_effect_file_names[] =
{
     "hit"
    ,"broken"
    ,"beam_2"
    ,"dead"
    ,"boss_dead"
};

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
Create(EFFECT_ID id, const aqua::CVector3& position, float rotate, float scale)
{
    IEffect* effect = nullptr;

    if (id != EFFECT_ID::SKILL)
        effect = aqua::CreateGameObject<CNormalEffect>(this);
    effect->Initialize(position, m_effect_file_names[(int)id], "",rotate,scale);
}

aqua::CEffect3D* CEffectManager::CreateGetEffect(EFFECT_ID id, const aqua::CVector3& position, float rotate, float scale)
{
    CNormalEffect* effect = nullptr;
    effect = aqua::CreateGameObject<CNormalEffect>(this);
    effect->Initialize(position, m_effect_file_names[(int)id], "", rotate, scale);
    return effect->GetEffect();
}

void CEffectManager::Update(void)
{
    IGameObject::Update();
}

void CEffectManager::Draw(void)
{
    IGameObject::Draw();
}

void CEffectManager::Finalize(void)
{
    IGameObject::Finalize();
}
