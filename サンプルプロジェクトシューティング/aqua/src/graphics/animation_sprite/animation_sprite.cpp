
/*!
 *  @file       animation_sprite.cpp
 *  @brief      �A�j���[�V�����t���X�v���C�g�N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "animation_sprite.h"
#include "..\..\debug\debug.h"
#include "..\..\framework\framework.h"
#include "..\..\utility\json_loader\rapidjson\document.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>

const char*     aqua::CAnimationSprite::m_key_names[] =
{
    "file",
    "frame",
    "width",
    "height",
    "cols",
    "rows",
    "animations",
    "frames",
    "interval",
    "loop",
};

const float     aqua::CAnimationSprite::m_second            = 1.0f;
const int       aqua::CAnimationSprite::m_dummy_anime_id    = -1;

/*
 *  �R���X�g���N�^
 */
aqua::CAnimationSprite::
CAnimationSprite( void )
    : position( CVector2::ZERO )
    , anchor( CVector2::ZERO )
    , scale( CVector2::ONE )
    , rotation( 0.0f )
    , color( aqua::CColor::WHITE )
    , blend_mode( aqua::ALPHABLEND::ALPHA )
    , m_FrameWidth( 0 )
    , m_FrameHeight( 0 )
    , m_FrameCols( 0 )
    , m_FrameRows( 0 )
    , m_CurrentAnimeID( m_dummy_anime_id )
    , m_CurrentFrame( 0.0f )
    , m_CurrentAnimeFPS( 1.0f )
    , m_Rect( CRect::ZERO )
    , m_StopFlag( false )
    , m_PlaySpeedRate( 1.0f )
{
}

/*
 *  ����
 */
void
aqua::CAnimationSprite::
Create( const std::string& file_name )
{
    Create( file_name, 0 );
}

/*
 *  ����
 */
void
aqua::CAnimationSprite::
Create( const std::string& file_name, const std::string& anime_name )
{
    Delete();

    // ASS�t�@�C���̓ǂݍ��݂Ɖ��
    LoadASS( file_name );

    // �e�N�X�`���ǂݍ���
    m_Texture.Load( m_FileName );

    // �A�j���[�V������ύX
    Change( anime_name );
}

/*
 *  ����
 */
void
aqua::CAnimationSprite::
Create( const std::string& file_name, int anime_id )
{
    Delete();

    // ASS�t�@�C���̓ǂݍ��݂Ɖ��
    LoadASS( file_name );

    // �e�N�X�`���ǂݍ���
    m_Texture.Load( m_FileName );

    // �A�j���[�V������ύX
    Change( anime_id );
}

/*
 *  ���
 */
void
aqua::CAnimationSprite::
Delete( void )
{
    m_Texture.Unload( );

    m_AnimationList.clear( );

    m_FileName.clear( );

    m_FrameWidth        = 0;
    m_FrameHeight       = 0;
    m_FrameCols         = 0;
    m_FrameRows         = 0;
    m_CurrentAnimeID    = m_dummy_anime_id;
    m_CurrentFrame      = 0.0f;
    m_CurrentAnimeFPS   = 0.0f;
    m_Rect              = CRect::ZERO;
    m_StopFlag          = false;
    m_PlaySpeedRate     = 1.0f;
}

/*
 *  �X�V
 */
void
aqua::CAnimationSprite::
Update( void )
{
    // �A�j���[�V������~�t���O�������Ă�����i�߂Ȃ�
    if( m_StopFlag ) return;

    // �f���^�^�C���擾
    float delta_time = aqua::core::CFramework::GetInstance().GetDeltaTime();

    // �f���^�^�C�����g���ăA�j���[�V�����t���[�����X�V
    // �A�j���[�V�����̍Đ����x�������f
    m_CurrentFrame += m_CurrentAnimeFPS * m_PlaySpeedRate * delta_time;

    // �A�j���[�V�����̍ő�t���[���𒴂��Ă��Ȃ�
    if( m_CurrentFrame < m_AnimationList[m_CurrentAnimeID].frames.size( ) )
        return;

    // ���[�v�ݒ�ł���΃t���[����擪�ɂ��ǂ�
    // �����łȂ���΍ŏI�t���[���ŌŒ肷��
    if( m_AnimationList[m_CurrentAnimeID].loop )
        m_CurrentFrame = 0.0f;
}

/*
 *  �`��
 */
void
aqua::CAnimationSprite::
Draw( void )
{
    // �e�N�X�`�����ǂݍ��܂�Ă��Ȃ���Ε`�悵�Ȃ�
    if( !m_Texture.IsEnable( ) ) return;

    // ��\���̎��͕`�悵�Ȃ�
    if( !visible ) return;

    // �J�����g�t���[�����擾
    int index = (int)m_CurrentFrame;

    // �ő�t���[���𒴂��Ă����琧��
    if( index >= (int)m_AnimationList[m_CurrentAnimeID].frames.size( ) )
        index = (int)m_AnimationList[m_CurrentAnimeID].frames.size() - 1;

    // �w�肳�ꂽ�A�j���[�V��������`��͈͂��Z�o
    int frame = m_AnimationList[m_CurrentAnimeID].frames[index];

    m_Rect.left   = ( frame % m_FrameCols ) * m_FrameWidth;
    m_Rect.top    = ( frame / m_FrameCols ) * m_FrameHeight;
    m_Rect.right  = m_Rect.left + m_FrameWidth;
    m_Rect.bottom = m_Rect.top + m_FrameHeight;

    // �A���t�@�u�����h�ݒ�
    SetDrawBlendMode( (int)blend_mode, color.alpha );

    // �P�x�ݒ�
    SetDrawBright( color.red, color.green, color.blue );

    // �`��
    DrawRectRotaGraph3F( position.x + anchor.x, position.y + anchor.y, m_Rect.left, m_Rect.top, m_Rect.right - m_Rect.left, m_Rect.bottom - m_Rect.top, anchor.x, anchor.y, scale.x, scale.y, rotation, m_Texture.GetResourceHandle( ), TRUE );

    // �P�x���f�t�H���g�ɖ߂�
    SetDrawBright( aqua::CColor::MAX_COLOR, aqua::CColor::MAX_COLOR, aqua::CColor::MAX_COLOR );

    // �A���t�@�u�����h���[�h���f�t�H���g�ɖ߂�
    SetDrawBlendMode( (int)aqua::ALPHABLEND::ALPHA, aqua::CColor::MAX_COLOR );
}

/*
 *  �A�j���[�V�����̕ύX
 */
void
aqua::CAnimationSprite::
Change( const std::string& anime_name )
{
    Change( ConvertAnimationNameToAnimationID( anime_name ) );
}

/*
 *  �A�j���[�V�����̕ύX
 */
void
aqua::CAnimationSprite::
Change( int anime_id )
{
    // �A�j���[�V����ID�������Ȃ�ύX���Ȃ�
    if( m_CurrentAnimeID == anime_id )
        return;

    m_CurrentAnimeID = anime_id;
    m_CurrentFrame   = 0.0f;

    // �A�j���[�V�������X�g������΍Đ�FPS���Z�o
    if( m_AnimationList.size( ) )
        m_CurrentAnimeFPS = (float)( m_second / (float)m_AnimationList[m_CurrentAnimeID].interval );

    // ��~�t���O��OFF
    m_StopFlag = false;
}

/*
 *  �A�j���[�V�����̍Đ�
 */
void
aqua::CAnimationSprite::
Play( void )
{
    m_StopFlag = false;
}

/*
 *  �A�j���[�V�����̒�~
 */
void
aqua::CAnimationSprite::
Stop( void )
{
    m_StopFlag = true;
}

/*
 *  �A�j���[�V�����t���[���̃��Z�b�g
 */
void
aqua::CAnimationSprite::
ResetAnimationFrame( void )
{
    m_CurrentFrame = 0.0f;
}

/*
 *  �A�j���[�V�����̏I�����m
 */
bool
aqua::CAnimationSprite::
Finished( void )
{
    if( m_AnimationList.empty( ) )
        return false;

    // ���[�v�ݒ�̏ꍇ�A�I�����m�����Ȃ�
    if( m_AnimationList[m_CurrentAnimeID].loop )
        return false;

    // �A�j���[�V�������ŏI�t���[���ɂȂ��Ă��Ȃ�
    if( m_CurrentFrame < (float)m_AnimationList[m_CurrentAnimeID].frames.size( ) )
        return false;

    return true;
}

/*
 *  �A�j���[�V�������擾
 */
std::string
aqua::CAnimationSprite::
GetAnimationName( void )
{
    // �A�j���[�V�������X�g���Ȃ���΋�̕������Ԃ�
    if( m_AnimationList.empty( ) )
        return "";

    if( m_CurrentAnimeID < 0 || m_CurrentAnimeID >= m_AnimationList.size( ) )
        return "";

    return m_AnimationList[m_CurrentAnimeID].name;
}

/*
 *  �A�j���[�V�������̎擾
 */
int
aqua::CAnimationSprite::
GetAnimationCount( void ) const
{
    if( m_AnimationList.empty( ) )
        return 0;

    return (int)m_AnimationList.size( );
}


/*
 *  ASS�t�@�C���̓ǂݍ��݂Ɖ��
 */
void
aqua::CAnimationSprite::
LoadASS( const std::string& file_name )
{
    // �t�@�C�����J��
    std::ifstream ifs(file_name, std::ios::in);

    AQUA_ASSERT( !ifs.fail(), file_name + "�̓ǂݍ��݂Ɏ��s���܂����B" );

    // �f�[�^�̓ǂݍ���
    const std::string json( (std::istreambuf_iterator<char>( ifs ) ), std::istreambuf_iterator<char>( ) );

    // �t�@�C�������
    ifs.close( );

    // RapicJSON�h�L�������g
    rapidjson::Document doc;

    // JSON�f�[�^����͂���
    doc.Parse( json.c_str( ) );

    AQUA_ASSERT( !doc.HasParseError( ), file_name + "�̉�͂Ɏ��s���܂����B�\���Ɍ�肪����܂��B");

    // �t�@�C�����擾
    m_FileName = doc[m_key_names[(int)ASS_KEY::FILE]].GetString( );

    // �t���[���I�u�W�F�N�g�擾
    const rapidjson::Value& frame_object = doc[m_key_names[(int)ASS_KEY::FRAME]];

    // �t���[���̕�
    m_FrameWidth = frame_object[m_key_names[(int)ASS_KEY::WIDTH]].GetInt( );

    // �t���[���̍���
    m_FrameHeight = frame_object[m_key_names[(int)ASS_KEY::HEIGHT]].GetInt( );

    // ���ɕ���ł���t���[����
    m_FrameCols = frame_object[m_key_names[(int)ASS_KEY::COLS]].GetInt( );

    // �c�ɕ���ł���t���[����
    m_FrameRows = frame_object[m_key_names[(int)ASS_KEY::ROWS]].GetInt( );

    // �A�j���[�V�����I�u�W�F�N�g�擾
    const rapidjson::Value& animations_object = doc[m_key_names[(int)ASS_KEY::ANIMATIONS]];

    rapidjson::Value::ConstMemberIterator it  = animations_object.MemberBegin( );
    rapidjson::Value::ConstMemberIterator end = animations_object.MemberEnd( );

    while( it != end )
    {
        ANIMATION_DATA data;

        // ���O���擾
        data.name = it->name.GetString( );

        // �t���[�����Ȃǂ̃A�j���[�V�����f�[�^�擾
        const rapidjson::Value& animation_data = it->value;

        // �A�j���[�V�����t���[���e�[�u���擾
        const rapidjson::Value& frames = animation_data[m_key_names[(int)ASS_KEY::FRAMES]];

        for( rapidjson::SizeType i = 0; i < frames.Size( ); ++i )
            data.frames.push_back( frames[i].GetInt( ) );

        // �X�V�Ԋu�擾
        data.interval = (float)animation_data[m_key_names[(int)ASS_KEY::INTERVAL]].GetDouble( );

        // ���[�v�ݒ�擾
        data.loop = animation_data[m_key_names[(int)ASS_KEY::LOOP]].GetBool( );

        // �A�j���[�V�����f�[�^���X�g�ɒǉ�
        m_AnimationList.push_back( data );

        ++it;
    }
}
/*
 *  �A�j���[�V���������A�j���[�V����ID�ɕϊ�
 */
int
aqua::CAnimationSprite::
ConvertAnimationNameToAnimationID( const std::string& anime_name )
{
    if( m_AnimationList.empty( ) ) return 0;

    for( int i = 0; i < (int)m_AnimationList.size( ); ++i )
    {
        // ���O����v����ID��Ԃ�
        if( m_AnimationList[i].name == anime_name )
            return i;
    }

    return 0;
}
