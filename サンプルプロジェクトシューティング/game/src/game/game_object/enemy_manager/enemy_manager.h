
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
    void        Initialize(CCSVReader* csv_r,CBulletManager* bm, CPlayer* player,CStageManager* st_m ,CRader* rader);

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
    void        Create(aqua::CVector3 pop_pos ,ENEMY_ID enemy_id);

    /*!
     *  @brief      ���
     */
    void        Finalize(void) override;

    /*!
     *  @brief      �I���m�F
     */
    bool        GetFinish(void) { return m_Finish; }

    /*!
     *  @brief      �G�I�o
     */
    CEnemy*     GetNearest(aqua::CVector3 player_pos);

    /*!
     *  @brief      �{�X�̕��ʐ���
     */
    CEnemy*     CreateBossParts(aqua::CVector3 pop_pos, ENEMY_ID enemy_id);

private:

    void        WaveChange(void);

    static const int m_max_wave;

    int             m_EnemyCount;
    int             m_WaveCount;
    bool            m_Finish;

    CCSVReader*     m_CSVReader;
    CPlayer*        m_Player;
    CBulletManager* m_BulletManagar;
    CStageManager*  m_StageManager;
    CRader*         m_Rader;
    std::vector<ENEMY_POP_LIST> m_PopList;
    std::vector<ENEMY_INFO> m_EnemyInfo;
};
