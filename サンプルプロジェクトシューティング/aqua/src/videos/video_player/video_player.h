
/*!
 *  @file       video_player.h
 *  @brief      �r�f�I�v���C���[
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <string>
#include "..\..\graphics\draw_object\draw_object.h"
#include "..\..\graphics\..\mathematics\mathematics.h"
#include "..\video\video.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CVideoPlayer
     *
     *  @brief      �r�f�I�v���C���[�N���X<br>
     *              avi�`���Empg�`���ɑΉ�
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CVideoPlayer
        : public aqua::core::IDrawObject
    {
    public:
        //! �ʒu
        aqua::CVector2      position;

        /*!
         *  @brief      �R���X�g���N�^
         */
        CVideoPlayer( void );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CVideoPlayer( void ) = default;

        /*!
         *  @brief      �Đ��p�o�b�t�@�쐬
         *
         *  @param[in]  file_name   �t�@�C����
         */
        void            Create( const std::string& file_name );

        /*!
         *  @brief      �Đ��o�b�t�@�̉��
         */
        void            Delete( void );

        /*!
         *  @brief      �`��
         */
        void            Draw( void );

        /*!
         *  @brief      �Đ�
         */
        void            Play( void );

        /*!
         *  @brief      ��~
         */
        void            Stop( void );

        /*!
         *  @brief      �ꎞ��~
         */
        void            Pause(void);

        /*!
         *  @brief      �I������
         */
        bool            Finished( void );

        /*!
         *  @brief      ���\�[�X�n���h���擾
         *
         *  @return     ���\�[�X�n���h��
         */
        int             GetResourceHandle( void ) const;

    private:
        //! �r�f�I�N���X
        CVideo      m_Video;
        //! �Đ��t���O
        bool        m_PlayFlag;
    };
}
