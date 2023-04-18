
/*!
 *  @file       alphablend.h
 *  @brief      �A���t�@�u�����h
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @brief      �A���t�@�u�����hID��`
     */
    enum class ALPHABLEND
    {
        //! �u�����h�Ȃ�
        NOBELEND    = DX_BLENDMODE_NOBLEND,
        //! ������
        ALPHA       = DX_BLENDMODE_ALPHA,
        //! ���Z����
        ADD         = DX_BLENDMODE_ADD,
        //! ���Z����
        SUB         = DX_BLENDMODE_SUB,
        //! ���]����
        INVSRC      = DX_BLENDMODE_INVSRC,
    };
}
