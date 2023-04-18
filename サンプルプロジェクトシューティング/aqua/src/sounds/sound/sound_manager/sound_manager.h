
/*!
 *  @file       sound_manager.h
 *  @brief      �T�E���h�Ǘ��N���X
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
        class CSoundResource;

        /*!
         *  @class      CSoundManager
         *
         *  @brief      �T�E���h�Ǘ��N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CSoundManager
        {
        public:
            /*!
             *  @brief      �C���X�^���X�̎擾
             *
             *  @return     �C���X�^���X�ւ̎Q��
             */
            static CSoundManager&   GetInstance( void );

            /*!
             *  @brief      �T�E���h�̓ǂݍ���
             *
             *  @param[in]  file_name       �t�@�C����
             *  @param[in]  buffer_count    SE���d�Đ��p�o�b�t�@��
             *
             *  @return     �T�E���h���\�[�X�N���X
             */
            CSoundResource*         Load( const std::string& file_name, int buffer_count );

            /*!
             *  @brief      �T�E���h�̉��
             *
             *  @param[in]  sound   �e�N�X�`�����\�[�X�N���X
             */
            void                    Unload( CSoundResource* sound );

            /*!
             *  @brief      �X�V
             */
            void                    Update( void );

            /*!
             *  @brief      �T�E���h�̌���
             *
             *  @param[in]  file_name   �t�@�C����
             *
             *  @return     �T�E���h���\�[�X�N���X
             */
            CSoundResource*         Find( const std::string& file_name );

            /*!
             *  @brief      �T�E���h���X�g�̃N���A
             */
            void                    Clear( void );

        private:
            /*!
             *  @brief      �R���X�g���N�^
             */
            CSoundManager( void );

            /*!
             *  @brief      �R�s�[�R���X�g���N�^
             *
             *  @param[in]  rhs �R�s�[�I�u�W�F�N�g
             */
            CSoundManager( const CSoundManager& rhs );

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CSoundManager( void ) = default;

            /*!
             *  @brief      ������Z�q
             *
             *  @param[in]  rhs ����I�u�W�F�N�g
             *
             *  @return     ���g�̃I�u�W�F�N�g
             */
            CSoundManager&    operator=( const CSoundManager& rhs );

            /*!
             *  @brief      �T�E���h���\�[�X���X�g
             */
            typedef std::list<CSoundResource*>  SOUND_RESOURCE_LIST;

            //! �T�E���h���\�[�X���X�g
            SOUND_RESOURCE_LIST     m_SoundResourceList;
        };
    }
}
