
/*!
 *  @file       font.h
 *  @brief      �t�H���g�N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "font_resource\font_resource.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CFont
     *
     *  @brief      �t�H���g�N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CFont
    {
    public:
        /*!
         *  @brief      �R���X�g���N�^
         */
        CFont( void );

        /*!
         *  @brief      �R�s�[�R���X�g���N�^
         *
         *  @param[in]  font    �t�H���g�N���X
         */
        CFont( const CFont& font );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CFont( void ) = default;

        /*!
         *  @brief      �t�H���g�̓ǂݍ���
         *
         *  @param[in]  size        �t�H���g�T�C�Y
         *  @param[in]  edge_bold   �G�b�W�̑���
         *  @param[in]  famiry_id   �t�H���g��ID
         */
        void                Create( int size, int edge_bold, bool anti_aliasing, aqua::FONT_FAMILY_ID family_id );

        /*!
         *  @brief      �t�H���g�̉��
         */
        void                Delete( void );

        /*!
         *  @brief      �t�H���g�̃��\�[�X�n���h���擾
         *
         *  @return     �t�H���g�̃��\�[�X�n���h��
         */
        int                 GetResourceHandle(void) const
        {
            if (!m_FontResource) return AQUA_UNUSED_HANDLE;

            return m_FontResource->GetResourceHandle();
        }

        /*!
         *  @brief      �t�H���g�̍����擾
         *
         *  @return     �t�H���g�̍���
         */
        int                 GetHeight(void) const
        {
            if (!m_FontResource) return AQUA_UNUSED_HANDLE;

            return m_FontResource->GetHeight();
        }

        /*!
         *  @brief      �t�H���g�̐����`�F�b�N
         *
         *  @retval     true    �����ς�
         *  @retval     false   ��������Ă��Ȃ�
         */
        bool                IsEnable(void) const
        {
            if (!m_FontResource) return false;

            return m_FontResource->IsEnable();
        }

        /*!
         *  @brief      ������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  mesh     �t�H���g�N���X
         */
        CFont&              operator=( const aqua::CFont& font );

    private:
        //! �t�H���g���\�[�X�N���X
        core::CFontResource*       m_FontResource;
    };
}
