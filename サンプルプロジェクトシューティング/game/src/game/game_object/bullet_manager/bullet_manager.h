
/*!
 *  @file       enemy_manager.h
 *  @brief      �G�l�~�[�Ǘ�
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/18
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "bullet/bullet.h"
#include "bullet/bullet_type.h"
 /*!
  *  @class      CBulletManager
  *
  *  @brief      �G�l�~�[�Ǘ��N���X
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/04/18
  *
  *  @version    1.0
  */


class CBulletManager
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     */
    CBulletManager(aqua::IGameObject* parent, const std::string& name);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CBulletManager(void) = default;

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
     *  @brief      �e�̐���
     */
    void        Create(aqua::CVector3 shot_pos,UNIT_TYPE unit_type, BULLET_TYPE bullet_type);

    /*!
     *  @brief      ���
     */
    void        Finalize(void) override;
private:

    BULLET_INFO     m_BulletInfo;

};
