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
#include "../bullet.h"


class CNomalBullet : public IBullet
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    CNomalBullet(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual ~CNomalBullet(void) = default;


    /*
     *  @brief      �X�V
     */
    virtual void    Update(void)override;

private:

};