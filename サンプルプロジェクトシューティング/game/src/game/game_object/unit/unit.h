/*
 *  @file       unit.h
 *  @brief      ���j�b�g����
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/14
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "unit_type.h"
#include "../bullet_manager/bullet/bullet_info.h"

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
    virtual void    Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, CStageManager* st_m, CBulletManager* bm);

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
    virtual bool    CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage);

    /*
     *  @brief      �r�[����e����
     */
    virtual bool    CheckHitBeam(UNIT_TYPE type, aqua::CCapsulePrimitive capsule, int damage);

    aqua::CVector3  GetPosition(void) { return m_Position; }

    bool            GetDead(void);

    /*
     *  @brief      ���ʍ��W�̎擾
     */
    aqua::CVector2  GetPosVector2(void) { return aqua::CVector2(m_Position.x, m_Position.z); }

    /*
     *  @brief      ��]�l�̎擾
     */
    float           GetRotate(void) { return m_Rotate; }
    /*
     *  @brief      �ő僉�C�t�̎擾
     */
    int             GetMaxLife(void) { return m_MaxLife; }
    /*
     *  @brief      ���݃��C�t�̎擾
     */
    int             GetLife(void) { return m_Life; }

    /*
     *  @brief      ���b�N�I���t���O�̎擾
     */
    bool            GetLockOnFlag(void) { return m_LockON; }

    /*
     *  @brief      �s���\�t���O�̃Z�b�^�[
     */
    virtual void    SetMoveFlag(bool flag) { m_MoveFlag = flag; }


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
    virtual void    Damage(int damage);

     /*
      *  @brief      ���S
      */
    virtual void    Dead(void);

    static const float   m_beam_damage_interval;

    int                  m_MaxLife;

    int                  m_Life;         // ���C�t

    bool                 m_DeadFlag;     // ���S�t���O

    bool                 m_MoveFlag;     // �s���\�t���O

    bool                 m_LockON;       // ���b�N�I���t���O

    float                m_Width;        // ��

    float                m_Height;       // ����

    float                m_Depth;        // ���s

    float                m_Angle;

    float                m_Rotate;       //! ������]�p�x

    UNIT_TYPE            m_UnitType;     // ���j�b�g����

    BULLET_TYPE          m_ShotBullet;

    aqua::CVector3       m_Position;     // ���W

    aqua::CVector3       m_Velocity;     // �ړ����x
    
    float                m_Speed;        // ����

    aqua::CColor         m_Color;        // �F

    aqua::CCubePrimitive m_Cube;         // ���j�b�g�̃R���C�_�[

    aqua::CTimer         m_ShotCT;

    aqua::CTimer         m_BeamInterval;

    CEffectManager*      m_EffectManager;

    CBulletManager*      m_BulletManager;

    CStageManager*       m_StageManager;
};