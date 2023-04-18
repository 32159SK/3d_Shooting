
/*!
 *  @file       model.h
 *  @brief      3D���f���N���X
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/13
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "model_resource\model_resource.h"
#include "../draw_object/draw_object.h"
#include "../../mathematics/mathematics.h"

 /*!
  *  @brief      aqua���O���
  */
namespace aqua
{
    /*!
     *  @class      CModel
     *
     *  @brief      ���f���N���X
     *
     *  @author     Kazuto Shimazaki
     *
     *  @date       2023/04/13
     *
     *  @version    7.17
     */
    class CModel
        :   public core::IDrawObject , public CCollision
    {
    public:

        CVector3        position;

        CVector3        scale;

        CVector3        rotation;

        /*!
         *  @brief      �R���X�g���N�^
         */
        CModel(void);

        /*!
         *  @brief      �R�s�[�R���X�g���N�^
         *
         *  @param[in]  model     �e�N�X�`���N���X
         */
        CModel(const CModel& model);

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CModel(void) = default;

        /*!
         *  @brief      ���f���̓ǂݍ���
         *
         *  @param[in]  file_name   �t�@�C����
         */
        void    Load(const std::string& file_name);

        /*!
         *  @brief      ���f���̉��
         */
        void    Unload(void);

        /*!
         *  @brief      �`��
         */
        void    Draw(void);


        /*!
         *  @brief      ���f���̃��\�[�X�n���h���擾
         *
         *  @return     ���f���̃��\�[�X�n���h���擾
         */
        int     GetResourceHandle(void) const
        {
            if (!m_ModelResource) return AQUA_UNUSED_HANDLE;

            return m_ModelResource->GetResourceHandle();
        }


        /*!
         *  @brief      ���f���̓ǂݍ��݃`�F�b�N
         *
         *  @retval     true    �ǂݍ��ݍς�
         *  @retval     false   �ǂݍ��܂�Ă��Ȃ�
         */
        bool    IsEnable(void) const
        {
            if (!m_ModelResource) return false;

            return m_ModelResource->IsEnable();
        }


        /*!
         *  @brief      ������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  model     �e�N�X�`���N���X
         */
        CModel& operator=(const CModel& model);

    private:        

        /*!
         *  @brief      ���f���̐���
         *
         *  @param[in]  width           ����
         *  @param[in]  height          �c��
         *  @param[in]  alpha_channel   �A���t�@�`�����l��
         */
        void    Create(bool alpha_channel);

        /*!
         *  @brief      ���f���̉��
         */
        void    Delete(void);

        /*!
         *  @brief      CSurface�N���X���t�����h�o�^
         */
        friend class CSurface;

        //! �e�N�X�`�����\�[�X�N���X
        core::CModelResource* m_ModelResource;
    };
}
