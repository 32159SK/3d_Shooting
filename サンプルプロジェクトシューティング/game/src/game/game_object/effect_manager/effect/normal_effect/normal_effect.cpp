
/*!
 *  @file       hit_effect.cpp
 *  @brief      ヒットエフェクト
 *  @author     Kazuto Shimazaki
 *  @date       2021/12/02
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "normal_effect.h"

 /*
  *  コンストラクタ
  */
CNormalEffect::
CNormalEffect(aqua::IGameObject* parent)
    : IEffect(parent, "NormalEffect")
{
}


/*
 *  初期化
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
    // エフェクトが終了したら自身を削除
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


