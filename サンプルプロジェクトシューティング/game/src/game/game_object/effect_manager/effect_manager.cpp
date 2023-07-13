
/*!
 *  @file       effect_manager.cpp
 *  @brief      �G�t�F�N�g�Ǘ�
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
Create(EFFECT_ID id, const aqua::CVector3& position, float rotate, float scale)
{
    // �G�t�F�N�g�Đ��N���X�𐶐����A��������󂯎�����������Ƃɂ���ɍ��킹���G�t�F�N�g���Đ�
    IEffect* effect = nullptr;
    effect = aqua::CreateGameObject<CNormalEffect>(this);
    effect->Initialize(position, m_effect_file_names[(int)id], "",rotate,scale);
}

aqua::CEffect3D* CEffectManager::CreateGetEffect(EFFECT_ID id, const aqua::CVector3& position, float rotate, float scale)
{
    // �G�t�F�N�g�Đ��N���X�𐶐�
    CNormalEffect* effect = nullptr;
    effect = aqua::CreateGameObject<CNormalEffect>(this);
    effect->Initialize(position, m_effect_file_names[(int)id], "", rotate, scale);
    // ���������N���X�ōĐ����̃G�t�F�N�g�̃|�C���^�n��
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
