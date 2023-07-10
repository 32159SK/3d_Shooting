/*
 *  @file       stage_manager.h
 *  @brief      �X�e�[�W�Ǘ��N���X
 *  @author
 *  @date       2023/05/12
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "stage_object/stage_object.h"
#include "stage_object/stage_object_id.h"


class CPlayer;

/*
 *  @class      CStageManager
 *
 *  @brief      �X�e�[�W�Ǘ��N���X
 *
 *  @author     
 *
 *  @date       2023/05/12
 *
 *  @since      1.0
 */
class CStageManager : public aqua::IGameObject
{
public:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CStageManager(aqua::IGameObject* parent);


    /*
     *  @brief      �f�X�g���N�^
     */
    ~CStageManager(void) = default;

    /*
     *  @brief      ������
     */
    void        Initialize(void)override;

    /*
     *  @brief      �X�V
     */
    void        Update(void)override;

    /*
     *  @brief      �`��
     */
    void        Draw(void)override;

    /*
     *  @brief      ���
     */
    void        Finalize(void)override;

    /*
     *  @brief      �E�F�[�u�؂�ւ�
     */
    void        WaveChange(int wave);

    /*
     *  @brief      ���
     */
    bool        StageObjectCollision(aqua::CVector3 position, aqua::CVector3 destination, bool this_bullet);

    /*
     *  @brief      �����擾
     */
    aqua::CCubePrimitive::COLL_DIRE GetCollDire(void) { return m_LastCollObject->GetCollDire(); }

    /*
     *  @brief      ���
     */
    int         GetEnemyCount(void) { return m_EnemyCount; }

    /*
     *  @brief      �G�o�����W
     */
    aqua::CVector3 GetEnemyPopPos(int pos_number) { return m_EnemyPopPos[pos_number]; }

private:

    void        StageLoad(void);

    void        Create(void);

    static const float              m_default_size;         //!< �W���T�C�Y
    static const std::string        m_file_path;
    struct POS_NUMBER
    {
        int z = 0;
        int x = 0;
    };

    int                             m_Stage[21][21];

    int                             m_WaveCount;

    int                             m_EnemyCount;

    std::vector<aqua::CVector3>     m_EnemyPopPos;

    CPlayer*                        m_Player;

    IStageObject*                   m_LastCollObject;   // �Ō�ɐڐG�����I�u�W�F�N�g
};
