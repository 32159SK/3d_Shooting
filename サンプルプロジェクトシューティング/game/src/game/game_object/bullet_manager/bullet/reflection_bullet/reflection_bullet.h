/*
 *  @file       reflect_bullet.h
 *  @brief      ���˒e
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
    void    Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user, CEffectManager* em)override;

    /*
     *  @brief      �X�e�[�W�I�u�W�F�N�g�q�b�g����
     */
    void    StageObjectHit(aqua::CCubePrimitive::COLL_DIRE c_dire)override;
private:

    static const int m_max_reflect_count = 3;   // �ő唽�ˉ�

    int             m_ReflectCount;             // ���ˉ񐔂̃J�E���g

};