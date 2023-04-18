
/*!
 *  @file       resource_object.h
 *  @brief      ���\�[�X�I�u�W�F�N�g�p�C���^�[�t�F�[�X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <string>

/*!
 *  @brief      �g�p���Ă��Ȃ��n���h���l
 */
#define AQUA_UNUSED_HANDLE      ( -1 )

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
         *  @brief      ���\�[�X�^�C�v
         */
        enum class RESOURCE_TYPE
        {
            //! �_�~�[
            DUMMY,
            //! �ǂݍ��񂾃e�N�X�`��
            LOAD_TEXTURE,
            //! �ǂݍ��񂾃}�X�N�e�N�X�`��
            LOAD_MASK_TEXTURE,
            //! �ǂݍ��񂾃T�E���h
            LOAD_SOUND,
            //! �ǂݍ��񂾃��b�V��
            LOAD_MODEL,
            //! �ǂݍ��񂾃��[�V����
            LOAD_MOTION,
            //! �ǂݍ��񂾃V�F�[�_�v���O����
            LOAD_SHADER,
            //! �ǂݍ��񂾃r�f�I
            LOAD_VIDEO,
            //! �ǂݍ���MMD�J����
            LOAD_MMD_CAMERA,
            //! �ǂݍ���Effekseer
            LOAD_EFFEKSEER,
            //! ���������e�N�X�`��
            CREATE_TEXTURE,
            //! ���������t�H���g
            CREATE_FONT,
            //! ���������f�B���N�V���i�����C�g
            CREATE_DIRECTIONAL_LIGHT
        };

        /*!
         *  @class      IResourceObject
         *
         *  @brief      ���\�[�X�I�u�W�F�N�g�p�C���^�[�t�F�C�X�N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class IResourceObject
        {
        public:
            /*!
             *  @brief      �R���X�g���N�^
             */
            IResourceObject( void );

            /*!
             *  @brief      �R���X�g���N�^
             *
             *  @param[in]  type    ���\�[�X�^�C�v
             */
            IResourceObject( RESOURCE_TYPE type );

            /*!
             *  @brief      �R���X�g���N�^
             *
             *  @param[in]  type    ���\�[�X�^�C�v
             *  @param[in]  name    ���\�[�X��
             */
            IResourceObject( RESOURCE_TYPE type, const std::string& name );

            /*!
             *  @brief      �f�X�g���N�^
             */
            virtual ~IResourceObject( void ) = default;

            /*!
             *  @brief      ���\�[�X�^�C�v�擾
             *
             *  @return     ���\�[�X�^�C�v
             */
            RESOURCE_TYPE   GetResourceType(void) const { return m_ResourceType; }

            /*!
             *  @biref      ���\�[�X�^�C�v�ݒ�
             *
             *  @param[in]  type    ���\�[�X�^�C�v
             */
            void            SetResourceType(RESOURCE_TYPE type) { m_ResourceType = type; }

            /*!
             *  @brief      ���\�[�X�n���h���擾
             *
             *  @return     ���\�[�X�n���h��
             */
            int             GetResourceHandle(void) const { return m_ResourceHandle; }

            /*!
             *  @brief      ���\�[�X�t�@�C�����擾
             *
             *  @return     ���\�[�X�t�@�C����
             */
            std::string     GetResourceName(void) const { return m_ResourceName; }

            /*!
             *  @biref      ���\�[�X�t�@�C�����ݒ�
             *
             *  @param[in]  file_name   ���\�[�X�t�@�C����
             */
            void            SetResourceName(const std::string& file_name) { m_ResourceName = file_name; }

            /*!
             *  @brief      �Q�ƃJ�E���^���Z
             *
             *  @return     ���݂̎Q�ƃJ�E���g�l
             */
            int             AddReference(void) { return (++m_ReferenceCount); }

            /*!
             *  @brief      �Q�ƃJ�E���^���Z
             *
             *  @return     ���݂̎Q�ƃJ�E���g�l
             */
            int             RemoveReference(void) { return (--m_ReferenceCount <= 0 ? 0 : m_ReferenceCount); }

            /*!
             *  @brief      ���p�\�����ׂ�
             *
             *  @retval     true    ���p�\
             *  @retval     false   ���p�s�\
             */
            bool            IsEnable(void) const { return m_Enabel; }

        protected:
            //! ���\�[�X�^�C�v
            RESOURCE_TYPE   m_ResourceType;
            //! ���\�[�X�t�@�C����
            std::string     m_ResourceName;
            //! ���\�[�X�n���h��
            int             m_ResourceHandle;
            //! �Q�ƃJ�E���g
            int             m_ReferenceCount;
            //! ���p�\�t���O
            bool            m_Enabel;
        };
    }
}
