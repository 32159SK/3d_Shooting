
/*!
 *  @file       hit_effect.h
 *  @brief      �ʏ�G�t�F�N�g�N���X
 *  @author     Kazuto Shimazaki
 *  @date       2023/06/19
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "..\effect.h"

 /*!
  *  @class      CNormalEffect
  *
  *  @brief      �ʏ�G�t�F�N�g�N���X
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/06/19
  *
  *  @version    1.0
  */
class CNormalEffect
    : public IEffect
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent  �e�̃I�u�W�F�N�g
     */
    CNormalEffect(IGameObject* parent);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CNormalEffect(void) = default;

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �ʒu
     */
    void    Initialize(const aqua::CVector3& position, std::string effect_name, std::string se_name,float rotate = 0.0f)override;

    /*!
     *  @brief      �X�V
     */
    void    Update(void)override;

    /*!
     *  @brief      �`��
     */
    void    Draw(void)override;

    /*!
     *  @brief      ���
     */
    void    Finalize(void)override;


private:
    aqua::CEffect3D     m_Effect;
    float               m_Rotate;
};
