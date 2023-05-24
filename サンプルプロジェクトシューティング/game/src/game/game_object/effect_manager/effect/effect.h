
/*!
 *  @file       effect.h
 *  @brief      �G�t�F�N�g
 *  @author     Kazuto Shimazaki
 *  @date       2021/12/02
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
  *  @date       2021/12/02
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
     */
    virtual void    Initialize(EFFECT_ID id, const aqua::CVector3& position, std::string effect_name, std::string se_name);


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

    aqua::CVector3      m_Position;

private:
    /*!
     *  @brief      ������<br>
     *              �g�p�֎~
     */
    void    Initialize(void) override;

    static const std::string    m_effect_category;  //! �G�t�F�N�g�J�e�S���[

};
