
/*!
 *  @file       timer.h
 *  @brief      �^�C�}�[�N���X
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
     *  @class      CTimer
     *
     *  @brief      �^�C�}�[�N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CTimer
    {
    public:
        /*!
         *  @brief      �R���X�g���N�^
         */
        CTimer( void );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CTimer( void ) = default;

        /*!
         *  @brief      ������
         *
         *  @param[in]  limit   �v������(�b)
         */
        void    Setup( float limit );

        /*!
         *  @brief      ������
         *
         *  @param[in]  limit   �v������(�b)
         *  @param[in]  scale   �^�C���X�P�[��(1.0f������)
         */
        void    Setup( float limit, float scale );

        /*!
         *  @brief      �X�V
         */
        void    Update( void );

        /*!
         *  @brief      ���Z�b�g
         */
        void    Reset( void );

        /*!
         *  @brief      �I������
         *
         *  @return     �w�肵�����Ԃ��o�߂���
         *  @retval     true    �o�߂���
         *  @retval     false   �o�߂��Ă��Ȃ�
         */
        bool    Finished( void ) const;

        /*!
         *  @brief      ���݂̌o�ߎ��Ԃ��擾
         *
         *  @return     ���݂̌o�ߎ���
         */
        float   GetTime( void ) const;

        /*!
         *  @brief      �w�肵�����E���Ԃ��擾
         *
         *  @return     �w�肵�����E���Ԏ���
         */
        float   GetLimit( void ) const;

        /*!
         *  @brief      ���Ԃ�ݒ�
         *
         *  @param[in]  time   ����(�b)
         */
        void    SetTime(float time);

        /*!
         *  @brief      �v�����Ԃ�ݒ�
         *
         *  @param[in]  limit   �v������(�b)
         */
        void    SetLimit( float limit );

        /*!
         *  @brief      �^�C���X�P�[�����擾
         *
         *  @return     �^�C���X�P�[��
         */
        float   GetTimeScale( void ) const;

        /*!
         *  @brief      �^�C���X�P�[����ݒ�
         *
         *  @param[in]  scale   �^�C���X�P�[��(1.0f������)
         */
        void    SetTimeScale( float scale );

    private:
        //! �����^�C���X�P�[��
        static const float  m_default_time_scale;
        //! ���݂̎���
        float               m_CurrentTime;
        //! �ݒ莞��
        float               m_LimitTime;
        //! �^�C���X�P�[��
        float               m_TimeScale;
    };
}
