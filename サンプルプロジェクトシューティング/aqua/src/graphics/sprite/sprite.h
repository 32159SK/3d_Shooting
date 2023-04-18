
/*!
 *  @file       sprite.h
 *  @brief      �e�N�X�`���`��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>
#include <string>
#include "..\alphablend\alphablend.h"
#include "..\graphic_filter\graphic_filter.h"
#include "..\texture\texture.h"
#include "..\surface\surface.h"
#include "..\draw_object\draw_object.h"
#include "..\..\mathematics\mathematics.h"
#include "..\color\color.h"
#include "..\..\utility\utility.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CSprite
     *
     *  @brief      �e�N�X�`���`��N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CSprite
        : public aqua::core::IDrawObject
    {
    public:
        //! �ʒu
        aqua::CVector2      position;
        //! �F
        aqua::CColor        color;
        //! �`��͈�
        aqua::CRect         rect;
        //! �g�k�E��]�̊�_
        aqua::CVector2      anchor;
        //! �g�嗦
        aqua::CVector2      scale;
        //! ��]�l
        float               rotation;
        //! �A���t�@�u�����h���[�h
        aqua::ALPHABLEND    blend_mode;

        /*!
         *  @brief      �R���X�g���N�^
         */
        CSprite( void );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CSprite( void ) = default;

        /*!
         *  @brief      ����
         *
         *  @param[in]  file_name   �e�N�X�`���t�@�C����
         */
        void    Create( const std::string& file_name );

        /*!
         *  @brief      ����
         *
         *  @param[in]  surface     �T�[�t�F�C�X�N���X
         */
        void    Create( const CSurface& surface );

        /*!
         *  @brief      ���
         */
        void    Delete( void );

        /*!
         *  @brief      �`��
         */
        void    Draw( void );

        /*!
         *  @brief      �K�E�X�t�B���^�[�̓K�p
         *
         *  @param[in]  pixel_width     8, 16, 32�̂����ꂩ
         *  @param[in]  param           100��1px���̕�
         */
        void    ApplyGaussFilter( int pixel_width, int param );

        /*!
         *  @brief      �O���t�B�b�N�t�B���^�[�̉���
         */
        void    UnsetGraphicFilter( void );

        /*!
         *  @brief      �e�N�X�`���̕��擾
         *
         *  @return     �e�N�X�`���̕�
         */
        int     GetTextureWidth(void) const { return m_Texture.GetWidth(); }

        /*!
         *  @brief      �e�N�X�`���̍����擾
         *
         *  @return     �e�N�X�`���̍���
         */
        int     GetTextureHeight(void) const { return m_Texture.GetHeight(); }

        /*!
         *  @brief      ���\�[�X�n���h���擾
         *
         *  @return     ���\�[�X�n���h��
         */
        int     GetResourceHandle(void) const { return m_Texture.GetResourceHandle(); }

    private:
        //! �e�N�X�`��
        aqua::CTexture          m_Texture;
        //! �O���t�B�b�N�t�B���^�[
        aqua::GRAPHIC_FILTER    m_GraphicFilter;
        //! �K�E�X�t�B���^�[�p�s�N�Z����
        int                     m_GaussFilterPixelWitdh;
        //! �K�E�X�t�B���^�[�p�p�����[�^
        int                     m_GaussFilterParam;
    };
}
