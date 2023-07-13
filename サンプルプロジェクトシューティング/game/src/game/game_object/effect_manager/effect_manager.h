
/*!
 *  @file       effect_manager.h
 *  @brief      �G�t�F�N�g�Ǘ�
 *  @author     Kazuto Shimazaki
 *  @date       2023/06/19
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
  *  @date       2023/06/19
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
     *  @param[in]  rotate      ��]�l
     *  @param[in]  scale       �g�嗦
     */
    void        Create(EFFECT_ID id, const aqua::CVector3& position, float rotate = 0.0f, float scale = 5.0f);

    /*!
     *  @brief      �G�t�F�N�g�������|�C���^��n��
     *
     *  @param[in]  id          �G�t�F�N�gID
     *  @param[in]  position    �ʒu
     *  @param[in]  rotate      ��]�l
     *  @param[in]  scale       �g�嗦
     */
    aqua::CEffect3D* CreateGetEffect(EFFECT_ID id, const aqua::CVector3& position, float rotate = 0.0f, float scale = 5.0f);

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
    static const std::string    m_effect_file_names[];   // �G�t�F�N�g�t�@�C���p�X
};
