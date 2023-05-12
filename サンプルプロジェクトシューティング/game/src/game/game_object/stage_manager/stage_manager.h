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
    void        Initialize(void);

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


private:



};
