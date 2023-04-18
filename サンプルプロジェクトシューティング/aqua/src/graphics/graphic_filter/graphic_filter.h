
/*!
 *  @file       graphic_filter.h
 *  @brief      �O���t�B�b�N�t�B���^�[
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
     *  @brief      �O���t�B�b�N�t�B���^�[ID��`
     */
    enum class GRAPHIC_FILTER
    {
        //! �t�B���^�[�Ȃ�
        NONE         = -1,
        //MONO         = DX_GRAPH_FILTER_MONO,         //! ���m�g�[���t�B���^
        //! �K�E�X�t�B���^
        GAUSS        = DX_GRAPH_FILTER_GAUSS,
        //DOWN_SCALE   = DX_GRAPH_FILTER_DOWN_SCALE,   //! �k���t�B���^
        //BRIGHT_CLIP  = DX_GRAPH_FILTER_BRIGHT_CLIP,  //! ���邳�N���b�v�t�B���^
        //BRIGHT_SCALE = DX_GRAPH_FILTER_BRIGHT_SCALE, //! �w��̖��邳�̈���g�傷��t�B���^
        //HSB          = DX_GRAPH_FILTER_HSB,          //! �F���E�ʓx�E���x�t�B���^
        //INVERT       = DX_GRAPH_FILTER_INVERT,       //! �K���̔��]�t�B���^
        //LEVEL        = DX_GRAPH_FILTER_LEVEL,        //! ���x���␳�t�B���^
        //TWO_COLOR    = DX_GRAPH_FILTER_TWO_COLOR,    //! �Q�K�����t�B���^
        //GRADIENT_MAP = DX_GRAPH_FILTER_GRADIENT_MAP, //! �O���f�[�V�����}�b�v�t�B���^
   };
}
