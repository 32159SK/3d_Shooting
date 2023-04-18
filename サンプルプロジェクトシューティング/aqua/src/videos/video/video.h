
/*!
 *  @file       video.h
 *  @brief      �r�f�I�Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "video_resource\video_resource.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CVideo
     *
     *  @brief      �r�f�I�N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CVideo
    {
    public:
        /*!
         *  @brief      �R���X�g���N�^
         */
        CVideo( void );

        /*!
         *  @brief      �R�s�[�R���X�g���N�^
         *
         *  @param[in]  video   �r�f�I�N���X
         */
        CVideo( const CVideo& video );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CVideo( void ) = default;

        /*!
         *  @brief      �r�f�I�̓ǂݍ���
         *
         *  @param[in]  file_name   �t�@�C����
         */
        void        Load( const std::string& file_name );

        /*!
         *  @brief      �r�f�I�̉��
         */
        void        Unload( void );

        /*!
         *  @brief      �r�f�I�̃��\�[�X�n���h���擾
         *
         *  @return     �r�f�I�̃��\�[�X�n���h���擾
         */
        int         GetResourceHandle( void ) const
        {
            if (!m_VideoResource) return AQUA_UNUSED_HANDLE;

            return m_VideoResource->GetResourceHandle();
        }

        /*!
         *  @brief      �r�f�I�̓ǂݍ��݃`�F�b�N
         *
         *  @retval     true    �ǂݍ��ݍς�
         *  @retval     false   �ǂݍ��܂�Ă��Ȃ�
         */
        bool        IsEnable( void ) const
        {
            if (!m_VideoResource) return false;

            return m_VideoResource->IsEnable();
        }


        /*!
         *  @brief      ������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  video   �r�f�I�N���X
         */
        CVideo&     operator=( const CVideo& video );

    private:
        //! �r�f�I���\�[�X�N���X
        core::CVideoResource*   m_VideoResource;
    };
}
