
/*!
 *  @file       effect.h
 *  @brief      �G�t�F�N�g
 *  @author     Kazuto Shimazaki
 *  @date       2023/06/19
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include <game/game_object/effect_manager/effect/effect_id.h>

 /*!
  *  @class      IEffect
  *
  *  @brief      �G�t�F�N�g�N���X
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/06/19
  *
  *  @version    1.0
  */
class IEffect
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    IEffect(aqua::IGameObject* parent, const std::string& object_name);

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �ʒu
     *  @param[in]  effect_name �G�t�F�N�g��
     *  @param[in]  se_name     SE��
     *  @param[in]  rotate      ��]�l
     *  @param[in]  scale       �g�嗦
     */
    virtual void    Initialize(const aqua::CVector3& position, std::string effect_name, std::string se_name, float rotate = 0.0f, float scale = 5.0f);


    /*!
     *  @brief      �X�V
     */
    virtual void    Update(void);

    /*!
     *  @brief      �`��
     */
    virtual void    Draw(void);

    /*!
     *  @brief      ���
     */
    virtual void    Finalize(void);

protected:

    aqua::CVector3      m_Position; // �`��ʒu

private:
    /*!
     *  @brief      ������<br>
     *              �g�p�֎~
     */
    void    Initialize(void) override;

    static const std::string    m_effect_category;  //! �G�t�F�N�g�J�e�S���[
};
