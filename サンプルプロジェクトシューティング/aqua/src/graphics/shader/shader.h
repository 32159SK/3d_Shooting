
/*!
 *  @file       shader.h
 *  @brief      �V�F�[�_�N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>
#include <string>
#include "..\..\resources\resources.h"
#include "..\..\utility\utility.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CShader
     *
     *  @brief      �V�F�[�_�N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CShader
        : aqua::core::IResourceObject
    {
    public:
        /*!
         *  @brief      �R���X�g���N�^
         */
        CShader( void );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CShader( void ) = default;

        /*!
         *  @brief      ����
         *
         *  @param[in]  file_name   �V�F�[�_�t�@�C����(�g���͎w�肵�Ȃ�)
         */
        void    Create( const std::string& file_name );

        /*!
         *  @brief      ���
         */
        void    Delete( void );

        /*!
         *  @brief      �V�F�[�_�K�p�J�n
         */
        void    Begin( void );

        /*!
         *  @brief      �V�F�[�_�̓K�p�I��
         */
        void    End( void );

        /*!
         *  @brief      �V�F�[�_�Ŏg�p����e�N�X�`����ݒ�
         *
         *  @param[in]  register_id     ���W�X�^ID(2�ȍ~�̐��������ԂɎg��)
         *  @param[in]  handle          �e�N�X�`���̃O���t�B�b�N�X�n���h��
         */
        void    SetUseTexture( int register_id, int handle );

    private:
        //! �o�[�e�b�N�X�V�F�[�_�n���h��
        int     m_VertexShaderHandle;
        //! �s�N�Z���V�F�[�_�n���h��
        int     m_PixelShaderHandle;
        //! ���_�V�F�[�_�p�萔�o�b�t�@�n���h��
        int     m_VertxConstBufferHandle;
    };
}
