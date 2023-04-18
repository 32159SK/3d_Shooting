
/*!
 *  @file       effekseer_resource.h
 *  @brief      Effekseer���\�[�X
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
     *  @brief      aqua::core���O���
     */
    namespace core
    {
        /*!
         *  @class      CEffekseerResource
         *
         *  @brief      Effekseer���\�[�X�N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CEffekseerResource
            : public core::IResourceObject
        {
        public:
            /*!
             *  @brief      �R���X�g���N�^
             */
            CEffekseerResource( void );

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CEffekseerResource( void ) = default;

            /*!
             *  @brief      Effekseer�̓ǂݍ���
             *
             *  @param[in]  file_name   �t�@�C����
             */
            void        Load( const std::string& file_name );

            /*!
             *  @brief      �e�N�X�`���̉��
             */
            void        Unload( void );

        };
    }
}
