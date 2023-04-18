
/*!
 *  @file       main.cpp
 *  @brief      �G���g���|�C���g
 *  @author     Kazuya Maruyama
 *  @date       2021/02/06
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "aqua.h"
#include "game\game.h"

/*!
 *  @brief      ���C���֐�
 *
 *  @param[in]  hInstance       �C���X�^���X�n���h��
 *  @param[in]  hPrevInstance   Win16����̈╨
 *  @param[in]  lpCmdLine       �R�}���h���C��������
 *  @param[in]  nCmdShow        �E�B���h�̕\�����@
 *
 *  @return     ���C���֐��̐���
 */
int WINAPI
WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    // �Q�[���N���X����
    CGame* game = aqua::CreateGameObject<CGame>( nullptr );

    // AQUA GAME LIBRARY �N��/���s
    aqua::Setup( hInstance, game );

    return 0;
}
