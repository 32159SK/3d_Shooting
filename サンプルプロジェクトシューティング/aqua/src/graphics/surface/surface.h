
/*!
 *  @file       surface.h
 *  @brief      �T�[�t�F�C�X�N���X
 *  @author     Kazuya Maruyama
 *  @date       2018/12/19
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "..\texture\texture.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CSurface
     *
     *  @brief      �T�[�t�F�C�X�N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2018/12/19
     *
     *  @version    7.17
     */
    class CSurface
    {
    public:
        /*!
         *  @brief  �R���X�g���N�^
         */
        CSurface( void );

        /*!
         *  @brief  �f�X�g���N�^
         */
        ~CSurface( void ) = default;

        /*!
         *  @brief  �T�[�t�F�C�X�쐬
         *
         *  @param[in]  width           ����
         *  @param[in]  height          �c��
         *  @param[in]  alpha_channel   �A���t�@�`�����l���̎g�p
         */
        void    Create( int width, int height, bool alpha_channel = false );

        /*!
         *  @brief  �T�[�t�F�C�X���
         */
        void    Delete( void );

        /*!
         *  @brief  �T�[�t�F�C�X�ւ̕`��J�n
         */
        void    Begin( void );

        /*!
         *  @brief  �T�[�t�F�C�X�ւ̕`��I��
         */
        void    End( void );

        /*!
         *  @brief  �`���̃X�N���[�����T�[�t�F�C�X�ɃR�s�[����
         */
        void    CopyDrawScreen( void );

        /*!
         *  @brief  �e�N�X�`���̎擾
         *
         *  @return �e�N�X�`��
         */
        CTexture    GetTexture( void );

    private:
        /*!
         *  @brief  ���\�[�X�̓ǂݍ���(���g�p)
         *
         *  @param[in]  file_name   �t�@�C����
         */
        void    Load( const std::string& file_name );

        /*!
         *  @brief  ���\�[�X�̉��(���g�p)
         */
        void    Unload( void );

        /*!
         *  @brief  �X�v���C�g�N���X���t�����h�o�^
         */
        friend class CSprite;

        //! �e�N�X�`���N���X
        aqua::CTexture  m_Texture;
    };
}
