/*!
 *  @file       unique_life.h
 *  @brief      ���ꃉ�C�t�o�[�N���X
 *  @author     Kazuto Shimazaki
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "../life_bar.h"

 /*!
  *  @class      CUniqueLifeBar
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/08/31
  *
  *  @version    1.0
  */
class CUniqueLifeBar
    : public CLifeBar
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent  �e�̃I�u�W�F�N�g
     */
    CUniqueLifeBar(aqua::IGameObject* parent);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CUniqueLifeBar(void) = default;

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      �X�V
     */
    void        Update(void)override;

    /*!
     *  @brief      ���C�t�o�[�v�Z����
     */
    void        CalcLifeBar(void)override;

private:



    std::string m_UnitName;     // ���j�b�g��
};
