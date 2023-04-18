
/*!
 *  @file       main.cpp
 *  @brief      エントリポイント
 *  @author     Kazuya Maruyama
 *  @date       2021/02/06
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "aqua.h"
#include "game\game.h"

/*!
 *  @brief      メイン関数
 *
 *  @param[in]  hInstance       インスタンスハンドル
 *  @param[in]  hPrevInstance   Win16時代の遺物
 *  @param[in]  lpCmdLine       コマンドライン文字列
 *  @param[in]  nCmdShow        ウィンドの表示方法
 *
 *  @return     メイン関数の成否
 */
int WINAPI
WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    // ゲームクラス生成
    CGame* game = aqua::CreateGameObject<CGame>( nullptr );

    // AQUA GAME LIBRARY 起動/実行
    aqua::Setup( hInstance, game );

    return 0;
}
