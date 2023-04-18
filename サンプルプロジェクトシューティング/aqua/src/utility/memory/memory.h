
/*!
 *  @file       memory.h
 *  @brief      �������֌W
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <iostream>
#include <windows.h>
#include <crtdbg.h>
#include "..\..\debug\debug.h"

#ifdef AQUA_DEBUG
/*!
 *  @brief      ���������[�N�`�F�b�N
 */
#define AQUA_CHECK_MEMORY_LEAK      _CrtSetDbgFlag( _CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF )
#else
#define AQUA_CHECK_MEMORY_LEAK
#endif

#ifdef AQUA_DEBUG
/*!
 *  @brief      ���������[�N���Ƀt�@�C�����ƍs�ԍ���\������
 */
#define AQUA_NEW                    new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#else
#define AQUA_NEW                    new
#endif

/*!
 *  @brief      �|�C���^�ϐ�������ANULL��ݒ�
 *
 *  @param[in]  p   �������|�C���^
 */
#define AQUA_SAFE_DELETE( p )           if( ( p ) ) { delete ( p ); ( p ) = nullptr; }

/*!
 *  @brief      �|�C���^�ϐ�������ANULL��ݒ�
 *
 *  @param[in]  p   �������|�C���^
 */
#define AQUA_SAFE_DELETE_ARRAY( p )     if( ( p ) ) { delete[] ( p ); ( p ) = nullptr; }

/*!
 *  @brief      �C���^�[�t�F�[�X�N���X��������ANULL��ݒ�
 *
 *  @param[in]  p   �������C���^�[�t�F�[�X�|�C���^
 */
#define AQUA_SAFE_RELEASE( p )          if( ( p ) ) { ( p )->Release( ); ( p ) = nullptr; }
