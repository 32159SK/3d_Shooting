
/*!
 *  @file       texture.h
 *  @brief      2D�e�N�X�`���N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "texture_resource\texture_resource.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CTexture
     *
     *  @brief      �e�N�X�`���N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CTexture
    {
    public:
        /*!
         *  @brief      �R���X�g���N�^
         */
        CTexture( void );

        /*!
         *  @brief      �R�s�[�R���X�g���N�^
         *
         *  @param[in]  texture     �e�N�X�`���N���X
         */
        CTexture( const CTexture& texture );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CTexture( void ) = default;

        /*!
         *  @brief      �e�N�X�`���̓ǂݍ���
         *
         *  @param[in]  file_name   �t�@�C����
         */
        void    Load( const std::string& file_name );

        /*!
         *  @brief      �e�N�X�`���̉��
         */
        void    Unload( void );

        /*!
         *  @brief      �e�N�X�`���̃��\�[�X�n���h���擾
         *
         *  @return     �e�N�X�`���̃��\�[�X�n���h���擾
         */
        int     GetResourceHandle( void ) const
        {
            if (!m_TextureResource) return AQUA_UNUSED_HANDLE;

            return m_TextureResource->GetResourceHandle();
        }

        /*!
         *  @brief      �e�N�X�`���̉����擾
         *
         *  @return     �e�N�X�`���̉���
         */
        int     GetWidth(void) const
        {
            if (!m_TextureResource) return 0;

            return m_TextureResource->GetWidth();
        }

        /*!
         *  @brief      �e�N�X�`���̏c���擾
         *
         *  @return     �e�N�X�`���̏c��
         */
        int     GetHeight( void ) const
        {
            if (!m_TextureResource) return 0;

            return m_TextureResource->GetHeight();
        }

        /*!
         *  @brief      �e�N�X�`���̓ǂݍ��݃`�F�b�N
         *
         *  @retval     true    �ǂݍ��ݍς�
         *  @retval     false   �ǂݍ��܂�Ă��Ȃ�
         */
        bool    IsEnable( void ) const
        {
            if (!m_TextureResource) return false;

            return m_TextureResource->IsEnable();
        }


        /*!
         *  @brief      ������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  texture     �e�N�X�`���N���X
         */
        CTexture&   operator=( const CTexture& texture );

    private:
        /*!
         *  @brief      �e�N�X�`���̐���
         *
         *  @param[in]  width           ����
         *  @param[in]  height          �c��
         *  @param[in]  alpha_channel   �A���t�@�`�����l��
         */
        void    Create( int width, int height, bool alpha_channel );

        /*!
         *  @brief      �e�N�X�`���̉��
         */
        void    Delete( void );

        /*!
         *  @brief      CSurface�N���X���t�����h�o�^
         */
        friend class CSurface;

        //! �e�N�X�`�����\�[�X�N���X
        core::CTextureResource*     m_TextureResource;
    };
}
