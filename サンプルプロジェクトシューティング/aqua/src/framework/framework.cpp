
/*!
 *  @file       framework.cpp
 *  @brief      �t���[�����[�N
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma comment( lib, "imm32.lib" )
#pragma comment( lib, "Shlwapi.lib" )

#include <windows.h>
#include <imm.h>
#include <time.h>
#include <shlwapi.h>
#include <string>
#include <sstream>
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "framework.h"
#include "..\debug\debug.h"
#include "..\graphics\graphics.h"
#include "..\game_object\game_object.h"
#include "..\controls\controls.h"
#include "..\sounds\sounds.h"

const char*         aqua::core::CFramework::m_class_name                = "AQUA GAME LIBRARY 7.17";
const unsigned int  aqua::core::CFramework::m_width                     = 1280;
const unsigned int  aqua::core::CFramework::m_height                    = 720;
const int           aqua::core::CFramework::m_color_bit                 = 32;
const float         aqua::core::CFramework::m_one_millisecond           = 1000.0f;
const float         aqua::core::CFramework::m_max_delta_time            = 0.16f;
const float         aqua::core::CFramework::m_default_delta_time_scale  = 1.0f;
const int           aqua::core::CFramework::m_default_frame_rate        = 60;
const int           aqua::core::CFramework::m_calc_frame_count          = 60;
const int           aqua::core::CFramework::m_max_effekseer_particle    = 5000;

/*
 *  �C���X�^���X�̎擾
 */
aqua::core::CFramework&
aqua::core::CFramework::
GetInstance( void )
{
    static CFramework instance;

    return instance;
}

/*
 *  ������
 */
void
aqua::core::CFramework::
Initialize( HINSTANCE instance_handle, aqua::IGameObject* game )
{
    // �C���X�^���X�n���h���o�^
    m_hInstance = instance_handle;

    // IME���֎~����
    ImmDisableIME( 0xffffffff );

    // �����̏�����
    srand( (unsigned int)time( NULL ) );

    // ���͏����֌W������
    aqua::core::CKeyboard::GetInstance( ).Initialize( );
    aqua::core::CMouse::GetInstance( ).Initialize( );
    aqua::core::CController::GetInstance( ).Initialize( );

    // Log.txt�𐶐����Ȃ�
    SetOutApplicationLogValidFlag( FALSE );

    // �E�B���h�E����A�N�e�B�u�����X�V����
    SetAlwaysRunFlag( TRUE );

    // �E�B���h�E�e�L�X�g�̕ύX
    SetMainWindowText( m_class_name );

    // �o�b�N�o�b�t�@�T�C�Y�w��
    SetGraphMode( m_width, m_height, m_color_bit );

    // �E�B���h�E�T�C�Y�w��
    SetWindowSize( m_width, m_height );

#ifdef AQUA_DEBUG
    // �E�B���h�E���[�h�ŋN��
    ChangeWindowMode( TRUE );
#else
    // �t���X�N���[�����[�h�ŋN��
    ChangeWindowMode( FALSE );

    // �Q�[����ʂ̉𑜓x�ɍ��킹�ăt���X�N���[���ɂ���
    SetFullScreenResolutionMode( DX_FSRESOLUTIONMODE_NATIVE );
#endif

    // DirectX11�̃o�[�W�������w�肷��
    if( SetUseDirect3DVersion( DX_DIRECT3D_11 ) == AQUA_DX_ERROR )
        return;

    // DX���C�u����������
    if( DxLib_Init( ) == AQUA_DX_ERROR )
        return;

    // Effekseer������
    if( Effkseer_Init( m_max_effekseer_particle ) == AQUA_DX_ERROR )
    {
        DxLib_End( );

        return;
    }

    // �t���X�N���[���E�B���h�E�؂�ւ����Ƀ��\�[�X��������̂�h��
    SetChangeScreenModeGraphicsSystemResetFlag( FALSE );

    // DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ�
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    // Effekseer��2D�`���ݒ肷��
    Effekseer_Set2DSetting(m_width, m_height);

    // Z�o�b�t�@�̗L����
    SetUseZBuffer3D( TRUE );

    // Z�o�b�t�@�ւ̏������݂�L����
    SetWriteZBuffer3D( TRUE );

#ifdef AQUA_DEBUG
    CVisualDebugger::GetInstance().Initialize();
#endif

    // �o�b�N�o�b�t�@�ɏ�������
    SetDrawScreen( DX_SCREEN_BACK );

    // �f�t�H���g�t�H���g���G�b�W�t���ɐݒ肷��
    ChangeFontType( DX_FONTTYPE_EDGE );

    AQUA_ASSERT( game, "�Q�[���I�u�W�F�N�g�������n���Ă��������B" );

    // �Q�[���I�u�W�F�N�g�m�[�h�ݒ�
    m_GameNode = game;

    // �Q�[���I�u�W�F�N�g�m�[�h������
    m_GameNode->Initialize( );
}

/*
 *  �X�V
 */
void
aqua::core::CFramework::
Update( void )
{
    // Windows����̖��߂�����
    while( ProcessMessage( ) != AQUA_DX_ERROR )
    {
        // �t���[���J�E���g�Z�o
        CalcFrameCount( );

        // �Q�[������
        GameProcess( );

        // �t���[������
        FrameSync( );

        // Esc�L�[�ŏI��
        if( CheckHitKey( KEY_INPUT_ESCAPE ) == TRUE )
            break;
    }
}

/*
 *  ���
 */
void
aqua::core::CFramework::
Finalize( void )
{
#ifdef AQUA_DEBUG
    CVisualDebugger::GetInstance().Finalize();
#endif

    // �Q�[���I�u�W�F�N�g�m�[�h���
    m_GameNode->Finalize( );

    // ���������
    AQUA_SAFE_DELETE( m_GameNode );

    // �e�N�X�`���̑S���
    aqua::core::CTextureManager::GetInstance( ).Clear( );

    // �T�E���h�S���
    aqua::core::CSoundManager::GetInstance().Clear();

    // ���͏����֌W���
    aqua::core::CController::GetInstance( ).Finalize( );
    aqua::core::CKeyboard::GetInstance( ).Finalize( );

    // �}�X�N��ʂ��폜����
    DeleteMaskScreen();

    // Effekseer���
    Effkseer_End( );

    // DX���C�u�������
    DxLib_End( );
}

/*
 *  ���Z�b�g
 */
void
aqua::core::CFramework::
Reset( void )
{
    m_GameNode->Finalize( );

    m_GameNode->Initialize( );
}

/*
 *  �f���^�^�C���擾
 */
float
aqua::core::CFramework::
GetDeltaTime( void ) const
{
#ifdef AQUA_DEBUG
    return m_DeltaTime * m_DeltaTimeScale * core::CVisualDebugger::GetInstance( ).GetDebugDeltaTimeScale( );
#else
    return m_DeltaTime * m_DeltaTimeScale;
#endif
}

/*
 *  �f���^�^�C���{���擾
 */
float
aqua::core::CFramework::
GetDeltaTimeScale(void) const
{
#ifdef AQUA_DEBUG
    return m_DeltaTimeScale * core::CVisualDebugger::GetInstance().GetDebugDeltaTimeScale();
#else
    return m_DeltaTimeScale;
#endif
}

/*
 *  �Q�[���I�u�W�F�N�g�̌���
 */
aqua::IGameObject*
aqua::core::CFramework::
FindGameObject( const std::string& name )
{
    if( !m_GameNode ) return nullptr;

    return m_GameNode->FindChild( name );
}

/*
 *  �Q�[���I�u�W�F�N�g�̌���
 */
aqua::IGameObject*
aqua::core::CFramework::
FindGameObject( aqua::FIND_METHOD func )
{
    if( !m_GameNode ) return nullptr;

    return m_GameNode->FindChild( func );
}

/*
 *  �R���X�g���N�^
 */
aqua::core::CFramework::
CFramework( void )
    : m_hInstance( NULL )
    , m_hWindow( NULL )
    , m_WindowMode( true )
    , m_GameNode( nullptr )
    , m_FrameRate( m_default_frame_rate )
    , m_FrameCount( 0 )
    , m_Fps( 0.0f )
    , m_DeltaTime( 0.0f )
    , m_StartTime( 0 )
    , m_PrevTime( 0 )
    , m_DeltaTimeScale( m_default_delta_time_scale )
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
aqua::core::CFramework::
CFramework( const aqua::core::CFramework& rhs )
    : m_hInstance(NULL)
    , m_hWindow(NULL)
    , m_WindowMode(true)
    , m_GameNode(nullptr)
    , m_FrameRate(m_default_frame_rate)
    , m_FrameCount(0)
    , m_Fps(0.0f)
    , m_DeltaTime(0.0f)
    , m_StartTime(0)
    , m_PrevTime(0)
    , m_DeltaTimeScale(m_default_delta_time_scale)

{
    (void)rhs;
}

/*
 *  ������Z�q
 */
aqua::core::CFramework&
aqua::core::CFramework::
operator=( const aqua::core::CFramework& rhs )
{
    (void)rhs;

    return *this;
}

/*
 *  �X�V����t���[���J�E���g�̌v�Z
 */
void
aqua::core::CFramework::
CalcFrameCount( void )
{
    // ���݂̎��Ԃ��擾
    int now_time = GetNowCount( );

    // �v�Z�J�n��
    if( m_FrameCount == 0 )
    {
        m_StartTime = now_time;
    }
    // �w�肳�ꂽ�t���[���J�E���g��
    else if( m_FrameCount == m_calc_frame_count )
    {
        // �t���[���̕��ς��Z�o����FPS�����߂�
        m_Fps = m_one_millisecond / ( ( now_time - m_StartTime ) / (float)m_calc_frame_count );

        m_FrameCount = 0;

        m_StartTime = now_time;
    }

    // �t���[���J�E���g���X�V
    ++m_FrameCount;

    // �O�̏����Ƃ̎��Ԃ̍�
    int sub_time = now_time - m_PrevTime;

    // �f���^�^�C�����Z�o
    m_DeltaTime = (float)sub_time / m_one_millisecond;

    // �ő�f���^�^�C���Ő�������
    if( m_DeltaTime > m_max_delta_time )
        m_DeltaTime = m_max_delta_time;

    // ���̎��Ԃ�ۑ�
    m_PrevTime = now_time;
}

/*
 *  �X�V�t���[���̑ҋ@����
 */
void
aqua::core::CFramework::
FrameSync( void )
{
    // ���ƃt���[���v���J�n���̍����Z�o
    int tookTime = GetNowCount( ) - m_StartTime;

    // �ҋ@���Ԃ��Z�o
    int waitTime = m_FrameCount * (int)m_one_millisecond / m_FrameRate - tookTime;

    // �ҋ@���Ԃ�����΂��̕��҂��ē�������
    if( waitTime > 0 )
        WaitTimer( waitTime );
}

/*
 *  �Q�[���v���Z�X���s
 */
void
aqua::core::CFramework::
GameProcess( void )
{
    // ���͏����֌W�X�V
    aqua::core::CKeyboard::GetInstance( ).Update( );
    aqua::core::CMouse::GetInstance( ).Update( );
    aqua::core::CController::GetInstance( ).Update( );

    // �T�E���h�����X�V
    CSoundManager::GetInstance( ).Update( );

#ifdef AQUA_DEBUG
    // �r�W���A���f�o�b�K�[�擾
    core::CVisualDebugger& debug = core::CVisualDebugger::GetInstance( );

    // �f�o�b�O�X�V�E���͏���
    debug.Update( );

    // �Q�[���X�V
    if( !debug.GetDebugPauseFlag( ) )
        m_GameNode->Update();
#else
    // �Q�[���X�V
    m_GameNode->Update( );
#endif

#ifdef AQUA_DEBUG
    // �f�o�b�O���[�h�ɍ��킹�āA�G�t�F�N�g�����ׂă|�[�Y����
    GetEffekseer2DManager()->SetPausedToAllEffects(debug.GetDebugPauseFlag());
#endif

    // Effekseer�X�V
    UpdateEffekseer2D();

#ifdef AQUA_DEBUG
    // �Q�[���`��
    if (!debug.GetDebugPauseFlag())
        m_GameNode->Draw( );
#else
    // �Q�[���`��
    m_GameNode->Draw();
#endif

    // �X�N���[���V���b�g�̎B�e
    // Debug���̏����ʂ��Ȃ��悤�ɂ��̃^�C�~���O�ōs��
    if( aqua::keyboard::Trigger( aqua::keyboard::KEY_ID::F9 ) )
        ScreenShot( );

#ifdef AQUA_DEBUG
    // �f�o�b�O�`�揈��
    debug.Draw( );
#endif

    // �o�b�N�o�b�t�@�̓]��
    ScreenFlip( );
}

/*
 *  �X�N���[���V���b�g�̎B�e
 */
void
aqua::core::CFramework::
ScreenShot( void )
{
    DATEDATA dd;

    // ���݂̎��Ԏ擾
    GetDateTime( &dd ) ;

     // �t�H���_�̗L���`�F�b�N
    // �Ȃ���΍쐬
    if( !PathIsDirectory( "capture" ) )
        CreateDirectory( "capture", NULL );

    // ���t���t�@�C�����ɂ���
    std::string file_name = "capture\\";

    file_name += std::to_string( dd.Year ) + std::to_string( dd.Mon ) + std::to_string( dd.Day ) + "_";

    file_name += std::to_string( dd.Hour ) + std::to_string( dd.Min ) + std::to_string( dd.Sec ) + ".bmp";

    // �X�N���[���V���b�g�̏����o��
    SaveDrawScreenToBMP( 0, 0, m_width, m_height, file_name.c_str( ));
}
