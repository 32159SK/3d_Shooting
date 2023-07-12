
/*!
 *  @file       hit_effect.cpp
 *  @brief      �q�b�g�G�t�F�N�g
 *  @author     Kazuto Shimazaki
 *  @date       2021/12/02
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "normal_effect.h"

 /*
  *  �R���X�g���N�^
  */
CNormalEffect::
CNormalEffect(aqua::IGameObject* parent)
    : IEffect(parent, "NormalEffect")
{
}


/*
 *  ������
 */
void
CNormalEffect::Initialize(const aqua::CVector3& position, std::string effect_name, std::string se_name, float rotate, float scale)
{
    m_Effect.Create("data\\texture\\effect\\" + effect_name + ".efkefc");
    m_Position = position;
    m_Rotate = rotate;
    m_Effect.position = m_Position;
    m_Effect.rotation.y = aqua::DegToRad(m_Rotate);
    m_Effect.Play();
    m_Effect.scale *= scale;
}

void CNormalEffect::Update(void)
{
    m_Effect.position = m_Position;
    m_Effect.rotation.y = aqua::DegToRad(m_Rotate);

    m_Effect.Update();
    // �G�t�F�N�g���I�������玩�g���폜
    if (m_Effect.Finished())
        DeleteObject();
}

void CNormalEffect::Draw(void)
{
    m_Effect.Draw();
}

void CNormalEffect::Finalize(void)
{
    m_Effect.Delete();
}


