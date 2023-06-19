#pragma once
/*
 *  @file       title_scene.h
 *  @brief      �^�C�g���V�[��
 *  @author     
 *  @date       
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "..\scene.h"

 /*
  *  @class      CResultScene
  *
  *  @brief      �^�C�g���V�[���N���X
  *
  *  @version    1.0
  */
class CResultScene
    : public IScene
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent  �e�̃I�u�W�F�N�g
     */
    CResultScene(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    ~CResultScene(void) = default;

    /*
     *  @brief      ������
     */
    void        Initialize(void) override;

    /*
     *  @brief      �X�V
     */
    void        Update(void) override;

    /*
     *  @brief      �`��
     */
    void        Draw(void) override;

    /*
     *  @brief      ���
     */
    void        Finalize(void) override;

    /*
     *  @brief      �V�[���u����\�v
     */
    void        Operation(void);


private:
    aqua::CSprite   m_BackgroundSprite;
    aqua::CSprite   m_ResultSprite[2];
};
