
/*!
 *  @file       camera_control.h
 *  @brief      �J�����Ǘ�
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/11
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */
#pragma once

#include "aqua.h"

/*!
 *  @class      CCameraControl
 *
 *  @brief      �J�����R���g���[���N���X
 *
 *  @author     Kazuto Shimazaki
 *
 *  @date       2023/04/11
 *
 *  @version    1.0
 */
class CCameraControl
{
public:

    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  camera  �J�����I�u�W�F�N�g
     */
    CCameraControl(aqua::CCamera* camera);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CCameraControl(void) = default;

    /*!
     *  @brief      �J�����ړ�
     */
    void            Move(void);

    /*!
     *  @brief      �J��������
     */
    void            Operation(void);

private:
	aqua::CCamera*	m_Camera;
    aqua::CVector3  m_Velocity;     // �J�����̈ړ����x
    float           m_CamSpeed;     // �J�����ړ��̑���
};