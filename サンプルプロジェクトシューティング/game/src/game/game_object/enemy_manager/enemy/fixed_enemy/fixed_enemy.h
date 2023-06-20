/*
 *  @file       unit.h
 *  @brief      ���j�b�g����
 *  @author     Kazuto Shimazaki
 *  @date       2022/06/20
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../enemy.h"

class CFixedEnemy : public CEnemy
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    CFixedEnemy(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual ~CFixedEnemy(void) = default;

    /*
     *  @brief      ������
     */
    void    Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m, CBulletManager* bm)override;

    /*
     *  @brief      �X�V
     */
    void    Update(void)override;

    /*
     *  @brief      �`��
     */
    void    Draw(void)override;

    /*
     *  @brief      ���
     */
    void    Finalize(void)override;


private:

    void            Shot(void)override;

    void            Move(void)override;

    static const float   m_capture_range;        // ���m�͈�

    bool            m_Capture;      // �ߑ��t���O

    aqua::CModel    m_Model;

};