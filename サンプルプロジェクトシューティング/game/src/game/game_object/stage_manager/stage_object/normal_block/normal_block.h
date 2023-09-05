/*
 *  @file       stage_object.h
 *  @brief      �X�e�[�W�I�u�W�F�N�g
 *  @author
 *  @date
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "../stage_object.h"

 /*
  *  @class      IStageObject
  *
  *  @brief      �X�e�[�W�I�u�W�F�N�g�N���X
  *
  *  @author     Kazuya Maruyama
  *
  *  @date       2019/11/16
  *
  *  @since      1.0
  */


class CNormalBlock : public IStageObject
{
public:

    /*
     *  @brief      �R���X�g���N�^
     */
    CNormalBlock(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    ~CNormalBlock(void) = default;

    /*!
     *  @brief      ������
     *
     *  @param[in]  id �X�e�[�W��̃}�b�v�`�b�vID
     */
    void        Initialize(const STAGE_OBJECT_ID& id, int x, int z)override;
};