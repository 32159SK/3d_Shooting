
/*!
 *  @file       draw_object.h
 *  @brief      �`��I�u�W�F�N�g�o�^�p�C���^�[�t�F�[�X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

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
        class CGraphicsDevice;

        /*!
         *  @class      IDrawObject
         *
         *  @brief      �`��I�u�W�F�N�g�o�^�p�C���^�[�t�F�C�X�N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class IDrawObject
        {
        public:
            //! ���t���O
            bool    visible;

        protected:
            /*!
             *  @brief      �R���X�g���N�^
             */
            IDrawObject( void );

            /*!
             *  @brief      �f�X�g���N�^
             */
            virtual ~IDrawObject( void ) = default;

            /*!
             *  @brief      �X�V�C���^�[�t�F�C�X
             */
            virtual void    Update( void );

            /*!
             *  @brief      �`��C���^�[�t�F�C�X
             */
            virtual void    Draw( void );
        };
    }
}
