
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
     *  @brief      �`���[�g���A�����[�h
     */
    void        SetTutorial(void) { m_TutorialMode = true; }

    /*!
     *  @brief      �G�I�o
     */
    CEnemy*     GetNearest(aqua::CVector3 player_pos);

    /*!
     *  @brief      �{�X�̕��ʐ���
     */
    CEnemy*     CreateBossParts(aqua::CVector3 pop_pos, ENEMY_ID enemy_id);

private:
    /*!
     *  @brief      �f�[�^�ǂݍ���
     */
    void        EnemyDataLoad(void);
    /*!
     *  @brief      �E�F�[�u�؂�ւ�
     */
    void        WaveChange(void);

    static const int m_max_wave;                // �ő�E�F�[�u��
    static const int m_heal_value;              // wave�N���A���̉񕜒l
    static const std::string m_enemy_info_path; // �G�l�~�[���̃t�@�C���p�X
    static const std::string m_pop_list_path;   // �o�����X�g�̃t�@�C���p�X

    int             m_EnemyCount;               // �G���J�E���g
    int             m_WaveCount;                // �E�F�[�u���̃J�E���g
    bool            m_TutorialMode;             // �`���[�g���A�����[�h�t���O
    bool            m_Finish;                   // �I������

    CPlayer*        m_Player;                   // �v���C���[�̃|�C���^
    CBulletManager* m_BulletManagar;            // �e�Ǘ��N���X�̃|�C���^
    CStageManager*  m_StageManager;             // �X�e�[�W�Ǘ��N���X�̃|�C���^
    CRader*         m_Rader;                    // ���[�_�[�N���X�̃|�C���^
    std::vector<ENEMY_POP_LIST> m_PopList;      // �o�����X�g
    std::vector<ENEMY_INFO> m_EnemyInfo;        // �G�l�~�[��񃊃X�g
};
