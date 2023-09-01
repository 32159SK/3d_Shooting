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
class CLifeBar;

class IUnit : public aqua::IGameObject
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    IUnit(aqua::IGameObject* parent, const std::string& object_name , const std::string& category_name);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual ~IUnit(void) = default;

    /*
     *  @brief      ������
     */
    virtual void    Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, CStageManager* st_m, CBulletManager* bm);

    /*
     *  @brief      �X�V
     */
    virtual void    Update(void)override;

    /*
     *  @brief      �`��
     */
    virtual void    Draw(void)override;

    /*
     *  @brief      ���
     */
    virtual void    Finalize(void)override;

    /*
     *  @brief      ��e����
     */
    virtual bool    CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage);

    /*
     *  @brief      �r�[����e����
     */
    virtual bool    CheckHitBeam(UNIT_TYPE type, aqua::CCapsulePrimitive capsule, int damage);

    /*
     *  @brief      ���W�擾
     */
    aqua::CVector3  GetPosition(void) { return m_Position; }

    /*
     *  @brief      ���S�m�F
     */
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
    virtual int     GetMaxLife(void) { return m_MaxLife; }

    /*
     *  @brief      ���݃��C�t�̎擾
     */
    virtual int     GetLife(void) { return m_Life; }

    /*
     *  @brief      ���b�N�I���t���O�̎擾
     */
    bool            GetLockOnFlag(void) { return m_LockON; }

    /*
     *  @brief      �s���\�t���O�̎擾
     */
    bool            GetMoveFlag(void) { return m_MoveFlag; }

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

    float                m_Angle;        // �p�x

    float                m_Rotate;       // ������]�l

    UNIT_TYPE            m_UnitType;     // ���j�b�g����

    BULLET_TYPE          m_ShotBullet;   // ���e��

    aqua::CVector3       m_Position;     // ���W

    aqua::CVector3       m_Velocity;     // �ړ����x
    
    float                m_Speed;        // ����

    aqua::CColor         m_Color;        // �F

    aqua::CCubePrimitive m_Cube;         // ���j�b�g�̃R���C�_�[

    aqua::CModel         m_Model;        // ���f��


    aqua::CTimer         m_ShotCT;       // �ˌ��N�[���^�C��

    aqua::CTimer         m_BeamInterval; // �r�[���̃_���[�W�C���^�[�o��

    CLifeBar*            m_LifeBar;      // ���C�t�o�[

    CEffectManager*      m_EffectManager;// �G�t�F�N�g�Ǘ��N���X

    CSoundManager*       m_SoundManager; // �T�E���h�Ǘ��N���X

    CBulletManager*      m_BulletManager;// �e�Ǘ��N���X

    CStageManager*       m_StageManager; // �X�e�[�W�Ǘ��N���X
};