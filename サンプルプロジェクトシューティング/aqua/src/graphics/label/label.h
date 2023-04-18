
/*!
 *  @file       label.h
 *  @brief      ������`��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>
#include <string>
#include "..\alphablend\alphablend.h"
#include "..\font\font.h"
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
     *  @class      CLabel
     *
     *  @brief      ������`��N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CLabel
        : public aqua::core::IDrawObject
    {
    public:
        //! �e�L�X�g
        std::string         text;
        //! �ʒu
        aqua::CVector2      position;
        //! �����F
        aqua::CColor        color;
        //! �G�b�W�̐F(alpha��color�̒l�ɉe�������)
        aqua::CColor        edge_color;
        //! �A���t�@�u�����h���[�h
        aqua::ALPHABLEND    blend_mode;

        /*!
         *  @brief      �R���X�g���N�^
         */
        CLabel( void );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CLabel( void ) = default;

        /*!
         *  @brief      ����
         *
         *  @param[in]  size    �T�C�Y
         */
        void    Create( int size );

        /*!
         *  @brief      ����
         *
         *  @param[in]  size_id     �T�C�YID
         *  @param[in]  edge_bold   �G�b�W�̑����G�b�W�̑���(0 = �G�b�W�Ȃ�)
         */
        void    Create( int size, int edge_bold );

        /*!
          *  @brief      ����
          *
          *  @param[in]  size_id     �T�C�YID
          *  @param[in]  edge_bold   �G�b�W�̑����G�b�W�̑���(0 = �G�b�W�Ȃ�)
          *  @param[in]  anti_aliasing   �t�H���g��ID
          */
        void    Create( int size, int edge_bold, bool anti_aliasing );

        /*!
         *  @brief      ����
         *
         *  @param[in]  size_id     �T�C�YID
         *  @param[in]  edge_bold   �G�b�W�̑����G�b�W�̑���(0 = �G�b�W�Ȃ�)
         *  @param[in]  family_id   �t�H���g��ID
         */
        void    Create( int size, int edge_bold, bool anti_aliasing, aqua::FONT_FAMILY_ID family_id );

        /*!
         *  @brief      �`��
         */
        void    Draw( void );

        /*!
         *  @brief      �폜
         */
        void    Delete( void );

        /*!
         *  @brief      �����񕝂̎擾
         *
         *  @return     �`�悷�镶����̉���
         */
        int     GetTextWidth( void ) const;

        /*!
         *  @brief      �t�H���g�̍����擾
         *
         *  @return     �t�H���g�̍���
         */
        int     GetFontHeight( void ) const;

        /*!
         *  @brief      ���\�[�X�n���h���擾
         *
         *  @return     ���\�[�X�n���h��
         */
        int     GetResourceHandle( void ) const;


    private:
        //! �t�H���g�N���X
        aqua::CFont     m_Font;
    };
}
