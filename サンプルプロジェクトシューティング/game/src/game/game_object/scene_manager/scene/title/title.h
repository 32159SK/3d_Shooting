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
    //aqua::CLabel        m_LicenseLabel;

    static const float          m_un_operation_time;    // ����s�\����
    static const float          m_dump_width;           // �摜�̒��ŕ\�����Ȃ�������̉���
    static const aqua::CVector2 m_frame_thick;          // �t���[���̑���

    /*
     *  @brief      ���쎞�̕����̋K��ʒu
     *  @param[in]  [0] = �^�C�g���X�v���C�g
     *  @param[in]  [1] = �u�X�^�[�g�v�̃{�^��
     *  @param[in]  [2] = �u�L�[�}�E����v�̃{�^��
     *  @param[in]  [3] = �u�}�E�X����v�̃{�^��
     */
    static const        aqua::CVector2 m_basis_position[3];

    OPERATE_STYLE       m_OperateStyle;     // ����X�^�C��

    aqua::CSprite       m_StartSprite;      // �X�v���C�g
    aqua::CSprite       m_ChoiceSprite[2];  // �I�����X�v���C�g

    CSoundManager*      m_SoundManager;
};
