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

#include"unit_type.h"

class IUnit : public aqua::IGameObject
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    IUnit(aqua::IGameObject* parent, const std::string& object_name);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual ~IUnit(void) = default;

    /*
     *  @brief      ������
     */
    virtual void    Initialize(void) override;

    /*
     *  @brief      �`��
     */
    virtual void    Draw(void)override;

    /*
     *  @brief      �X�V
     */
    virtual void    Update(void)override;

    /*
     *  @brief      ��e����
     */
    virtual bool    CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive shot);

protected:

    /*
     *  @brief      �ˌ�
     */
    virtual void    Shot(void);

    /*
     *  @brief      �ړ�����
     */
    virtual void    Move(void);

    /*
     *  @brief      �_���[�W
     */
    void            Damage(void);

     /*
      *  @brief      ���S
      */
    virtual void    Dead(void);

    static const int     m_max_life;     // ���C�t���

    int                  m_Life;         // ���C�t

    bool                 m_DeadFlag;     // ���S�t���O

    float                m_Width;        // ��

    float                m_Height;       // ����

    float                m_Depth;        // ���s

    UNIT_TYPE            m_UnitType;     // ���j�b�g����

    aqua::CVector3       m_Position;     // ���W

    aqua::CColor         m_Color;        // �F

    aqua::CCubePrimitive m_Cube;        // ���@
};