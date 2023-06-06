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

    void        SetEnemy(CEnemy* enemy) { m_LockOnEnemy = enemy; }

private:


    aqua::CSprite  m_Sprite;   // 

    aqua::CCamera* m_Camera;   // �J�����̃|�C���^�e��

    CPlayer*       m_Player;

    CEnemy*        m_LockOnEnemy;

    CGameMain*     m_GameMain; // �Q�[�����C���V�[���̃|�C���^�e��
};
