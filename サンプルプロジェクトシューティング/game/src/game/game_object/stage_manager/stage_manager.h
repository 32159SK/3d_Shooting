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
    void        Initialize(CCSVReader* csv_reader);

    /*
     *  @brief      �X�V
     */
    void        Update(void);

    /*
     *  @brief      �`��
     */
    void        Draw(void);

    /*
     *  @brief      ���
     */
    void        Finalize(void);


    void        WaveChange(int wave);

    bool        StageObjectCollision(aqua::CVector3 position, aqua::CVector3 destination);

private:
    void        Create(void);

    static const float              m_default_size;         //!< �W���T�C�Y

    struct POS_NUMBER
    {
        int z = 0;
        int x = 0;
    };

    int                             m_Stage[4][10][10];

    int                             m_WaveCount;

    POS_NUMBER                      m_SwichPoint[4];

    CCSVReader* m_CSVReader;
};
