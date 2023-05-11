
/*!
 *  @file       stage.h
 *  @brief      ��
 *  @author     Kazuto Shimazaki
 *  @date       2023/05/11
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"

 /*!
  *  @class      CFloor
  *
  *  @brief      �X�e�[�W�N���X
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/05/11
  *
  *  @version    1.0
  */
class CFloor final
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent  �e�̃I�u�W�F�N�g
     */
    CFloor(aqua::IGameObject* parent);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CFloor(void) = default;

    /*!
     *  @brief      ������
     */
    void        Initialize(void) override;

    /*!
     *  @brief      �X�V
     */
    void        Update(void) override;

    /*!
     *  @brief      �`��
     */
    void        Draw(void) override;

    /*!
     *  @brief      ���
     */
    void        Finalize(void) override;

private:
    aqua::CModel            m_Floor;
};
