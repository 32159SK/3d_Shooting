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
    void    Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri,aqua::CVector3 pop_pos,aqua::CVector3 front,IUnit* user);

    /*
     *  @brief      �`��
     */
    virtual void    Draw(void)override;

    /*
     *  @brief      �X�V
     */
    virtual void    Update(void)override;


    /*
     *  @brief      �����擾
     */
    UNIT_TYPE       GetAttri(void) { return m_Attri; }

    /*
     *  @brief      �_���[�W�擾
     */
    int             GetDamage(void) { return m_Damage; }

    /*
     *  @brief      �e�̋��擾
     */
    aqua::CSpherePrimitive GetSphere(void) { return m_Sphere; }

    aqua::CVector3  GetPosition(void) { return m_Position; }

    void            Hit(void);

protected:

    int                     m_Damage;       // �_���[�W��

    float                   m_Radius;       // ���a

    aqua::CVector3          m_Dir;

    aqua::CVector3          m_Velocity;     // �e�̑��x

    float                   m_Speed;        // �e�̑���

    UNIT_TYPE               m_Attri;        // ����

    aqua::CVector3          m_Position;     // ���W

    aqua::CColor            m_Color;        // �F

    aqua::CSpherePrimitive  m_Sphere;       // 

    IUnit*                  m_Unit;
};