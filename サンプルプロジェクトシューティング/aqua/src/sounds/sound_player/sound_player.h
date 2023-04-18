
/*!
 *  @file       sound_player.h
 *  @brief      �T�E���h�v���C���[
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <string>
#include "..\sound\sound.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CSoundPlayer
     *
     *  @brief      �T�E���h�v���C���[�N���X<br>
     *              wav�`���Emp3�`���Eogg�`���Eopus�`���ɑΉ�
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CSoundPlayer
    {
    public:
        /*!
         *  @brief      �R���X�g���N�^
         */
        CSoundPlayer( void );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CSoundPlayer( void ) = default;

        /*!
         *  @brief      �Đ��p�o�b�t�@�쐬
         *
         *  @param[in]  file_name       �t�@�C����
         *  @param[in]  loop            ���[�v�ݒ�
         *  @param[in]  buffer_count    SE���d�Đ��p�o�b�t�@��(���[�v�Đ��ݒ�̏ꍇ��1�ɂȂ�)
         */
        void            Create( const std::string& file_name, bool loop = false, int buffer_count = 3 );

        /*!
         *  @brief      �Đ��p�o�b�t�@�쐬
         *
         *  @param[in]  sound   �T�E���h�N���X
         */
        void            Create( const aqua::CSound& sound );

        /*!
         *  @brief      �Đ��o�b�t�@�̉��
         */
        void            Delete( void );

        /*!
         *  @brief      �Đ�
         */
        void            Play( void );

        /*!
         *  @brief      ��~
         */
        void            Stop( void );

        /*!
         *  @brief      ������Đ����Ȃ���
         */
        void            ReStart(void);

        /*!
         *  @brief      ���݂̍Đ����Ԃ��擾
         *
         *  @return     ���݂̍Đ�����(�b�P��)
         */
        float           GetCurrentPlayTime(void);

        /*!
         *  @brief      ���Đ����Ԃ��擾
         *
         *  @return     ���Đ�����(�b�P��)
         */
        float           GetTotalTime(void);

        /*!
         *  @brief      �Đ��������ׂ�
         *
         *  @retval     true    �Đ���
         *  @retval     false   �Đ����Ă��Ȃ�
         */
        bool            IsPlaying(void);

        /*!
         *  @brief      �{�����[���ݒ�<br>
         *              0�`255�̐����Ŏw��
         *
         *  @param[in]  volume  �{�����[��
         */
        void            SetVolume( int volume );

        /*!
         *  @brief      ���\�[�X�n���h���擾
         *
         *  @return     ���\�[�X�n���h��
         */
        int             GetResourceHandle( void ) const;

        /*!
         *  @brief      �\�t�g�E�F�A�T�E���h�n���h���擾
         *
         *  @return     �\�t�g�E�F�A�T�E���h�n���h��
         */
        int             GetSoftSoundHandle( void ) const;

    private:
        //! �ő剹��
        static const int    m_max_volume;
        //! �ŏ�����
        static const int    m_min_volume;
        //! �T�E���h�N���X
        CSound              m_Sound;
        //! ���[�v�Đ��t���O
        bool                m_LoopFlag;
    };
}
