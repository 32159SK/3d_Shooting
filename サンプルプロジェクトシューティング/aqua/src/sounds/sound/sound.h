
/*!
 *  @file       sound.h
 *  @brief      �T�E���h�Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "sound_resource\sound_resource.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CSound
     *
     *  @brief      �T�E���h�N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CSound
    {
    public:
        /*!
         *  @brief      �R���X�g���N�^
         */
        CSound( void );

        /*!
         *  @brief      �R�s�[�R���X�g���N�^
         *
         *  @param[in]  sound   �T�E���h�N���X
         */
        CSound( const CSound& sound );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CSound( void ) = default;

        /*!
         *  @brief      �T�E���h�̓ǂݍ���
         *
         *  @param[in]  file_name       �t�@�C����
         *  @param[in]  buffer_count    SE���d�Đ��o�b�t�@��
         */
        void        Load( const std::string& file_name, int buffer_count );

        /*!
         *  @brief      �T�E���h�̉��
         */
        void        Unload( void );

        /*!
         *  @brief      ���݂̍Đ����Ԃ��擾
         *
         *  @return     ���݂̍Đ�����(�b�P��)
         */
        float       GetCurrentPlayTime(void)
        {
            if (!m_SoundResource) return 0.0f;

            return m_SoundResource->GetCurrentPlayTime();
        }

        /*!
         *  @brief      ���Đ����Ԃ��擾
         *
         *  @return     ���Đ�����(�b�P��)
         */
        float       GetTotalTime(void)
        {
            if (!m_SoundResource) return 0.0f;

            return m_SoundResource->GetTotalTime();
        }

        /*!
         *  @brief      �T�E���h�̃��\�[�X�n���h���擾
         *
         *  @return     �T�E���h�̃��\�[�X�n���h���擾
         */
        int         GetResourceHandle( void ) const
        {
            if (!m_SoundResource) return AQUA_UNUSED_HANDLE;

            return m_SoundResource->GetResourceHandle();
        }

        /*!
         *  @brief      �\�t�g�E�F�A�T�E���h�n���h���擾
         *
         *  @return     �\�t�g�E�F�A�T�E���h�n���h��
         */
        int         GetSoftSoundHandle(void) const
        {
            if (!m_SoundResource) return AQUA_UNUSED_HANDLE;

            return m_SoundResource->GetSoftSoundHandle();
        }

        /*!
         *  @brief      ���p�\�����ׂ�
         *
         *  @retval     true    ���p�\
         *  @retval     false   ���p�s�\
         */
        bool        IsEnable(void) const
        {
            if (m_SoundResource)
                return m_SoundResource->IsEnable();

            return false;
        }

        /*!
         *  @brief      ������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  sound   �T�E���h�N���X
         */
        CSound&     operator=( const CSound& sound );

    private:
        //! �T�E���h���\�[�X�N���X
        core::CSoundResource*   m_SoundResource;
    };
}
