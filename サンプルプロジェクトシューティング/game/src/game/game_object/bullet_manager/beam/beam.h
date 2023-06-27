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

class CBeam : public aqua::IGameObject
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    CBeam(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    ~CBeam(void) = default;

    /*
     *  @brief      ������
     */
    void            Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 dir, IUnit* user, CEffectManager* em);

    /*
     *  @brief      �`��
     */
    void            Draw(void)override;

    /*
     *  @brief      �X�V
     */
    void            Update(void)override;

    /*
     *  @brief      �X�V
     */
    void            Finalize(void)override;

    aqua::CCapsulePrimitive GetCapsule(void) { return m_Capsule; }


    /*
     *  @brief      �����擾
     */
    UNIT_TYPE       GetAttri(void) { return m_Attri; }

    /*
     *  @brief      �_���[�W�擾
     */
    int             GetDamage(void) { return m_Damage; }

    bool            GetDamageFlag(void) { return m_DamageFlag; }

private:

    void            Charge(void);

    void            Firing(void);

    void            Destroy(void);


    enum class BEAM_STATE
    {
        CHARGE, // ����
        FIRING, // ����
        DESTROY // ����
    };

    static const float      m_max_range;    // �˒�����

    static const float      m_charge_time;  // ��������

    int                     m_Damage;       // �_���[�W��

    float                   m_Rotate;       //! ������]�p�x

    float                   m_Radius;       //! ���a

    bool                    m_DamageFlag;   //

    aqua::CVector3          m_Dir;          //

    aqua::CVector3          m_StartPos;     //

    aqua::CVector3          m_EndPos;       //

    UNIT_TYPE               m_Attri;        // ����

    BEAM_STATE              m_BeamState;    // 

    aqua::CCapsulePrimitive m_Capsule;      // 

    aqua::CTimer            m_Timer;
    
    aqua::CEffect3D*        m_Effect;

    CEffectManager*         m_EffectManager;

    IUnit*                  m_User;         // 
};