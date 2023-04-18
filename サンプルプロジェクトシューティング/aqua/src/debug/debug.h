
/*!
 *  @file       debug.h
 *  @brief      �f�o�b�O
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <DxLib.h>
#include <string>
#include <list>

#ifdef  _DEBUG
/*!
 *  @brief  �f�o�b�O���s���}�N��<br>
 *          ���̃}�N�����L���Ȏ��ADebug�p�v���Z�X�Ńv���O���������s���܂��B
 */
#define AQUA_DEBUG

#else
/*!
 *  @brief  �������[�X���s���}�N��<br>
 *          ���̃}�N�����L���Ȏ��ARelease�p�v���Z�X�Ńv���O���������s���܂��B
 */
#define AQUA_RELEASE

#endif

/*!
 *  @brief      DXLib�G���[�l
 */
#define AQUA_DX_ERROR   ( -1 )


#ifdef  AQUA_DEBUG

/*!
 *  @brief      �A�T�[�g����
 *              �Q�[����ʏo�͗p
 *
 *  @param[in]  x       ������
 *  @param[in]  message �G���[���b�Z�[�W
 */
#define AQUA_ASSERT( x, message )       aqua::core::CVisualDebugger::GetInstance( ).VisualAssert( ( x ), ( message ), __FILE__, __LINE__ )

/*!
 *  @brief      �A�T�[�g����
 *              �Q�[����ʏo�͗p
 *
 *  @param[in]  x       ������
 *  @param[in]  message �G���[���b�Z�[�W
 */
#define AQUA_DX_ASSERT( x, message )    aqua::core::CVisualDebugger::GetInstance( ).VisualAssert( ( x ) != AQUA_DX_ERROR, ( message ), __FILE__, __LINE__ )

/*!
 *  @brief      �f�o�b�O���O�̕\��
 *              �Q�[����ʏo�́E�t�@�C���ւ̏����o��
 *
 *  @param[in]  text    ���b�Z�[�W
 */
#define AQUA_DEBUG_LOG( text )          aqua::core::CVisualDebugger::GetInstance( ).DebugLog( ( text ) )

#else

#define AQUA_ASSERT( x, type )
#define AQUA_DX_ASSERT( x, type )
#define AQUA_DEBUG_LOG( text )

#endif

#ifdef AQUA_DEBUG

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
        *  @class      CVisualDebugger
        *
        *  @brief      �r�W���A���f�o�b�K�[�N���X
        *
        *  @author     Kazuya Maruyama
        *
        *  @date       2021/03/10
        *
        *  @version    7.17
        */
        class CVisualDebugger
        {
        public:
            /*!
             *  @brief      �C���X�^���X�̎擾
             *
             *  @return     �C���X�^���X�ւ̎Q��
             */
            static CVisualDebugger&  GetInstance( void );

            /*!
             *  @brief      ������
             */
            void    Initialize( void );

            /*!
             *  @brief      �X�V
             */
            void    Update( void );

            /*!
             *  @brief      �`��
             */
            void    Draw( void );

            /*!
             *  @brief      ���
             */
            void    Finalize( void );

            /*!
             *  @brief      �A�T�[�g����
             *              �Q�[����ʏo�͗p
             *
             *  @param[in]  result      �����⌋�ʂ�n���Bfalse�ɂȂ�ƃA�T�[�g����������
             *  @param[in]  message     �G���[���b�Z�[�W
             *  @param[in]  file        �t�@�C����
             *  @param[in]  line        �s�ԍ�
             */
            void    VisualAssert( bool result, const std::string& message, const std::string& file, int line );

            /*!
             *  @brief      �f�o�b�O���O�̕\��
             *              �Q�[����ʏo�͗p
             *
             *  @param[in]  text         �e�L�X�g
             */
            void    DebugLog( const std::string& text );

            /*!
             *  @brief      �|�[�Y�t���O�擾
             *
             *  @retval     true    �|�[�Y��
             *  @retval     false   �|�[�Y���łȂ�
             */
            bool    GetDebugPauseFlag( void );

            /*!
             *  @brief      �f�o�b�O�p�f���^�^�C���X�P�[���擾
             *
             *  @return     �f�o�b�O�p�f���^�^�C���X�P�[��
             */
            float   GetDebugDeltaTimeScale( void ) const;

        private:
            /*!
             *  @brief      �R���X�g���N�^
             */
            CVisualDebugger( void );

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CVisualDebugger( void ) = default;

            /*!
             *  @brief      �R�s�[�R���X�g���N�^
             *
             *  @param[in]  rhs �R�s�[�I�u�W�F�N�g
             */
            CVisualDebugger( const CVisualDebugger& rhs );

            /*!
             *  @brief      ������Z�q
             *
             *  @param[in]  rhs ����I�u�W�F�N�g
             *
             *  @return     ���g�̃I�u�W�F�N�g
             */
            CVisualDebugger&    operator=( const CVisualDebugger& rhs );

            /*!
             *  @brief  �f�o�b�O���O�p���X�g�^
             */
            typedef std::list<std::string> DEBUG_LOG_LIST;

            //! �w�i�F
            static const unsigned int   m_background_color;
            //! �����F
            static const unsigned int   m_message_color;
            //! �f�o�b�O���O�t�@�C����
            static const char*          m_debug_log_file_name;
            //! �f�o�b�O���O��\�����鐔
            static const int            m_max_show_debug_log;
            //! �f�o�b�O�t�H���g�̐F
            static const unsigned int   m_debug_text_color;
            //! �f�o�b�O�t�H���g�̘g�̐F
            static const unsigned int   m_debug_text_edge_color;
            //! �f�o�b�O�R�}���h��
            static const int            m_max_debug_command;
            //! �f�o�b�O�R�}���h�\���ʒu
            static const int            m_debug_command_width;
            //! �f�o�b�O�R�}���h��
            static const char*          m_debug_command_names[];
            //! �����̃f���^�^�C���X�P�[��
            static const float          m_default_delta_time_scale;
            //! �ŏ��̃f���^�^�C���X�P�[��
            static const float          m_min_delta_time_scale;
            //! �ő�̃f���^�^�C���X�P�[��
            static const float          m_max_delta_time_scale;
            //! �f���^�^�C���X�P�[���̕ύX�l
            static const float          m_change_delta_time_scale;
            //! �f���^�^�C���X�P�[�����͊Ԋu
            static const int            m_delta_time_scale_input_interval;
            //! FPS�̕\���t���O
            bool                        m_ShowDebugFPS;
            //! �f�o�b�O�w���v�\���t���O
            bool                        m_ShowDebugHelp;
            //! �f�o�b�O���O�\���t���O
            bool                        m_ShowDebugLog;
            //! �f�o�b�O�p�|�[�Y�t���O
            bool                        m_DebugPauseFlag;
            //! �f�o�b�O�p�f���^�^�C���{��
            float                       m_DebugDeltaTimeScale;
            //! �f�o�b�O���O���X�g
            DEBUG_LOG_LIST              m_DebugLogList;
            //! �f�o�b�O���O�����o���p�t�@�C��
            FILE*                       m_DebugLogFile;
            //! �f���^�^�C���X�P�[�����͎���
            int                         m_DeltaTimeScaleInputTime;
        };
    }
}

#endif
