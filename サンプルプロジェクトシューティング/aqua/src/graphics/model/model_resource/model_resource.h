#pragma once

#include "../../../resources/resources.h"


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
         *  @class      CModelResource
         *
         *  @brief      ���f�����\�[�X�N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2023/04/13
         *
         *  @version    7.17
         */
        class CModelResource
            : public IResourceObject
        {
            /*!
             *  @brief      �R���X�g���N�^
             */
            CModelResource(void);

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CModelResource(void) = default;

            /*!
             *  @brief      ���f���̓ǂݍ���
             *
             *  @param[in]  file_name   �t�@�C����
             */
            void        Load(const std::string& file_name);

            /*!
             *  @brief      ���f���̕���
             *
             *  @param[in]  model   �������郂�f��
             */
            void        Duplicate(const CModelResource* model);

            /*!
             *  @brief      ���f���̉��
             */
            void        Unload(void);

            /*!
             *  @brief      ���A�j���[�V������
             */
            int         GetTotalAnimeNum(void);

        private:

            friend class CModel;
            friend class CModelManager;

            int     m_TotalAnimeNum;
        };


    }
}