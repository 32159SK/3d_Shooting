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
#include "../bullet.h"


class CReflectionBullet : public IBullet
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    CReflectionBullet(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual ~CReflectionBullet(void) = default;

    /*
     *  @brief      ������
     */
    void    Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user)override;


    /*
     *  @brief      �X�V
     */
    void    Update(void)override;

    void    Draw(void)override;

    void    Finalize(void)override;

    void    StageObjectHit(aqua::CCubePrimitive::COLL_DIRE c_dire)override;
private:

    static const int m_max_reflect_count = 4;

    int             m_ReflectCount;

    aqua::CModel    m_Model;

    aqua::CCubePrimitive::COLL_DIRE m_CollDire;
};