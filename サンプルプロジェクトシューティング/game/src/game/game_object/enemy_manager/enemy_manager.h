
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
#include "enemy/enemy_id.h"
#include "../ui_component/rader/rader.h"

 /*!
  *  @brief      �G�l�~�[�̃|�b�v�e�[�u��
  */
struct ENEMY_POP_LIST
{
    int   wave = 1;
    ENEMY_ID pop_e_id = ENEMY_ID::MOB;
};

/*!
 *  @brief      �G�l�~�[�̏��
 */
struct ENEMY_INFO
{
    ENEMY_ID id = ENEMY_ID::MOB;
    int   life = 1;
    float width = 5.0f;
    float height = 5.0f;
    float depth = 5.0f;
    float speed = 1.0f;
    float shot_ct = 1.5f;
};


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
    void        Initialize(CBulletManager* bm, CPlayer* player,CStageManager* st_m ,CRader* rader);

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
     *  @brief      �G�I�o
     */
    CEnemy*     GetNearest(aqua::CVector3 player_pos);

    /*!
     *  @brief      �{�X�̕��ʐ���
     */
    CEnemy*     CreateBossParts(aqua::CVector3 pop_pos, ENEMY_ID enemy_id);

private:

    void        EnemyDataLoad(void);

    void        WaveChange(void);

    static const int m_max_wave;
    static const int m_heal_value;      // wave�N���A���̉񕜒l
    static const std::string m_enemy_info_path;
    static const std::string m_pop_list_path;

    int             m_EnemyCount;       // 
    int             m_WaveCount;        // 
    bool            m_Finish;           // 

    CPlayer*        m_Player;
    CBulletManager* m_BulletManagar;
    CStageManager*  m_StageManager;
    CRader*         m_Rader;
    std::vector<ENEMY_POP_LIST> m_PopList;
    std::vector<ENEMY_INFO> m_EnemyInfo;
};
