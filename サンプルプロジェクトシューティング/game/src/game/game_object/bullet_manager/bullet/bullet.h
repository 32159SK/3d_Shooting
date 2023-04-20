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
#include "../../unit/unit.h"
#include "bullet_type.h"

class IBullet : public aqua::IGameObject
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    IBullet(aqua::IGameObject* parent, const std::string& object_name);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual ~IBullet(void) = default;

    /*
     *  @brief      ������
     */
    void    Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri,aqua::CVector3 pop_pos);

    /*
     *  @brief      �`��
     */
    virtual void    Draw(void)override;

    /*
     *  @brief      �X�V
     */
    virtual void    Update(void)override;

    /*
     *  @brief      ���j�b�g�Z�b�^�[
     */
    void            SetUnit(IUnit* unit) { m_Unit = unit; }

    /*
     *  @brief      �����擾
     */
    UNIT_TYPE       GetAttri(void) { return m_Attri; }

protected:

    void            Hit(void);

    int                     m_Damage;       // �_���[�W��

    float                   m_Radius;       // ���a

    UNIT_TYPE               m_Attri;        // ����

    aqua::CVector3          m_Position;     // ���W

    aqua::CColor            m_Color;        // �F

    aqua::CSpherePrimitive  m_Sphere;       // 

    IUnit*                  m_Unit;
};