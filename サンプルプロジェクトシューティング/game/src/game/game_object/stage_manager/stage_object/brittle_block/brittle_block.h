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
#include "../normal_block/normal_block.h"

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


class CBrittleBlock : public IStageObject
{
public:

    /*
     *  @brief      �R���X�g���N�^
     */
    CBrittleBlock(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    ~CBrittleBlock(void) = default;

    /*!
     *  @brief      ������
     *
     *  @param[in]  id �X�e�[�W��̃}�b�v�`�b�vID
     */
    void        Initialize(const STAGE_OBJECT_ID& id, int x, int z)override;

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


    bool        CollisionCheck(aqua::CVector3 position, aqua::CVector3 destination,bool this_bullet)override;


private:

    void GoIn(void)override;
    void GoOut(void)override;

    void        Broken(void);

    int             m_Endurance;        // �ϋv�l

    CEffectManager* m_EfectManager;

};