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

class CBulletManager;
class IBullet;

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
    virtual void    Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CBulletManager* bm);

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
    virtual bool    CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere,int damage);

    aqua::CVector3  GetPosition(void) { return m_Position; }

    bool            GetDead(void) { return m_DeadFlag; }

    /*
     *  @brief      ���ʍ��W�̎擾
     */
    aqua::CVector2  GetPosVector2(void) { return aqua::CVector2(m_Position.x, m_Position.z); }

    /*
     *  @brief      ��]�l�̎擾
     */
    float           GetRotate(void) { return m_Rotate; }

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
    void            Damage(int damage);

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

    //! ������]�p�x
    float                m_Rotate;

    UNIT_TYPE            m_UnitType;     // ���j�b�g����

    BULLET_TYPE          m_ShotBullet;

    aqua::CVector3       m_Position;     // ���W

    aqua::CVector3       m_Velocity;     // �ړ����x
    
    float                m_Speed;        // ����

    aqua::CColor         m_Color;        // �F

    aqua::CCubePrimitive m_Cube;         // ���@

    aqua::CLinePrimitive3D m_Line;


    aqua::CTimer         m_ShotCT;

    CBulletManager*      m_BulletManager;
};