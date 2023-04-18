
/*!
 *  @file       font_resource.h
 *  @brief      �t�H���g���\�[�X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "..\..\..\resources\resources.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @brief      �t�H���g��ID
     */
    enum class FONT_FAMILY_ID
    {
        //! ���C���I
        MEIRIO,
        //! MS�S�V�b�N
        MS_GOTHIC,
        //! MS����
        MS_MINCHO,
        //! HG�s����
        HG_GYOUSYO,
        //! HG�n�p�p�߯�ߑ�
        HG_SOUEIKAKUPOP,
        //! ���S�V�b�N
        YU_GOTHIC,
        //! ������
        YU_MINCHO,

        //! �t�H���g��ID��
        MAX
    };

    /*!
     *  @brief      aqua::core���O���
     */
    namespace core
    {
        /*!
         *  @class      CFontResource
         *
         *  @brief      �t�H���g���\�[�X�N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CFontResource
            : public core::IResourceObject
        {
        public:
            /*!
             *  @brief      �R���X�g���N�^
             */
            CFontResource( void );

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CFontResource( void ) = default;

            /*!
             *  @brief      �t�H���g�̐���
             *
             *  @param[in]  size        �t�H���g�T�C�Y
             *  @param[in]  edge_bold   �G�b�W�̑���(0 = �G�b�W�Ȃ�)
             *  @param[in]  famiry_id   �t�H���g��ID
             */
            void        Create(int size, int edge_bold, bool anti_aliasing, FONT_FAMILY_ID famiry_id);

            /*!
             *  @brief      �t�H���g�̍폜
             */
            void        Delete( void );

            /*!
             *  @brief      �t�H���g�̍����擾
             */
            int         GetHeight(void) const { return m_FontSize; }

            /*!
             *  @brief      �t�H���g�̔�r
             *
             *  @param[in]  font    �t�H���g���\�[�X�N���X
             *
             *  @retval     true    �����t�H���g�f�[�^
             *  @retval     false   �Ⴄ�t�H���g�f�[�^
             */
            bool        CheckFont( core::CFontResource* font );

            /*!
             *  @brief      �t�H���g�̔�r
             *
             *  @param[in]  size     �t�H���g�T�C�YID
             *  @param[in]  edge_bold   �G�b�W�̑���
             *  @param[in]  famiry_id   �t�H���g��ID
             *
             *  @retval     true    �����t�H���g�f�[�^
             *  @retval     false   �Ⴄ�t�H���g�f�[�^
             */
            bool        CheckFont( int size, int edge_bold, FONT_FAMILY_ID famiry_id );

        private:
            /*!
             *  @brief      �g�p�֎~
             */
            void        Load( const std::string& file_name );

            /*!
             *  @brief      �g�p�֎~
             */
            void        Unload( void );

            //! �t�H���g���e�[�u��
            static const std::string    m_font_family_table[(int)FONT_FAMILY_ID::MAX];
            //! �����t�H���g�T�C�Y
            static const int            m_default_font_size;
            //! �t�H���g�T�C�Y
            int                         m_FontSize;
            //! �G�b�W�̑���
            int                         m_EdgeBold;
            //! �t�H���g��ID
            FONT_FAMILY_ID              m_FontFamilyID;
        };
    }
}
