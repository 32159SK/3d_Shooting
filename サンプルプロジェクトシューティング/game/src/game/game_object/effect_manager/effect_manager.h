
/*!
 *  @file       effect_manager.h
 *  @brief      �G�t�F�N�g�Ǘ�
 *  @author     Kazuto Shimazaki
 *  @date       2021/12/02
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "effect\effect.h"
#include "effect\effect_id.h"

 /*!
  *  @class      CEffectManager
  *
  *  @brief      �G�t�F�N�g�Ǘ��N���X
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/5/23
  *
  *  @version    1.0
  */
class CEffectManager
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     */
    CEffectManager(aqua::IGameObject* parent);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CEffectManager(void) = default;

    /*!
     *  @brief      �G�t�F�N�g����
     *
     *  @param[in]  id          �G�t�F�N�gID
     *  @param[in]  position    �ʒu
     */
    void        Create(EFFECT_ID id, const aqua::CVector3& position, float rotate = 0.0f);

    /*!
     *  @brief      �X�V
     */
    void        Update(void)override;

    /*!
     *  @brief      �`��
     */
    void        Draw(void)override;

    /*!
     *  @brief      ���
     */
    void        Finalize(void)override;

private:
    static const std::string    m_effect_file_names[];   // �T�E���h�t�@�C���p�X
};
