
/*!
 *  @file       effekseer_manager.h
 *  @brief      Effekseer�Ǘ��N���X
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
        class CEffekseerResource;

        /*!
         *  @class      CEffekseerManager
         *
         *  @brief      Effekseer�Ǘ��N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CEffekseerManager
        {
        public:
            /*!
             *  @brief      �C���X�^���X�̎擾
             *
             *  @return     �C���X�^���X�ւ̎Q��
             */
            static CEffekseerManager& GetInstance( void );

            /*!
             *  @brief      Effekseer�̓ǂݍ���
             *
             *  @param[in]  file_name   �t�@�C����
             *
             *  @return     Effekseer���\�[�X�N���X
             */
            CEffekseerResource*     Load( const std::string& file_name );

            /*!
             *  @brief      Effekseer�̉��
             *
             *  @param[in]  effect     Effekseer���\�[�X�N���X
             */
            void                    Unload( CEffekseerResource* effect );

            /*!
             *  @brief      Effekseer�̌���
             *
             *  @param[in]  file_name   �t�@�C����
             *
             *  @return     Effekseer���\�[�X�N���X
             */
            CEffekseerResource*     Find( const std::string& file_name );

            /*!
             *  @brief      Effekseer���X�g�̃N���A
             */
            void                    Clear( void );

        private:
            /*!
             *  @brief      �R���X�g���N�^
             */
            CEffekseerManager( void );

            /*!
             *  @brief      �R�s�[�R���X�g���N�^
             *
             *  @param[in]  rhs �R�s�[�I�u�W�F�N�g
             */
            CEffekseerManager( const CEffekseerManager& rhs );

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CEffekseerManager( void ) = default;

            /*!
             *  @brief      ������Z�q
             *
             *  @param[in]  rhs ����I�u�W�F�N�g
             *
             *  @return     ���g�̃I�u�W�F�N�g
             */
            CEffekseerManager&    operator=( const CEffekseerManager& rhs );

            /*!
             *  @brief      Effekseer���\�[�X���X�g
             */
            typedef std::list<CEffekseerResource*> EFFEKSEER_LIST;

            //! Effekseer���\�[�X���X�g
            EFFEKSEER_LIST  m_EffekseerList;
        };
    }
}
