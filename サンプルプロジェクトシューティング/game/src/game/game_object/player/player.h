/*
 *  @file       unit.h
 *  @brief      ���j�b�g����
 *  @author     Kazuto Shimazaki
 *  @date       2023/05/20
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
    void            Initialize(aqua::CVector3 pop_pos, CStageManager* st_m, CBulletManager* bm);

    /*
     *  @brief      �X�V
     */
    void            Update(void)override;

    /*
     *  @brief      �`��
     */
    void            Draw(void) override;

    /*
     *  @brief      ���
     */
    void            Finalize(void)override;

    /*
     *  @brief      ��e�m�F
     */
    bool            CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)override;

    /*
     *  @brief      ��e�m�F
     */
    bool            CheckHitBeam(UNIT_TYPE type, aqua::CCapsulePrimitive capsule, int damage)override;

    /*
     *  @brief      �����O�̍��W�擾
     */
    aqua::CVector3  GetAgoPos(void) { return m_AgoPosition; }


    /*
     *  @brief      �G�Ǘ��N���X�Z�b�^�[
     */
    void            SetEnemyManager(CEnemyManager* em) { m_EnemyManager = em; }

    /*
     *  @brief      ���W�̃Z�b�^�[
     */
    void            SetPosition(aqua::CVector3 pos) { m_Position = pos; }

    /*
     *  @brief      ��
     */
    void            LifeHeal(int heal_value);
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
     *  @brief      ���S
     */
    void            Dead(void)override;

    /*
     *  @brief      ����
     */
    void            Operation(void);

    /*
     *  @brief      �}�E�X�Ǐ]�ɂ���]
     */
    void            MouseTrack(void);

    /*
     *  @brief      ���b�N�I��
     */
    void            LockOn(void);

    static const float m_change_shotCT;  // �e��؂�ւ��Ԋu

    static const float m_shot_ct;       // �ˌ��Ԋu
    
    static const float m_ago_pos_time;  // ���W�����Ԋu

    static const float m_invincible_time;// ���G����

    static const float m_flash_time;// �_�Ő؂�ւ�����

    static const float m_lock_range;    // ���b�N�I���͈�

    static const float m_width;         // ���萔

    static const float m_height;        // �����萔

    static const float m_depth;         // ���s�萔

    static const float m_speed;         // �ړ����x�萔


    static const float m_font_size;     // �t�H���g�T�C�Y

    static const int   m_max_life;      // ���C�t�̍ő�l

    bool            m_Invincible;       // ���G

    aqua::CVector3  m_AgoPosition;      // �ǔ����W

    aqua::CSprite   m_BulletIcon[4];    // �e��A�C�R��

    aqua::CTimer    m_ChangeCT;         // �e��؂�ւ��^�C�}�[

    aqua::CTimer    m_AgoPosTimer;      // �ǔ����W�����Ԋu�p�̃^�C�}�[

    aqua::CTimer    m_InvincibleTimer;  // ���G���ԃ^�C�}�[

    aqua::CTimer    m_LockonTimer;      // �A����m_LockON���؂�ւ��̂�h�~

    aqua::CTimer    m_FlashTimer;       // �t���b�V���^�C�}�[

    CFloor*         m_Floor;            // ���̃|�C���^

    CEnemyManager*  m_EnemyManager;     // �G�Ǘ��N���X

    CEnemy*         m_LockOnEnemy;      // ���b�N�I�����̓G

    CLockOnMarker*  m_LockOnMarker;     // ���b�N�I���}�[�J�[�N���X�̃|�C���^
};