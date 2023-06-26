
/*!
 *  @file       effect.cpp
 *  @brief      �G�t�F�N�g
 *  @author     Kazuto Shimazaki
 *  @date       2021/12/02
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "effect.h"

const std::string IEffect::m_effect_category = "Effect";

/*
 *  �R���X�g���N�^
 */
IEffect::
IEffect(aqua::IGameObject* parent, const std::string& object_name)
    : aqua::IGameObject(parent, object_name, m_effect_category)
    , m_Position(aqua::CVector3::ZERO)
{
}

/*
 *  ������
 *  �g�p�֎~
 */
void
IEffect::
Initialize(void)
{
}

void IEffect::Initialize(const aqua::CVector3& position, std::string effect_name, std::string se_name, float rotate)
{
}

/*
 *  �X�V
 */
void
IEffect::
Update(void)
{
}

/*
 *  �`��
 */
void
IEffect::
Draw(void)
{
}

/*
 *  ���
 */
void
IEffect::
Finalize(void)
{
}
