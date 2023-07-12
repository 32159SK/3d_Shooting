/*!
 *  @file       life_bar.h
 *  @brief
 *  @brief
 *  @author     Kazuto Shimazaki
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "../ui_component.h"

 /*!
  *  @class      CLifeBar
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/06/05
  *
  *  @version    1.0
  */
class CLockOnMarker
    : public IUIComponent
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent  �e�̃I�u�W�F�N�g
     */
    CLockOnMarker(aqua::IGameObject* parent);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CLockOnMarker(void) = default;

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      �X�V
     */
    void        Update(void)override;

    /*!
     *  @brief      �`��
     */
    void        Draw(void) override;

    /*!
     *  @brief      ���
     */
    void        Finalize(void) override;

    void        SetTarget(IUnit* target) { m_Target = target; }

private:

    aqua::CSprite  m_Sprite;   // ���b�N�I���摜�X�v���C�g

    aqua::CCamera* m_Camera;   // �J�����̃|�C���^�e��

    IUnit*         m_User;     // ���b�N�I���g�p��

    IUnit*         m_Target;   // ���b�N�I���Ώ�

    CGameMain*     m_GameMain; // �Q�[�����C���V�[���̃|�C���^�e��
};
