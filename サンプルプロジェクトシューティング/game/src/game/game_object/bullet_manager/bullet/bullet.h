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
#include "../../game_object.h"
#include "../../unit/unit.h"

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
    virtual void    Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri,aqua::CVector3 pop_pos,aqua::CVector3 front,IUnit* user);

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

    /*
     *  @brief      �e�̍��W�擾
     */
    aqua::CVector3  GetPosition(void) { return m_Position; }

    /*
     *  @brief      �e�̐i�s���W�擾
     */
    aqua::CVector3  GetDestination(void) { return m_Position + m_Velocity * 1.5f; }

    /*
     *  @brief      �q�b�g����
     */
    void            Hit(void);


    /*
     *  @brief      �X�e�[�W�I�u�W�F�N�g�q�b�g����
     */
    virtual void    StageObjectHit(aqua::CCubePrimitive::COLL_DIRE c_dire);


protected:


    int                     m_Damage;       // �_���[�W��

    float                   m_Radius;       // ���a

    float                   m_Range;        // �˒�����

        //! ������]�p�x
    float                   m_Rotate;

    aqua::CVector3          m_Dir;

    aqua::CVector3          m_Velocity;     // �e�̑��x

    aqua::CVector3          m_StartPos;

    float                   m_Speed;        // �e�̑���

    UNIT_TYPE               m_Attri;        // ����

    aqua::CVector3          m_Position;     // ���W

    aqua::CColor            m_Color;        // �F

    aqua::CSpherePrimitive  m_Sphere;       // 

    IUnit*                  m_Unit;
};