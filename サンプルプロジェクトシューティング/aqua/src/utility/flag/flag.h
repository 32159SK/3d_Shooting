
/*!
 *  @file       flag.h
 *  @brief      �t���O�Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

/*!
 *  @brief  aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CFlag
     *
     *  @brief      �t���O�N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CFlag
    {
    public:
        /*!
         *  @brief      �R���X�g���N�^
         */
        CFlag(void) : m_Flag(0) { }

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CFlag( void ) = default;

        /*!
         *  @brief      �t���O�̎擾
         *
         *  @return     �t���O
         */
        unsigned int    GetFlag(void) const { return m_Flag; }

        /*!
         *  @brief      �t���O�̐ݒ�
         *
         *  @param[in]  flag    �ݒ肷��t���O
         */
        void            SetFlag(unsigned int flag) { m_Flag = flag; }

        /*!
         *  @brief      �t���O�ǉ�
         *
         *  @param[in]  flag    �ǉ�����t���O
         */
        void            Add(unsigned int flag) { m_Flag |= flag; }

        /*!
         *  @brief      �t���O�폜
         *
         *  @param[in]  flag    �폜����t���O
         */
        void            Del(unsigned int flag) { m_Flag &= ~flag; }

        /*!
         *  @brief      �t���O�̃N���A
         */
        void            Clear(void) { m_Flag = 0; }

        /*!
         *  @brief      �t���O�̔�r
         *
         *  @param[in]  flag    ��r�t���O
         *
         *  @return     �t���O�Ƃ̔�r����
         *  @retval     true    �t���O�������Ă���
         *  @retval     false   �t���O�������Ă��Ȃ�
         */
        bool            IsFlag(unsigned int flag) { return (m_Flag & flag); }

    private:
        //! �t���O
        unsigned int    m_Flag;
    };
}
