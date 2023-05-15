
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
    CBulletManager(aqua::IGameObject* parent);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CBulletManager(void) = default;

    /*!
     *  @brief      ������
     */
    void        Initialize(CCSVReader* csv_r);

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
    void        Create(aqua::CVector3 shot_pos, aqua::CVector3 shot_front, UNIT_TYPE unit_type, BULLET_TYPE bullet_type, IUnit* user);

    /*!
     *  @brief      ���
     */
    void        Finalize(void) override;

    /*!
     *  @brief      �G�Z�b�^�[
     */
    void        SetEnemy(CEnemy* enemy) { m_Enemy.push_back(enemy); }

    /*!
     *  @brief      ���@�Z�b�^�[
     */
    void        SetPlayer(CPlayer* player) { m_Player = player; }

    void        EnemyReset(void) { m_Enemy.clear(); }
private:

    void        CheakHit(void);

    CCSVReader*             m_CSVReader;
    CPlayer*                m_Player;
    std::vector<BULLET_INFO> m_BulletInfo;
    std::vector<CEnemy*>    m_Enemy;
};
