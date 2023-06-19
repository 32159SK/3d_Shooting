
/*!
 *  @file       effect_manager.cpp
 *  @brief      �G�t�F�N�g�Ǘ�
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
    ,"dead"
};

/*
  *  �R���X�g���N�^
  */
CEffectManager::
CEffectManager(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "EffectManager")
{
}

/*
 *  ����
 */
void
CEffectManager::
Create(EFFECT_ID id, const aqua::CVector3& position)
{
    IEffect* effect = nullptr;

    if (id != EFFECT_ID::SKILL)
        effect = aqua::CreateGameObject<CNormalEffect>(this);
    //else
    //effect = aqua::CreateGameObject<CSkillEffect>(this);
    effect->Initialize(position, m_effect_file_names[(int)id], "");
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
