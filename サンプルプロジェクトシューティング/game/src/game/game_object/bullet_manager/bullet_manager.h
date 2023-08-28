
/*!
 *  @file       enemy_manager.h
 *  @brief      �G�l�~�[�Ǘ�
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/18
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "bullet/bullet_info.h"


 /*!
  *  @class      CBulletManager
  *
  *  @brief      �G�l�~�[�Ǘ��N���X
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/04/18
  *
  *  @version    1.0
  */

class CBeam;

class CBulletManager
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     */
    CBulletManager(aqua::IGameObject* parent);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CBulletManager(void) = default;

    /*!
     *  @brief      ������
     */
    void        Initialize(void)override;

    /*!
     *  @brief      �X�V
     */
    void        Update(void) override;

    /*!
     *  @brief      �`��
     */
    void        Draw(void) override;

    /*!
     *  @brief      �e�̐���
     */
    void        Create(aqua::CVector3 shot_pos, aqua::CVector3 shot_front, UNIT_TYPE unit_type, BULLET_TYPE bullet_type, IUnit* user);

    /*!
     *  @brief      �r�[���𐶐����|�C���^��n��
     */
    CBeam*      CreateGetBeam(aqua::CVector3 shot_pos, aqua::CVector3 shot_front, UNIT_TYPE unit_type,IUnit* user);

    /*!
     *  @brief      ���
     */
    void        Finalize(void) override;

    /*!
     *  @brief      �G�Z�b�^�[
     */
    void        SetEnemy(CEnemy* enemy) { m_EnemyList.push_back(enemy); }

    /*!
     *  @brief      ���@�Z�b�^�[
     */
    void        SetPlayer(CPlayer* player) { m_Player = player; }

    /*
     *  @brief      ���Z�b�g
     */
    void        EnemyReset(void);

    /*
     *  @brief      ���Z�b�g
     */
    void        EnemyReset(CEnemy* enemy);

    void        WaveChange(void);

    /*
     *  @brief      �e�햼�擾
     */
    std::string GetBulletName(BULLET_TYPE bullet_type) { return m_BulletInfo[(int)bullet_type].bullet_name; }
private:

    /*
     *  @brief      ���Z�b�g
     */
    void        BulletDataLoad(void);

    /*
     *  @brief      �q�b�g����
     */
    void        CheakHit(void);

    /*
     *  @brief      �r�[���̃q�b�g����
     */
    void        CheakHitBeam(CBeam* beam,int e_count);

    static const std::string m_bullet_info_path;

    CPlayer*                m_Player;           // �v���C���[�N���X
    CStageManager*          m_StageManager;     // �X�e�[�W�Ǘ��N���X
    CEffectManager*         m_EffectManager;    // �G�t�F�N�g�Ǘ��N���X
    CSoundManager*          m_SoundManager;     // �T�E���h�Ǘ��N���X
    std::vector<BULLET_INFO> m_BulletInfo;      // �e���̃��X�g
    std::vector<CEnemy*>    m_EnemyList;        // ���ݐ������Ă���G�̃��X�g
};
