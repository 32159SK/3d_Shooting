
/*!
 *  @file       animation_sprite.h
 *  @brief      �A�j���[�V�����t���X�v���C�g�N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>
#include <vector>
#include <string>
#include "..\alphablend\alphablend.h"
#include "..\texture\texture.h"
#include "..\surface\surface.h"
#include "..\draw_object\draw_object.h"
#include "..\..\mathematics\mathematics.h"
#include "..\color\color.h"
#include "..\..\utility\utility.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CAnimationSprite
     *
     *  @brief      �A�j���[�V�����t���X�v���C�g�N���X
     *
     *  @details    JSON�`���̃t�@�C��(.ass)��ǂݍ��݁A<br>
     *              �X�v���C�g�̃A�j���[�V�������Đ����܂��B<br>
     *              �A�j���[�V������ass�t�@�C�����Œ�`�����L�[�����w�肵�܂��B<br>
     *              ���[�v�Đ����Ȃ��A�j���[�V�����ł͍Đ��I�������m���邱�Ƃ��\�ł��B
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CAnimationSprite
        : public aqua::core::IDrawObject
    {
    public:
        //! �ʒu
        aqua::CVector2      position;
        //! �F
        aqua::CColor        color;
        //! �g�k�E��]�̊�_
        aqua::CVector2      anchor;
        //! �g�嗦
        aqua::CVector2      scale;
        //! ��]�l(���W�A��)
        float               rotation;
        //! �A���t�@�u�����h���[�h
        aqua::ALPHABLEND    blend_mode;

        /*!
         *  @brief      �R���X�g���N�^
         */
        CAnimationSprite( void );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CAnimationSprite(void) = default;

        /*!
         *  @brief      ����
         *
         *  @param[in]  file_name   �A�j���[�V�����p�t�@�C����(.ass)
         */
        void    Create( const std::string& file_name );

        /*!
         *  @brief      ����
         *
         *  @param[in]  file_name   �A�j���[�V�����p�t�@�C����(.ass)
         *  @param[in]  anime_name  �A�j���[�V������
         */
        void    Create( const std::string& file_name, const std::string& anime_name );

        /*!
         *  @brief      ����
         *
         *  @param[in]  file_name   �A�j���[�V�����p�t�@�C����(.ass)
         *  @param[in]  anime_id    �A�j���[�V����ID
         */
        void    Create( const std::string& file_name, int anime_id );

        /*!
         *  @brief      ���
         */
        void    Delete( void );

        /*!
         *  @brief      �X�V
         */
        void    Update( );

        /*!
         *  @brief      �`��
         */
        void    Draw( void );

        /*!
         *  @brief      �A�j���[�V�����̕ύX
         *
         *  @param[in]  anime_name  �A�j���[�V������
         */
        void    Change( const std::string& anime_name );

        /*!
         *  @brief      �A�j���[�V�����̕ύX
         *
         *  @param[in]  anime_id    �A�j���[�V����ID
         */
        void    Change( int anime_id );

        /*!
         *  @brief      �A�j���[�V�����̍Đ�
         *              �J�����g�t���[������Đ�����
         */
        void    Play( void );

        /*!
         *  @brief      �A�j���[�V�����̒�~
         */
        void    Stop( void );

        /*!
         *  @brief      �A�j���[�V�����̃��Z�b�g
         *              �A�j���[�V�����t���[�������Z�b�g��0�ɂ���
         */
        void    ResetAnimationFrame( void );

        /*!
         *  @brief      �A�j���[�V�����I�����m
         *
         *  @retval     true    �A�j���[�V�����I��
         *  @retval     false   �A�j���[�V�����p��
         */
        bool    Finished( void );

        /*!
         *  @brief      ���ݍĐ����Ă���A�j���[�V�����ԍ��擾
         *
         *  @return     �Đ����̃A�j���[�V�����ԍ�
         */
        int             GetCurrentAnimationID(void) const { return m_CurrentAnimeID; }

        /*!
         *  @brief      ���ݍĐ����Ă���A�j���[�V�������擾
         *
         *  @return     �A�j���[�V������
         */
        std::string     GetAnimationName( void );

        /*!
         *  @brief      �A�j���[�V�������̎擾
         *
         *  @return     �A�j���[�V������
         */
        int             GetAnimationCount( void ) const;

        /*!
         *  @brief      �e�N�X�`���̕��擾
         *
         *  @return     �e�N�X�`���̕�
         */
        int             GetTextureWidth(void) const { return m_Texture.GetWidth(); }

        /*!
         *  @brief      �e�N�X�`���̍����擾
         *
         *  @return     �e�N�X�`���̍���
         */
        int             GetTextureHeight(void) const { return m_Texture.GetHeight(); }
 
       /*!
        *  @brief      �t���[���̕��擾
        *
        *  @return     �t���[���̕�
        */
        int             GetFrameWidth(void) const { return m_FrameWidth; }

       /*!
        *  @brief      �t���[���̍����擾
        *
        *  @return     �t���[���̍���
        */
        int             GetFrameHeight(void) const { return m_FrameHeight; }

        /*!
         *  @brief      �A�j���[�V�����̍Đ����x���擾
         *
         *  @return     �A�j���[�V�����̍Đ����x��
         */
        float           GetPlayRate(void) const { return m_PlaySpeedRate; }

        /*!
         *  @brief      �A�j���[�V�����̍Đ����x���ݒ�
         *
         *  @param[in]  rate    �A�j���[�V�����̍Đ����x��
         */
        void            SetPlayRate(float rate) { m_PlaySpeedRate = rate; }

        /*!
         *  @brief      ���݂̃A�j���[�V�����t���[���擾
         *
         *  @return     ���݂̃A�j���[�V�����t���[��
         */
        float           GetCurrentAnimationFrame(void) const { return m_CurrentFrame; }

        /*!
         *  @brief      �A�j���[�V�����t���[���ݒ�
         *
         *  @param[in]  frame   �A�j���[�V�����t���[��
         */
        void            SetAnimationFrame(float frame) { m_CurrentFrame = frame; }

        /*!
         *  @brief      ���\�[�X�n���h���擾
         *
         *  @return     ���\�[�X�n���h��
         */
        int             GetResourceHandle(void) const { return m_Texture.GetResourceHandle(); }

    private:
        /*!
         *  @brief      ASS�t�@�C���̓ǂݍ��݂Ɖ��
         *
         *  @param[in]  file_name   �A�j���[�V�����p�t�@�C����(.ass)
         */
        void    LoadASS( const std::string& file_name );

        /*!
         *  @brief      �A�j���[�V���������A�j���[�V����ID�ɕϊ�
         *
         *  @param[in]  anime_name  �A�j���[�V������
         *
         *  @return     �A�j���[�V����ID
         */
        int     ConvertAnimationNameToAnimationID( const std::string& anime_name );

        /*!
         *  @brief      �A�j���[�V�����f�[�^�\����
         */
        struct ANIMATION_DATA
        {
            //! �A�j���[�V������
            std::string         name;
            //! �t���[���f�[�^
            std::vector<int>    frames;
            //! �X�V�Ԋu(�b�P��)
            float               interval;
            //! ���[�v�t���O
            bool                loop;
        };

        /*!
         *  @brief      �A�j���[�V�����f�[�^���X�g
         */
        typedef std::vector<ANIMATION_DATA> ANIMATION_LIST;

        /*!
         *  @brief      �A�j���[�V�����X�v���C�g�L�[ID
         */
        enum class ASS_KEY
        {
            //! �g�p����t�@�C����
            FILE,
            //! �t���[���I�u�W�F�N�g
            FRAME,
            //! �t���[���̕�
            WIDTH,
            //! �t���[���̍���
            HEIGHT,
            //! ���ɕ���ł���t���[���̐�
            COLS,
            //! �c�ɕ���ł���t���[���̐�
            ROWS,
            //! �A�j���[�V�����I�u�W�F�N�g
            ANIMATIONS,
            //! �A�j���[�V�����Ŏg�p����t���[���ԍ�
            FRAMES,
            //! �A�j���[�V�����X�V�Ԋu(�b�P��)
            INTERVAL,
            //! �A�j���[�V�������[�v�t���O
            LOOP,

            //! ASS�L�[�̐�
            MAX
        };

        //! �L�[��
        static const char*          m_key_names[(int)ASS_KEY::MAX];
        //! 1�b
        static const float          m_second;
        //! �_�~�[ID
        static const int            m_dummy_anime_id;
        //! �t�@�C����
        std::string                 m_FileName;
        //! 1�t���[���̕�
        int                         m_FrameWidth;
        //! 1�t���[���̍���
        int                         m_FrameHeight;
        //! ���ɕ���ł���t���[���̐�
        int                         m_FrameCols;
        //! �c�ɕ���ł���t���[���̐�
        int                         m_FrameRows;
        //! �A�j���[�V�������X�g
        ANIMATION_LIST              m_AnimationList;
        //! ���݂̃A�j���[�V����ID
        int                         m_CurrentAnimeID;
        //! ���݂̃A�j���[�V�����t���[��
        float                       m_CurrentFrame;
        //! ���݂̃A�j���[�V�����X�V���x
        float                       m_CurrentAnimeFPS;
        //! �e�N�X�`��
        aqua::CTexture              m_Texture;
        //! �e�N�X�`���̓ǂݍ��ݔ͈�
        aqua::CRect                 m_Rect;
        //! �A�j���[�V������~�t���O
        bool                        m_StopFlag;
        //! �A�j���[�V�����̍Đ����x��
        float                       m_PlaySpeedRate;
    };
}
