
/*!
 *  @file       hit_effect.cpp
 *  @brief      ヒットエフェクト
 *  @author     Kazuto Shimazaki
 *  @date       2021/12/02
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "hit_effect.h"

/*
 *  コンストラクタ
 */
CHitEffect::
CHitEffect(aqua::IGameObject* parent)
    : IEffect(parent, "HitEffect")
{
}


