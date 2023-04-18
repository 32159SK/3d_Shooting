
/*!
 *  @file       texture_manager.h
 *  @brief      �e�N�X�`���Ǘ��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <list>
#include <string>

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
        class CTextureResource;

        /*!
         *  @class      CTextureManager
         *
         *  @brief      �e�N�X�`���Ǘ��N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CTextureManager
        {
        public:
            /*!
             *  @brief      �C���X�^���X�̎擾
             *
             *  @return     �C���X�^���X�ւ̎Q��
             */
            static CTextureManager& GetInstance( void );

            /*!
             *  @brief      �e�N�X�`���̓ǂݍ���
             *
             *  @param[in]  file_name   �t�@�C����
             *
             *  @return     �e�N�X�`�����\�[�X�N���X
             */
            CTextureResource*       Load( const std::string& file_name );

            /*!
             *  @brief      �e�N�X�`���̉��
             *
             *  @param[in]  texture     �e�N�X�`�����\�[�X�N���X
             */
            void                    Unload( CTextureResource* texture );

            /*!
             *  @brief      �e�N�X�`���̐���
             *
             *  @param[in]  width           ����
             *  @param[in]  height          �c��
             *  @param[in]  alpha_channel   �A���t�@�`�����l��
             */
            CTextureResource*       Create( int width, int height, bool alpha_channel );

            /*!
             *  @brief      �e�N�X�`���̉��
             */
            void                    Delete( CTextureResource* texture );

            /*!
             *  @brief      �e�N�X�`���̌���
             *
             *  @param[in]  file_name   �t�@�C����
             *
             *  @return     �e�N�X�`�����\�[�X�N���X
             */
            CTextureResource*       Find( const std::string& file_name );

            /*!
             *  @brief      �e�N�X�`�����X�g�̃N���A
             */
            void                    Clear( void );

        private:
            /*!
             *  @brief      �R���X�g���N�^
             */
            CTextureManager( void );

            /*!
             *  @brief      �R�s�[�R���X�g���N�^
             *
             *  @param[in]  rhs �R�s�[�I�u�W�F�N�g
             */
            CTextureManager( const CTextureManager& rhs );

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CTextureManager( void ) = default;

            /*!
             *  @brief      ������Z�q
             *
             *  @param[in]  rhs ����I�u�W�F�N�g
             *
             *  @return     ���g�̃I�u�W�F�N�g
             */
            CTextureManager&    operator=( const CTextureManager& rhs );

            /*!
             *  @brief      �e�N�X�`�����\�[�X���X�g
             */
            typedef std::list<CTextureResource*> TEXTURE_LIST;

            //! �e�N�X�`�����\�[�X���X�g
            TEXTURE_LIST    m_TextureList;
        };
    }
}
