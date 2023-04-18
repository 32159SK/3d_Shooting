
/*!
 *  @file       sound_resource.h
 *  @brief      �T�E���h���\�[�X�t�@�C��
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <windows.h>
#include <string>
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
         *  @class      CSoundResource
         *
         *  @brief      �T�E���h���\�[�X�N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CSoundResource
            : public core::IResourceObject
        {
        public:
            /*!
             *  @brief      �R���X�g���N�^
             */
            CSoundResource( void );

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CSoundResource( void ) = default;

            /*!
             *  @brief      �T�E���h�t�@�C���ǂݍ���
             *
             *  @param[in]  file_name   �t�@�C����
             *  @param[in]  count       SE���d�Đ��p�o�b�t�@�̐�
             */
            void            Load( const std::string& file_name, int buffer_count );

            /*!
             *  @brief      ���
             */
            void            Unload( void );

            /*!
             *  @brief      ���݂̍Đ����Ԃ��擾
             *
             *  @return     ���݂̍Đ�����(�b�P��)
             */
            float           GetCurrentPlayTime( void );

            /*!
             *  @brief      ���Đ����Ԃ��擾
             *
             *  @return     ���Đ�����(�b�P��)
             */
            float           GetTotalTime( void );

            /*!
             *  @brief      ���g�����擾
             *
             *  @return     ���g��(�w���c�P��)
             */
            int             GetFrequency( void );

            /*!
             *  @brief      �����̎��g�����擾
             *
             *  @return     ���g��(�w���c�P��)
             */
            int             GetDefaultFrequency( void );

            /*!
             *  @brief      ���g����ݒ�
             *
             *  @param[in]  frequency   ���g��(�w���c�P��:44.10KHz�̏ꍇ��44100)
             */
            void            SetFrequency( int frequency );

            /*!
             *  @brief      �\�t�g�E�F�A�T�E���h�n���h���擾
             *
             *  @return     �\�t�g�E�F�A�T�E���h�n���h��
             */
            int             GetSoftSoundHandle( void );


        private:
            //! ���[�h����o�b�t�@�̍ő吔
            static const int    m_max_load_buffer;
            //! �����̎��g��
            int                 m_DefaultFrequency;
            //! �\�t�g�E�F�A�T�E���h�n���h��
            int                 m_SoftSoundHandle;
        };
    }
}
