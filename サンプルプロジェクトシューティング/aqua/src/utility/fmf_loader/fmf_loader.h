
/*!
 *  @file       fmf_loader.h
 *  @brief      FMF���[�_�[
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <string>

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CFMFLoader
     *
     *  @brief      FMF���[�_�[�N���X
     * 
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CFMFLoader
    {
    public:
        /*!
         *  @brief      �R���X�g���N�^
         */
        CFMFLoader( void );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CFMFLoader( void ) = default;

        /*!
         *  @brief      FMF�t�@�C���ǂݍ���
         *
         *  @param[in]  file_name   �t�@�C����
         */
        void            Load( const std::string& file_name );

        /*!
         *  @brief      ���
         */
        void            Unload( void );

        /*!
         *  @brief      �f�[�^���̃T�C�Y�擾
         *
         *  @return     �f�[�^���̃T�C�Y
         */
        int             GetSize( void );

        /*!
         *  @brief      ���C���[���擾
         *
         *  @return     ���C���[��
         */
        int             GetLayerCount( void );

        /*!
         *  @brief      �}�b�v�̕��擾
         *
         *  @return     �}�b�v�̕�
         */
        int             GetMapWidth( void );

        /*!
         *  @brief      �}�b�v�̍����擾
         *
         *  @return     �}�b�v�̍���
         */
        int             GetMapHeight( void );

        /*!
         *  @brief      �`�b�v�̕��擾
         *
         *  @return     �`�b�v�̕�
         */
        int             GetChipWidth( void );

        /*!
         *  @brief      �`�b�v�̍����擾
         *
         *  @return     �`�b�v�̍���
         */
        int             GetChipHeight( void );

        /*!
         *  @brief      �f�[�^���擾
         *
         *  @return     �f�[�^��
         */
        unsigned char*  GetData( void );

        /*!
         *  @brief      1���C���[�ӂ�̃T�C�Y�擾
         *
         *  @return     1���C���[�ӂ�̃T�C�Y
         */
        int             GetLayerSize( void );

        /*!
         *  @brief      ���C���[�ʃf�[�^�擾
         *
         *  @return     ���C���[ID
         */
        unsigned char*  GetLayerData( int layer_id );

        /*!
         *  @brief      ���ɕ���ł���`�b�v�̐�
         *              �r�b�g�ɍ��킹�Đ����ς��
         *              8bit�̏ꍇ�A16��
         *              16bit�̏ꍇ�A255��
         *
         *  @return     ���ɕ���ł���`�b�v�̐�
         */
        int             GetChipLineCount( void );

    private:
        /*!
         *  @class      FMF_HEADER
         *
         *  @brief      FMF�w�b�_�\����
         * 
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        struct FMF_HEADER
        {
            //! "FMF_"
            unsigned char identifer[4];
            //! �w�b�_�������}�b�v�f�[�^�̃T�C�Y
            unsigned int  size;
            //! �}�b�v�̕�(�`�b�v��)
            unsigned int  mapWidth;
            //! �}�b�v�̍���(�`�b�v��)
            unsigned int  mapHeight;
            //! �`�b�v�̕�(�s�N�Z���P��)
            unsigned char chipWidth;
            //! �`�b�v�̍���(�s�N�Z���P��)
            unsigned char chipHeight;
            //! ���C���[��
            unsigned char layerCount;
            //! �`�b�v�̃r�b�g��(8��16)
            unsigned char bitCount;
        };

        //! �w�b�_���
        FMF_HEADER      m_Header;
        //! �f�[�^��
        unsigned char*  m_Data;
        //! �`�b�v�̕���ł��鐔
        int             m_ChipLineCount;
    };
}
