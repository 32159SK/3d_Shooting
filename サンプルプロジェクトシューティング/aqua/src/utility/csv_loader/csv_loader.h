
/*!
 *  @file       csv_loader.h
 *  @brief      CSV���[�_�[
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <vector>
#include <string>

/*!
 *  @brief  aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CCSVLoader
     *
     *  @brief      CSV���[�_�[�N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CCSVLoader
    {
    public:
        /*!
         *  @brief      �R���X�g���N�^
         */
        CCSVLoader(void);

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CCSVLoader(void) = default;

        /*!
         *  @brief      FMF�t�@�C���ǂݍ���
         *
         *  @param[in]  file_name   �t�@�C����
         */
        void        Load(const std::string& file_name);

        /*!
         *  @brief      ���
         */
        void        Unload(void);

        /*!
         *  @brief      ���ɕ���ł��鐔���擾
         *
         *  @return     ���ɕ���ł��鐔
         */
        int         GetCols(void);

        /*!
         *  @brief      �c�ɕ���ł��鐔���擾
         *
         *  @return     �c�ɕ���ł��鐔
         */
        int         GetRows(void);

        /*!
         *  @brief      �f�[�^�����擾
         *
         *  @return     �f�[�^��
         */
        int         GetDataCount(void);

        /*!
         *  @brief      �w�肳�ꂽ�f�[�^�𕶎���Ŏ擾
         *
         *  @param[in]  rows    �c
         *  @param[in]  cols    ��
         *
         *  @return     �w�肳�ꂽ�f�[�^�̕�����
         */
        std::string GetString(int rows, int cols);

       /*!
        *  @brief      �w�肳�ꂽ�f�[�^�𐮐��ɕϊ����Ď擾
        *
        *  @param[in]  rows    �c
        *  @param[in]  cols    ��
        *
        *  @return     �w�肳�ꂽ�f�[�^(����)
        */
        int         GetInteger(int rows, int cols);

       /*!
        *  @brief      �w�肳�ꂽ�f�[�^�������ɕϊ����Ď擾
        *
        *  @param[in]  rows    �c
        *  @param[in]  cols    ��
        *
        *  @return     �w�肳�ꂽ�f�[�^(����)
        */
        float       GetFloat(int rows, int cols);

    private:
        /*!
         *  @brief      CSV�f�[�^���X�g
         */
        typedef std::vector<std::string>    CSV_DATA;

        //! �f�[�^
        CSV_DATA    m_Data;
        //! ���ɕ���ł���f�[�^�̌�
        int         m_Cols;
        //! �c�ɕ���ł���f�[�^�̌�
        int         m_Rows;
    };
}
