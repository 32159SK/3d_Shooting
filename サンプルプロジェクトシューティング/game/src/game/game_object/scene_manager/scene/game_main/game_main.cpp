
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

    // 弾管理クラスの生成
    CBulletManager* bm = aqua::CreateGameObject<CBulletManager>(this);

    // 敵管理クラスの生成
    m_EnemyManager = aqua::CreateGameObject<CEnemyManager>(this);

    // プレイヤーの生成
    m_Player = aqua::CreateGameObject<CPlayer>(this);

    // レーダークラスの生成
    CRader* rd = aqua::CreateGameObject<CRader>(this);
    rd->Initialize(m_Player);
    st_m->Initialize(csv_r);

    // エフェクト管理クラス
    aqua::CreateGameObject<CEffectManager>(this);

    // プレイヤーの初期化＆弾管理クラスのセット
    m_Player->Initialize(aqua::CVector3(0.0f, 0.0f, -50.0f), 10.0f, 10.0f, 10.0f, aqua::CColor::BLUE,st_m, bm);
    m_Player->SetEnemyManager(m_EnemyManager);
    // 敵管理クラスの初期化＆プレイヤー、弾管理クラスのセット
    m_EnemyManager->Initialize(csv_r, bm, m_Player, st_m, rd);
    // 弾管理クラスの初期化
    bm->Initialize(csv_r,st_m);

    m_Camera.SetCamera(50.0f, 10000.0f);
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
    m_Camera.m_Target = m_Player->GetPosition();
    float wheel_value = (float)aqua::mouse::GetWheel();
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
