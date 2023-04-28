
/*!
 *  @file       ui_component.cpp
 *  @brief      UIコンポーネント
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/28
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "../game_object.h"
#include "ui_component.h"

const std::string IUIComponent::m_ui_category = "UIComponent";

/*
 *  コンストラクタ
 */
IUIComponent::
IUIComponent(aqua::IGameObject* parent, const std::string& object_name)
    : aqua::IGameObject(parent, object_name, m_ui_category)
{
}
