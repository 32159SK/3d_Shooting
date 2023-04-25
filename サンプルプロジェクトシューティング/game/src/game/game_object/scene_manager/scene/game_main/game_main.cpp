
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
    , m_Player(nullptr)
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
    // 弾管理クラスの生成
    CBulletManager* bm = aqua::CreateGameObject<CBulletManager>(this);
    // プレイヤーの生成
    m_Player = aqua::CreateGameObject<CPlayer>(this);
    // 敵管理クラスの生成
    CEnemyManager* em = aqua::CreateGameObject<CEnemyManager>(this);
    
    // プレイヤーの初期化＆弾管理クラスのセット
    m_Player->Initialize(aqua::CVector3(0.0f, 0.0f, -50.0f), 10.0f, 10.0f, 10.0f, aqua::CColor::BLUE, bm);
    // 敵管理クラスの初期化＆プレイヤー、弾管理クラスのセット
    em->Initialize(bm, m_Player);

    m_Camera.SetCamera(0.1, 10000.0, aqua::CVector3(0, 100.0f, -50.0f), m_Player->GetPosition());
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
    //m_CamContorl->Move();
    m_Camera.m_Target = m_Player->GetPosition();
    m_Camera.m_Position = m_Camera.m_Target + aqua::CVector3(0.0f, 100.0f, -50.0f);
    m_Camera.SetCamera();
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
