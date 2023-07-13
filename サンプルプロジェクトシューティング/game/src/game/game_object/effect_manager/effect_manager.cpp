
/*!
 *  @file       effect_manager.cpp
 *  @brief      エフェクト管理
 *  @author     kazuto shimazaki
 *  @date       2023/06/19
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
    ,"beam"
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
    // エフェクト再生クラスを生成し、引数から受け取った情報をもとにそれに合わせたエフェクトを再生
    IEffect* effect = nullptr;
    effect = aqua::CreateGameObject<CNormalEffect>(this);
    effect->Initialize(position, m_effect_file_names[(int)id], "",rotate,scale);
}

aqua::CEffect3D* CEffectManager::CreateGetEffect(EFFECT_ID id, const aqua::CVector3& position, float rotate, float scale)
{
    // エフェクト再生クラスを生成
    CNormalEffect* effect = nullptr;
    effect = aqua::CreateGameObject<CNormalEffect>(this);
    effect->Initialize(position, m_effect_file_names[(int)id], "", rotate, scale);
    // 生成したクラスで再生中のエフェクトのポインタ渡す
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
