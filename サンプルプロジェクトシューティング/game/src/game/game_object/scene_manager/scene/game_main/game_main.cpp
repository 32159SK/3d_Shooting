
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
    // CSV読み取りクラスの生成
    CCSVReader* csv_r = aqua::CreateGameObject<CCSVReader>(this);
    // 床
    aqua::CreateGameObject<CFloor>(this);

    // 引数なしで初期化できるものはここで
    IGameObject::Initialize();

    // ステージ管理の生成
    CStageManager* st_m = aqua::CreateGameObject<CStageManager>(this);
    st_m->Initialize(csv_r);

    // 弾管理クラスの生成
    CBulletManager* bm = aqua::CreateGameObject<CBulletManager>(this);
    bm->Initialize(csv_r,st_m);

    // プレイヤーの生成
    m_Player = aqua::CreateGameObject<CPlayer>(this);

    // 敵管理クラスの生成
    m_EnemyManager = aqua::CreateGameObject<CEnemyManager>(this);

    // レーダークラスの生成
    CRader* rd = aqua::CreateGameObject<CRader>(this);
    rd->Initialize(m_Player);


    // プレイヤーの初期化＆弾管理クラスのセット
    m_Player->Initialize(aqua::CVector3(0.0f, 0.0f, -50.0f), 10.0f, 10.0f, 10.0f, aqua::CColor::BLUE,st_m, bm);

    // 敵管理クラスの初期化＆プレイヤー、弾管理クラスのセット
    m_EnemyManager->Initialize(csv_r, bm, m_Player, st_m, rd);

//    m_Camera.SetCamera(0.1, 10000.0, aqua::CVector3(0, 500.0f, -50.0f), m_Player->GetPosition());
    m_Camera.SetCamera(50.0, 10000.0);
    m_Camera.m_Target = m_Player->GetPosition();
    m_Camera.m_Distace = 100.0f;
    m_Camera.m_VRotate = aqua::DegToRad(50.0f);

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
    //m_Camera.m_Position = m_Camera.m_Target + aqua::CVector3(0.0f, 500.0f, -30.0f);
    //m_Camera.SetCamera();
    float wheel_value = aqua::mouse::GetWheel();
    if (wheel_value > 0) m_Camera.m_Distace -= 5.0f;
    else if (wheel_value < 0) m_Camera.m_Distace += 5.0f;
    m_Camera.Update();

    if (m_Player->GetDead()||m_EnemyManager->GetFinish())
        GameFinish();
}

void CGameMain::GameFinish(void)
{
    Change(SCENE_ID::RESULT);
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
