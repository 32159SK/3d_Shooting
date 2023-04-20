
/*
 *  @file       game_main.cpp
 *  @brief      ゲームメインシーン
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/20
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#include "../../../game_object.h"
#include "game_main.h"


CGameMain::CGameMain(aqua::IGameObject* parent)
    : IScene(parent, "GameMainScene")
    , m_State(STATE::STATE_GAME_START)
{
}

/*
 *  デストラクタ
 */
CGameMain::
~CGameMain(void)
{
}

/*
 *  初期化
 */
void
CGameMain::
Initialize(void)
{


    IGameObject::Initialize();
}

/*
 *  更新
 */
void
CGameMain::
Update(void)
{
    IGameObject::Update();

    //状態を分岐
    switch (m_State)
    {
    case STATE_GAME_START:  GameStart();   break;
    case STATE_GAME_PLAY:   GamePlay();    break;
    }
    m_State = STATE_GAME_PLAY;


}

/*
 *  ゲーム開始
 */
void
CGameMain::
GameStart(void)
{


}

/*
 *  ゲーム中
 */
void
CGameMain::
GamePlay(void)
{
}

void CGameMain::GameFinish(void)
{
}


/*
 *  描画
 */
void
CGameMain::
Draw(void)
{
    IGameObject::Draw();
}

/*
 *  解放
 */
void
CGameMain::
Finalize(void)
{
    IGameObject::Finalize();
}
