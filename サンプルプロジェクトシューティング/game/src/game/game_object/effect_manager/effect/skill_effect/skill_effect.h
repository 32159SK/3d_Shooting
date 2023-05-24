
/*!
 *  @file       hit_effect.h
 *  @brief      �q�b�g�G�t�F�N�g
 *  @author     Kazuto Shimazaki
 *  @date       2021/12/02
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "..\effect.h"

 /*!
  *  @class      CHitEffect
  *
  *  @brief      �q�b�g�G�t�F�N�g�N���X
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2021/12/02
  *
  *  @version    1.0
  */
class CSkillEffect
    : public IEffect
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent  �e�̃I�u�W�F�N�g
     */
    CSkillEffect(IGameObject* parent);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSkillEffect(void) = default;

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �ʒu
     */
    void    Initialize(EFFECT_ID id, const aqua::CVector3& position, std::string effect_name, std::string se_name)override;



private:

};
