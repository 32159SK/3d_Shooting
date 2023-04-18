
/*!
 *  @file       framework.h
 *  @brief      �t���[�����[�N
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <windows.h>
#include <string>
#include "..\debug\debug.h"
#include "..\game_object\game_object.h"

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
         *  @brief  �E�B���h�E�v���V�[�W���o�^�p�֐��|�C���^
         */
        typedef int (*WINDOW_PROC)( HWND hWnd, unsigned int msg, unsigned int wParam, unsigned int lParam );

        /*!
         *  @class      CFramework
         *
         *  @brief      �Q�[���t���[�����[�N�N���X
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         *
         *  @note       �V���O���g���p�^�[��
         */
        class CFramework
        {
        public:
            /*!
             *  @brief      �C���X�^���X�̎擾
             *
             *  @return     �C���X�^���X�ւ̎Q��
             */
            static CFramework&  GetInstance( void );

            /*!
             *  @brief      ������
             *
             *  @param[in]  instance_handle     �C���X�^���X�n���h��
             *  @param[in]  game                �Q�[���N���X
             */
            void                Initialize( HINSTANCE instance_handle, IGameObject* game );

            /*!
             *  @brief      �X�V
             */
            void                Update( void );

            /*!
             *  @brief      ���
             */
            void                Finalize( void );

            /*!
             *  @brief      ���Z�b�g
             */
            void                Reset( void );

            /*!
             *  @brief      �C���X�^���X�n���h���̎擾
             *
             *  @return     �C���X�^���X�n���h��
             */
            HINSTANCE           GetInstanceHandle(void) const { return m_hInstance; }

            /*!
             *  @brief      �E�B���h�E�n���h���̎擾
             *
             *  @return     �E�B���h�E�n���h��
             */
            HWND                GetWindowHandle(void) const { return m_hWindow; }

            /*!
             *  @brief      �E�B���h�E�̉����擾
             *
             *  @return     �E�B���h�E�̉���
             */
            unsigned int        GetWindowWidth(void) const { return m_width; }

            /*!
             *  @brief      �E�B���h�E�̏c���擾
             *
             *  @return     �E�B���h�E�̏c��
             */
            unsigned int        GetWindowHeight(void) const { return m_height; }

            /*!
             *  @brief      �f���^�^�C���擾
             *              �f���^�^�C���͑O��̍X�V����ǂꂭ�炢�̎��Ԃ��o�߂������̒l
             *
             *  @return     �f���^�^�C��
             */
            float               GetDeltaTime(void) const;

            /*!
             *  @brief      �f���^�^�C��(�^�C���X�P�[���Ȃ�)�擾
             *              �f���^�^�C���͑O��̍X�V����ǂꂭ�炢�̎��Ԃ��o�߂������̒l
             *
             *  @return     �f���^�^�C��
             */
            float               GetUnscaledDeltaTime(void) const { return m_DeltaTime; }

            /*!
             *  @brief      �f���^�^�C���{���擾
             *
             *  @return     �f���^�^�C���{��
             */
            float               GetDeltaTimeScale(void) const;

            /*!
             *  @brief      �f���^�^�C���{���ݒ�
             *
             *  @param[in]  scale   �f���^�^�C���{��
             */
            void                SetDeltaTimeScale(float scale) { m_DeltaTimeScale = scale; }

            /*!
             *  @brief      ���݂�FPS�擾
             *
             *  @return     ���݂�FPS
             */
            float               GetFPS(void) const { return m_Fps; }

            /*!
             *  @brief      �t���[�����[�g�̐ݒ�
             *
             *  @param[int] frame_rate  �t���[�����[�g
             */
            void                SetFrameRate(int frame_rate) { m_FrameRate = frame_rate; }

            /*!
             *  @brief      �Q�[���I�u�W�F�N�g�̌���
             *
             *  @param[in]  name    �I�u�W�F�N�g��
             *
             *  @return     �����I�u�W�F�N�g<br>
             *              ������Ȃ������ꍇ��nullptr
             */
            IGameObject*        FindGameObject( const std::string& name );

            /*!
             *  @brief      �Q�[���I�u�W�F�N�g�̌���
             *
             *  @param[in]  func    �����������\�b�h
             *
             *  @return     �����I�u�W�F�N�g<br>
             *              ������Ȃ������ꍇ��nullptr
             */
            IGameObject*        FindGameObject( aqua::FIND_METHOD func );

        private:
            /*!
             *  @brief      �R���X�g���N�^
             */
            CFramework( void );

            /*!
             *  @brief      �R�s�[�R���X�g���N�^
             *
             *  @param[in]  rhs �R�s�[�I�u�W�F�N�g
             */
            CFramework( const CFramework& rhs );

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CFramework( void ) = default;

            /*!
             *  @brief      ������Z�q
             *
             *  @param[in]  rhs ����I�u�W�F�N�g
             *
             *  @return     ���g�̃I�u�W�F�N�g
             */
            CFramework&         operator=( const CFramework& rhs );

            /*!
             *  @brief      �X�V����t���[���J�E���g�̌v�Z
             */
            void                CalcFrameCount( void );

            /*!
             *  @brief      �X�V�t���[���̓���
             */
            void                FrameSync( void );

            /*!
             *  @brief      �Q�[���v���Z�X
             */
            void                GameProcess( void );

            /*!
             *  @brief      �X�N���[���V���b�g�̎B�e
             */
            void                ScreenShot( void );

            //! �N���X�l�[��
            static const char*          m_class_name;
            //! �W���E�C���h�E�̉���
            static const unsigned int   m_width;
            //! �W���E�C���h�E�̏c��
            static const unsigned int   m_height;
            //! �J���[�r�b�g
            static const int            m_color_bit;
            //! 1�~���b
            static const float          m_one_millisecond;
            //! �ő�f���^�^�C��
            static const float          m_max_delta_time;
            //! �����̃f���^�^�C���X�P�[��
            static const float          m_default_delta_time_scale;
            //! �f�t�H���g�̃t���[�����[�g
            static const int            m_default_frame_rate;
            //! ���ς��v�Z����t���[���̐�
            static const int            m_calc_frame_count;
            //! Effekseer�Ŏg�p����p�[�e�B�N���̍ő吔
            static const int            m_max_effekseer_particle;
            //! �C���X�^���X�n���h��
            HINSTANCE                   m_hInstance;
            //! �E�B���h�E�n���h��
            HWND                        m_hWindow;
            //! �E�B���h�E���[�h�ؑփt���O
            bool                        m_WindowMode;
            //! �Q�[���I�u�W�F�N�g���[�g�m�[�h
            IGameObject*                m_GameNode;
            //! �t���[�����[�g
            int                         m_FrameRate;
            //! ���݂�FPS
            float                       m_Fps;
            //! �t���[���J�E���g
            int                         m_FrameCount;
            //! �t���[���v���J�n����
            int                         m_StartTime;
            //! 1�t���[���O�̎���
            int                         m_PrevTime;
            //! �Q�[���X�V�p�f���^�^�C��
            float                       m_DeltaTime;
            //! �f���^�^�C���{��
            float                       m_DeltaTimeScale;
        };
    }
}
