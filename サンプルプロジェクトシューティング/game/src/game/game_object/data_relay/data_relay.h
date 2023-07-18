
/*!
 *  @file       data_relay.h
 *  @brief      ���p�N���X
 *  @author
 *  @date
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "../player/play_style.h"
#include <stdio.h>
#include <string>


/*!
 *  @class      CDataRelay
 *
 *  @brief      ���p�N���X
 *
 *  @author
 *
 *  @date
 *
 *  @version    1.0
 */
class CDataRelay
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     */
    CDataRelay(aqua::IGameObject* parent);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CDataRelay(void) = default;

    /*!
     *  @brief      ����X�^�C���̎擾
     */
    void    SetOPerateStyle(OPERATE_STYLE style) { m_OperateStyle = style; }

    /*!
     *  @brief      ���U���g���Ɉ����f�[�^�擾
     */
    void    SetClear(bool clear) { m_Clear = clear; }

    /*!
     *  @brief      ���U���g���Ɉ����f�[�^�擾
     */
    OPERATE_STYLE    GetOperateStyle(void) { return m_OperateStyle; }

    /*!
     *  @brief      ���U���g���Ɉ����f�[�^�擾
     */
    bool    GetClearFlag(void) { return m_Clear; }
private:

    bool            m_Clear;        // 
    OPERATE_STYLE   m_OperateStyle; // ����X�^�C��
};
