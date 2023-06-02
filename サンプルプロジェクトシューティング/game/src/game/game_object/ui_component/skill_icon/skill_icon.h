/*!
 *  @file       rader.h
 *  @brief      ���[�_�[�N���X
 *  @brief      UI�R���|�[�l���g
 *  @author     Kazuto Shimazaki
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "../ui_component.h"

 /*!
  *  @class      CRader
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/06/02
  *
  *  @version    1.0
  */
class CSkillIcon
    : public IUIComponent
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent  �e�̃I�u�W�F�N�g
     */
    CSkillIcon(aqua::IGameObject* parent);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSkillIcon(void) = default;

    /*!
     *  @brief      ������
     */
    void        Initialize(CPlayer* player);

    void        Update(void)override;

    /*!
     *  @brief      �`��
     */
    void        Draw(void) override;

    /*!
     *  @brief      ���
     */
    void        Finalize(void) override;

    void        SetEnemy(CEnemy* enemy);

private:

    /*!
     *  @brief      ���[�_�[���ł̕\�����W�ϊ�
     */
    aqua::CVector2                  SetRaderPos(aqua::CVector2 pos);

    static const std::string        m_unit_path;

    int                             m_EnemyCount;

    aqua::CSprite                   m_RaderSprite;  // ���[�_�[�摜
    aqua::CSprite                   m_PlayerSprite; // ���[�_�[���̎��@�\��
    std::vector<aqua::CSprite>      m_EnemySprite;  // ""�̃G�l�~�[�\��

    aqua::CVector2                  m_RaderSize;    // ���[�_�[�摜�̃T�C�Y

    CPlayer* m_Player;       // �v���C���[
};
