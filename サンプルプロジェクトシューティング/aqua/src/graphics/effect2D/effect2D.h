
/*!
 *  @file       effect2D.h
 *  @brief      Effekseer�p2D�G�t�F�N�g
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "..\draw_object\draw_object.h"
#include "..\..\mathematics\mathematics.h"
#include ".\..\color\color.h"
#include "..\effekseer\effekseer.h"

 /*!
  *  @brief      aqua���O���
  */
namespace aqua
{
    /*!
     *  @class      CEffect2D
     *
     *  @brief      Effekseer�p2D�G�t�F�N�g�N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CEffect2D
        : public aqua::core::IDrawObject
    {
    public:
        //! �\���ʒu
        aqua::CVector2  position;
        //! �g�嗦
        aqua::CVector2  scale;
        //! ��]�l(���W�A��)
        float           rotation;
        //! �F
        aqua::CColor    color;

        /*!
         *  @brief  �R���X�g���N�^
         */
        CEffect2D(void);

        /*!
         *  @brief  �f�X�g���N�^
         */
        ~CEffect2D(void) = default;

        /*!
         *  @brief  ����
         *
         *  @param[in]  file_name   �t�@�C����
         */
        void    Create(const std::string& file_name);

        /*!
         *  @brief  ���
         */
        void    Delete(void);

        /*!
         *  @brief  �X�V
         */
        void    Update(void);

        /*!
         *  @brief  �`��
         */
        void    Draw(void);

        /*!
         *  @brief  �Đ�
         */
        void    Play(void);

        /*!
         *  @brief  ��~
         */
        void    Stop(void);

        /*!
         *  @brief  �G�t�F�N�g�I�����m
         *
         *  @retval true    �G�t�F�N�g�Đ��I��
         *  @retval false   �G�t�F�N�g�Đ���
         */
        bool    Finished(void);

        /*!
         *  @brief  �Đ����̃G�t�F�N�g�̍Đ����x�擾
         *
         *  @return �Đ����x
         */
        float   GetPlayingSpeed(void);

        /*!
         *  @brief  �Đ����̃G�t�F�N�g�̍Đ����x�ݒ�
         *
         *  @param[in]  speed   �Đ����x
         */
        void    SetPlayingSpeed(float speed);

        /*!
         *  @brief  ���\�[�X�n���h���擾
         *
         *  @return ���\�[�X�n���h��
         */
        int     GetResourceHandle( void ) const;

    private:
        //! Effekseer���\�[�X
        CEffekseer  m_Effekseer;
        //! �Đ����̃G�t�F�N�g�n���h��
        int         m_PlayingEffectHandle;
        //! �Đ����x
        float       m_PlaySpeed;
    };
}
