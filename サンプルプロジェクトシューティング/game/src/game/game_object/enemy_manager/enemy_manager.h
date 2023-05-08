
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
#include "enemy/enemy.h"
#include "../ui_component/rader/rader.h"

 /*!
  *  @class      CEnemyManager
  *
  *  @brief      �G�l�~�[�Ǘ��N���X
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/04/18
  *
  *  @version    1.0
  */
class CEnemyManager
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     */
    CEnemyManager(aqua::IGameObject* parent);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CEnemyManager(void) = default;

    /*!
     *  @brief      ������
     */
    void        Initialize(CBulletManager* bm, CPlayer* player, CRader* rader);

    /*!
     *  @brief      �X�V
     */
    void        Update(void) override;

    /*!
     *  @brief      �`��
     */
    void        Draw(void) override;

    /*!
     *  @brief      �G�l�~�[�̐���
     */
    void        Create(aqua::CVector3 pop_pos, float wid, float hei,float dep,aqua::CColor color);

    /*!
     *  @brief      ���
     */
    void        Finalize(void) override;



private:


    int             m_EnemyCount;

    CPlayer*        m_Player;
    CBulletManager* m_BulletManagar;
    CRader*         m_Rader;
};
