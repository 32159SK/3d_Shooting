
/*!
 *  @file       texture_resource.h
 *  @brief      �e�N�X�`�����\�[�X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "..\..\..\resources\resources.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @brief      aqua::core���O���
     */
    namespace core
    {
        /*!
         *  @class      CTextureResource
         *
         *  @brief      �e�N�X�`�����\�[�X�N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CTextureResource
            : public core::IResourceObject
        {
        public:
            /*!
             *  @brief      �R���X�g���N�^
             */
            CTextureResource( void );

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CTextureResource( void ) = default;

            /*!
             *  @brief      �e�N�X�`���̓ǂݍ���
             *
             *  @param[in]  file_name   �t�@�C����
             */
            void        Load( const std::string& file_name );

            /*!
             *  @brief      �e�N�X�`���̉��
             */
            void        Unload( void );

            /*!
             *  @brief      �e�N�X�`���̉����擾
             *
             *  @return     �e�N�X�`���̉���
             */
            int         GetWidth(void) const { return m_Width; }

            /*!
             *  @brief      �e�N�X�`���̏c���擾
             *
             *  @return     �e�N�X�`���̏c��
             */
            int         GetHeight(void) const { return m_Height; }

        private:
            /*!
             *  @brief      �N���X���t�����h�o�^
             */
            friend class CTexture;
            friend class CTextureManager;

            /*!
             *  @brief      �e�N�X�`���̐���
             *
             *  @param[in]  width           ����
             *  @param[in]  height          �c��
             *  @param[in]  alpha_channel   �A���t�@�`�����l��
             */
            void        Create( int width, int height, bool alpha_channel );

            /*!
             *  @brief      �e�N�X�`���̉��
             */
            void        Delete( void );

            //! ���ߐF(�}�[���^ : 0xffff00ff)
            static const unsigned int   m_transparent_color;
            //! �e�N�X�`���̕�
            int                         m_Width;
            //! �e�N�X�`���̍���
            int                         m_Height;
        };
    }
}
