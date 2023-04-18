
/*!
 *  @file       video_resource.h
 *  @brief      �r�f�I���\�[�X�t�@�C��
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <windows.h>
#include <string>
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
         *  @class      CVideoResource
         *
         *  @brief      �r�f�I���\�[�X�N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CVideoResource
            : public core::IResourceObject
        {
        public:
            /*!
             *  @brief      �R���X�g���N�^
             */
            CVideoResource( void );

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CVideoResource( void ) = default;

            /*!
             *  @brief      �r�f�I�t�@�C���ǂݍ���
             *
             *  @param[in]  file_name   �t�@�C����
             */
            void            Load( const std::string& file_name );

            /*!
             *  @brief      ���
             */
            void            Unload( void );
        };
    }
}
