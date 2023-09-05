/*
 *  @file       penetrate_bullet.h
 *  @brief      �ђʒe
 *  @author     Kazuto Shimazaki
 *  @date       2022/06/20
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../bullet.h"


class CPenetrateBullet : public IBullet
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    CPenetrateBullet(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual ~CPenetrateBullet(void) = default;

    /*
     *  @brief      ������
     *
     *  @param[in]  bullet_info      ���˂���e���
     *  @param[in]  attri            ����
     *  @param[in]  pop_pos          ���ˍ��W
     *  @param[in]  dir              ����
     *  @param[in]  user             �g�p��
     *  @param[in]  em               �G�t�F�N�g�Ǘ��N���X�̃|�C���^(���x�T����������d���Ȃ�)
     */
    void    Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user, CEffectManager* em)override;


    /*
     *  @brief      �X�e�[�W�I�u�W�F�N�g�q�b�g����
     */
    void    StageObjectHit(aqua::CCubePrimitive::COLL_DIRE c_dire)override { return; }  // �I�u�W�F�N�g�����蔲����悤�ɂ��邽�߉������Ȃ�
};