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
#include "../unit/unit.h"

class CEnemyManager;

class CPlayer : public IUnit
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    CPlayer(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual         ~CPlayer(void) = default;

    /*
     *  @brief      ������
     */
    void            Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color,CBulletManager* bm)override;

    /*
     *  @brief      �X�V
     */
    virtual void    Update(void)override;

    void Draw(void) override;

    /*
     *  @brief      �X�V
     */
    bool            CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)override;

private:

    /*
     *  @brief      �ˌ�
     */
    void            Shot(void)override;

    /*
     *  @brief      �ړ�����
     */
    void            Move(void)override;

    /*
     *  @brief      ���S
     */
    void            Dead(void)override;

    CEnemyManager*  m_EnemyManager;
};