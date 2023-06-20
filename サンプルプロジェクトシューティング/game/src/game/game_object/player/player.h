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
#include "../unit/unit.h"

class CEnemyManager;
class CEnemy;
class CLockOnMarker;

class CPlayer : public IUnit
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    CPlayer(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual         ~CPlayer(void) = default;

    /*
     *  @brief      ������
     */
    void            Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m,CBulletManager* bm)override;

    /*
     *  @brief      �X�V
     */
    void            Update(void)override;

    /*
     *  @brief      �`��
     */
    void            Draw(void) override;

    void            Finalize(void)override;

    /*
     *  @brief      ��e�m�F
     */
    bool            CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)override;

    /*
     *  @brief      �����O�̍��W�擾
     */
    aqua::CVector3  GetAgoPos(void) { return m_AgoPosition; }

    /*
     *  @brief      ���~�ߊm�F
     */
    bool            GetTimeStop(void) { return m_TimeStop; }

    /*
     *  @brief      �G�Ǘ��N���X�Z�b�^�[
     */
    void            SetEnemyManager(CEnemyManager* em) { m_EnemyManager = em; }

    bool            GetLockOnFlag(void) { return m_LockON; }

private:

    /*
     *  @brief      �ˌ�
     */
    void            Shot(void)override;

    /*
     *  @brief      �ړ�����
     */
    void            Move(void)override;

    /*
     *  @brief      ���S����
     */
    void            Damage(int damage)override;

    /*
     *  @brief      ���S
     */
    void            Dead(void)override;

    /*
     *  @brief      ���b�N�I��
     */
    void            LockOn(void);

    /*
     *  @brief      �U�E���[���h
     */
    void            TheWorld(void);

    static const float m_chage_shotCT;  // 
    static const float m_ago_pos_time;  // 
    static const float m_the_world_time;// �����~�߂Ă����鎞��
    static const float m_the_world_CT;  // �Ăю����~�߂���܂ł̎���
    static const float m_lock_range;

    bool            m_Invincible;       // ���G

    bool            m_TimeStop;         // ���~�ߊm�F

    bool            m_LockON;           // ���b�N�I���m�F

    aqua::CVector3  m_AgoPosition;       //

    aqua::CModel    m_Model;            // ���@�̃��f��

    aqua::CLabel    m_DrawBT;           // 

    aqua::CTimer    m_ChageCT;          //

    aqua::CTimer    m_AgoPosTimer;      // 

    aqua::CTimer    m_InvincibleTimer;  //

    aqua::CTimer    m_TheWorldTimer;    // 

    aqua::CTimer    m_LockonTimer;      // �A����m_LockON���؂�ւ��̂�h�~

    CEnemyManager*  m_EnemyManager;     //

    CEnemy*         m_Enemy;

    CLockOnMarker*  m_LockOnMarker;
};