
/*!
 *  @file       effect.cpp
 *  @brief      エフェクト
 *  @author     Kazuto Shimazaki
 *  @date       2021/12/02
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "effect.h"

const std::string IEffect::m_effect_category = "Effect";

/*
 *  コンストラクタ
 */
IEffect::
IEffect(aqua::IGameObject* parent, const std::string& object_name)
    : aqua::IGameObject(parent, object_name, m_effect_category)
    , m_Position(aqua::CVector3::ZERO)
{
}

/*
 *  初期化
 *  使用禁止
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
 *  更新
 */
void
IEffect::
Update(void)
{
}

/*
 *  描画
 */
void
IEffect::
Draw(void)
{
}

/*
 *  解放
 */
void
IEffect::
Finalize(void)
{
}
