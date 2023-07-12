/*
 *  @file       beam.h
 *  @brief      ���j�b�g����
 *  @author     Kazuto Shimazaki
 *  @date       2023/06/26
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
     *  @brief      �����蔻��p�̃J�v�Z���擾
     */
    aqua::CCapsulePrimitive GetCapsule(void) { return m_Capsule; }


    /*
     *  @brief      �����擾
     */
    UNIT_TYPE       GetAttri(void) { return m_Attri; }

    /*
     *  @brief      �_���[�W�擾
     */
    int             GetDamage(void) { return m_Damage; }

    /*
     *  @brief      �_���[�W�t���O�̎擾
     */
    bool            GetDamageFlag(void) { return m_DamageFlag; }

    /*
     *  @brief      �I���t���O�̎擾
     */
    bool            GetFinishFlag(void) { return m_Finished; }

private:
    /*
     *  @brief      �`���[�W
     */
    void            Charge(void);

    /*
     *  @brief      ����
     */
    void            Firing(void);

    /*
     *  @brief      ����
     */
    void            Destroy(void);

    /*
     *  @brief      �r�[���̏��
     */
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

    bool                    m_DamageFlag;   // �_���[�W����

    bool                    m_Finished;     // �I��

    aqua::CVector3          m_Dir;          // ����

    aqua::CVector3          m_StartPos;     // �n�_

    aqua::CVector3          m_EndPos;       // �I�_

    UNIT_TYPE               m_Attri;        // ����

    BEAM_STATE              m_BeamState;    // ���݂̃r�[���̏��

    aqua::CCapsulePrimitive m_Capsule;      // �����蔻��p�̃J�v�Z���N���X

    aqua::CLinePrimitive3D  m_PredictionLine;// �\����

    aqua::CTimer            m_Timer;        // �^�C�}�[
    
    aqua::CEffect3D*        m_Effect;       // �G�t�F�N�g�̃|�C���^�e��

    CEffectManager*         m_EffectManager;// �G�t�F�N�g�Ǘ��N���X�̃|�C���^�e��

    IUnit*                  m_User;         // �g�p��
};