
/*!
 *  @file       ui_component.h
 *  @brief      UIコンポーネント
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/28
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"

 /*!
  *  @class      IUIComponent
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/04/28
  *
  *  @version    1.0
  */
class IUIComponent
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     *  @param[in]  object_name     オブジェクト名
     */
    IUIComponent(aqua::IGameObject* parent, const std::string& object_name);

    /*!
     *  @brief      デストラクタ
     */
    virtual ~IUIComponent(void) = default;

private:
    static const std::string    m_ui_category;
};
