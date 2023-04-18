
/*!
 *  @file       video_manager.h
 *  @brief      �r�f�I�Ǘ��N���X
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
        class CVideoResource;

        /*!
         *  @class      CVideoManager
         *
         *  @brief      �r�f�I�Ǘ��N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CVideoManager
        {
        public:
            /*!
             *  @brief      �C���X�^���X�̎擾
             *
             *  @return     �C���X�^���X�ւ̎Q��
             */
            static CVideoManager&   GetInstance( void );

            /*!
             *  @brief      �r�f�I�̓ǂݍ���
             *
             *  @param[in]  file_name   �t�@�C����
             *
             *  @return     �r�f�I���\�[�X�N���X
             */
            CVideoResource*         Load( const std::string& file_name );

            /*!
             *  @brief      �r�f�I�̉��
             *
             *  @param[in]  sound   �e�N�X�`�����\�[�X�N���X
             */
            void                    Unload( CVideoResource* video );

            /*!
             *  @brief      �r�f�I�̌���
             *
             *  @param[in]  file_name   �t�@�C����
             *
             *  @return     �r�f�I���\�[�X�N���X
             */
            CVideoResource*         Find( const std::string& file_name );

            /*!
             *  @brief      �r�f�I���X�g�̃N���A
             */
            void                    Clear( void );

        private:
            /*!
             *  @brief      �R���X�g���N�^
             */
            CVideoManager( void );

            /*!
             *  @brief      �R�s�[�R���X�g���N�^
             *
             *  @param[in]  rhs �R�s�[�I�u�W�F�N�g
             */
            CVideoManager( const CVideoManager& rhs );

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CVideoManager( void ) = default;

            /*!
             *  @brief      ������Z�q
             *
             *  @param[in]  rhs ����I�u�W�F�N�g
             *
             *  @return     ���g�̃I�u�W�F�N�g
             */
            CVideoManager&    operator=( const CVideoManager& rhs );

            /*!
             *  @brief      �r�f�I���\�[�X���X�g
             */
            typedef std::list<CVideoResource*>  VIDEO_RESOURCE_LIST;

            //! �r�f�I���\�[�X���X�g
            VIDEO_RESOURCE_LIST     m_VideoResourceList;
        };
    }
}
