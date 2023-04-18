
/*!
 *  @file       font_manager.h
 *  @brief      �t�H���g�Ǘ��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <list>
#include <string>
#include "..\font_resource\font_resource.h"

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
         *  @class      CFontManager
         *
         *  @brief      �t�H���g�Ǘ��N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CFontManager
        {
        public:
            /*!
             *  @brief      �C���X�^���X�̎擾
             *
             *  @return     �C���X�^���X�ւ̎Q��
             */
            static CFontManager&   GetInstance( void );

            /*!
             *  @brief      �t�H���g�̐���
             *
             *  @param[in]  size        �T�C�Y
             *  @param[in]  edge_bold   �G�b�W�̑���(0 = �G�b�W�Ȃ�)
             *  @param[in]  family_id   �t�H���g��ID
             *
             *  @return     �t�H���g���\�[�X�N���X
             */
            CFontResource*  Create(int size, int edge_bold, bool anti_aliasing, aqua::FONT_FAMILY_ID family_id);

            /*!
             *  @brief      �t�H���g�̉��
             *
             *  @param[in]  font    �t�H���g���\�[�X�N���X
             */
            void            Delete( core::CFontResource* font );

            /*!
             *  @brief      �t�H���g�̌���
             *
             *  @param[in]  size_id     �T�C�YID
             *  @param[in]  edge_bold   �G�b�W�̑���(0 = �G�b�W�Ȃ�)
             *  @param[in]  family_id   �t�H���g��ID
             *
             *  @return     �t�H���g���\�[�X�N���X
             */
            CFontResource*  Find( int size, int edge_bold, aqua::FONT_FAMILY_ID family_id );

            /*!
             *  @brief      �t�H���g���X�g�̃N���A
             */
            void            Clear( void );

        private:
            /*!
             *  @brief      �R���X�g���N�^
             */
            CFontManager( void );

            /*!
             *  @brief      �R�s�[�R���X�g���N�^
             *
             *  @param[in]  rhs �R�s�[�I�u�W�F�N�g
             */
            CFontManager( const CFontManager& rhs );

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CFontManager( void ) = default;

            /*!
             *  @brief      ������Z�q
             *
             *  @param[in]  rhs ����I�u�W�F�N�g
             *
             *  @return     ���g�̃I�u�W�F�N�g
             */
            CFontManager&    operator=( const CFontManager& rhs );

            /*!
             *  @brief      �t�H���g���\�[�X���X�g
             */
            typedef std::list<CFontResource*> FONT_LIST;

            //! �t�H���g���\�[�X���X�g
            FONT_LIST      m_FontList;
        };
    }
}
