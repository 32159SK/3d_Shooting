
/*!
 *  @file       effekseer.h
 *  @brief      Effekseer�N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "effekseer_resource\effekseer_resource.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CEffekseer
     *
     *  @brief      Effekseer�N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CEffekseer
    {
    public:
        /*!
         *  @brief      �R���X�g���N�^
         */
        CEffekseer( void );

        /*!
         *  @brief      �R�s�[�R���X�g���N�^
         *
         *  @param[in]  effect     Effekseer�N���X
         */
        CEffekseer( const CEffekseer& effect );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CEffekseer( void ) = default;

        /*!
         *  @brief      Effekseer�̓ǂݍ���
         *
         *  @param[in]  file_name   �t�@�C����
         */
        void    Load( const std::string& file_name );

        /*!
         *  @brief      Effekseer�̉��
         */
        void    Unload( void );

        /*!
         *  @brief      Effekseer�̃��\�[�X�n���h���擾
         *
         *  @return     Effekseer�̃��\�[�X�n���h���擾
         */
        int     GetResourceHandle( void ) const
        {
            if (!m_EffekseerResource) return AQUA_UNUSED_HANDLE;

            return m_EffekseerResource->GetResourceHandle();
        }

        /*!
         *  @brief      Effekseer�̓ǂݍ��݃`�F�b�N
         *
         *  @retval     true    �ǂݍ��ݍς�
         *  @retval     false   �ǂݍ��܂�Ă��Ȃ�
         */
        bool    IsEnable( void ) const
        {
            // ���\�[�X���Ȃ�
            if (!m_EffekseerResource) return false;

            // �ǂݍ��܂�Ă��Ȃ�
            return m_EffekseerResource->IsEnable();
        }

        /*!
         *  @brief      ������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  effect     Effekseer�N���X
         */
        CEffekseer&   operator=( const CEffekseer& effect );

    private:
        //! Effekseer���\�[�X�N���X
        core::CEffekseerResource*   m_EffekseerResource;
    };
}
