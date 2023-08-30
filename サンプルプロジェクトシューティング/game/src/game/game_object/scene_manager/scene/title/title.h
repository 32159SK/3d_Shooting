#pragma once
/*
 *  @file       title_scene.h
 *  @brief      �^�C�g���V�[��
 *  @author     Miyu Hujita
 *  @date       2021/07/01
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "..\scene.h"
#include "../../../game_object.h"

 /*
  *  @class      CTitleScene
  *
  *  @brief      �^�C�g���V�[���N���X
  *
  *  @version    1.0
  */
class CTitleScene
    : public IScene
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent  �e�̃I�u�W�F�N�g
     */
    CTitleScene(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    ~CTitleScene(void) = default;

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
    aqua::CSprite       m_BackgroundSprite;     //! �w�i�p�X�v���C�g
    aqua::CSprite       m_TitleSprite;          //! �^�C�g���p�X�v���C�g
    aqua::CSprite       m_StartSprite;          //! �^�C�g���p�X�v���C�g
    //aqua::CLabel        m_LicenseLabel;

    /*
     *  @brief      ���쎞�̕����̋K��ʒu
     *  @param[in]  [0] = �^�C�g���X�v���C�g
     *  @param[in]  [1] = �u�X�^�[�g�v�̃{�^��
     */
    static const        aqua::CVector2 m_basis_position[2];

    aqua::CSprite       m_Sprite;  // �X�v���C�g

    CSoundManager*      m_SoundManager;
};
