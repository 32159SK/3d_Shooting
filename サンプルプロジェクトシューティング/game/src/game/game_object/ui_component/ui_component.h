
/*!
 *  @file       ui_component.h
 *  @brief      UI�R���|�[�l���g
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
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    IUIComponent(aqua::IGameObject* parent, const std::string& object_name);

    /*!
     *  @brief      �f�X�g���N�^
     */
    virtual ~IUIComponent(void) = default;

private:
    static const std::string    m_ui_category;
};
