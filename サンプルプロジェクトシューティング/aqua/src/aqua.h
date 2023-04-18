
/*!
 *  @file       aqua.h
 *  @brief      AQUA Game Library
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <windows.h>
#include <DxLib.h>
#include <string>
#include <list>
#include <vector>
#include "controls\controls.h"
#include "debug\debug.h"
#include "framework\framework.h"
#include "game_object\game_object.h"
#include "graphics\graphics.h"
#include "mathematics\mathematics.h"
#include "sounds\sounds.h"
#include "utility\utility.h"
#include "videos\videos.h"

/*!
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @brief      AQUA Game Library�N��/���s
     *              �g�p����ۂɕK���Ăяo�����ƁB
     *
     *  @param[in]  instance_handle     �C���X�^���X�n���h��
     *  @param[in]  game                �Q�[���N���X
     */
    void                Setup( HINSTANCE instance_handle, aqua::IGameObject* game );

    /*!
     *  @brief      �C���X�^���X�n���h���̎擾
     *
     *  @return     �C���X�^���X�n���h��
     */
    HINSTANCE           GetInstanceHandle( void );

    /*!
     *  @brief      �E�B���h�E�n���h���̎擾
     *
     *  @return     �E�B���h�E�n���h��
     */
    HWND                GetWindowHandle( void );

    /*!
     *  @brief      �E�B���h�E�̉����擾
     *
     *  @return     �E�B���h�E�̉���
     */
    unsigned int        GetWindowWidth( void );

    /*!
     *  @brief      �E�B���h�E�̏c���擾
     *
     *  @return     �E�B���h�E�̏c��
     */
    unsigned int        GetWindowHeight( void );

    /*!
     *  @brief      �f���^�^�C���擾
     *
     *  @return     �f���^�^�C��
     */
    float               GetDeltaTime( void );

    /*!
     *  @brief      �f���^�^�C��(�^�C���X�P�[���Ȃ�)�擾
     *              �f���^�^�C���͑O��̍X�V����ǂꂭ�炢�̎��Ԃ��o�߂������̒l
     *
     *  @return     �f���^�^�C��
     */
    float               GetUnscaledDeltaTime( void );

    /*!
     *  @brief      �f���^�^�C���{���擾
     *
     *  @return     �f���^�^�C���{��
     */
    float               GetDeltaTimeScale( void );

    /*!
     *  @brief      �f���^�^�C���{���ݒ�
     *
     *  @param[in]  scale   �f���^�^�C���{��
     */
    void                SetDeltaTimeScale( float scale );

    /*!
     *  @brief      �t���[�����[�g�ݒ�
     *
     *  @param[in]  frame_rate  �t���[�����[�g
     */
    void                SetFrameRate( int frame_rate );

    /*!
     *  @brief      �Q�[���I�u�W�F�N�g�̌���
     *
     *  @param[in]  name    �I�u�W�F�N�g��
     *
     *  @return     �����I�u�W�F�N�g<br>
     *              ������Ȃ������ꍇ��NULL
     */
    aqua::IGameObject*  FindGameObject( const std::string& name );

    /*!
     *  @brief      �Q�[���I�u�W�F�N�g�̌���
     *
     *  @param[in]  func    �����������\�b�h
     *
     *  @return     �����I�u�W�F�N�g<br>
     *              ������Ȃ������ꍇ��NULL
     */
    aqua::IGameObject*  FindGameObject( aqua::FIND_METHOD func );

    /*!
     *  @brief      ��ʂ̃N���A
     *
     *  @param[in]  color   �N���A�J���[
     */
    void                Clear( unsigned int color );
}
