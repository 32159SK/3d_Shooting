
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

const float CGameMain::m_white_out_time = 7.0f;
const float CGameMain::m_camera_distace = 150.0f;
const float CGameMain::m_camera_v_rotate = 60.0f;

CGameMain::CGameMain(aqua::IGameObject* parent)
    : IScene(parent, "GameMainScene")
    , m_State(STATE::STATE_GAME_START)
    , m_Floor(nullptr)
    , m_Player(nullptr)
    , m_EnemyManager(nullptr)
    , m_GameClear(false)
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
    // 床の生成
    m_Floor = aqua::CreateGameObject<CFloor>(this);

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

    // エフェクト管理クラス
    aqua::CreateGameObject<CEffectManager>(this);
    // 引数なしで初期化できるものはここで
    IGameObject::Initialize();

    // レーダークラスの初期化
    rd->Initialize(m_Player);

    // プレイヤーの初期化＆敵管理クラスのセット
    m_Player->Initialize(aqua::CVector3::ZERO, 10.0f, 10.0f, 10.0f, aqua::CColor::BLUE,st_m, bm);
    m_Player->SetEnemyManager(m_EnemyManager);
    // 敵管理クラスの初期化＆プレイヤー、弾管理クラスのセット
    m_EnemyManager->Initialize(bm, m_Player, st_m, rd);

    // カメラのセットアップ
    m_Camera.SetCamera(50.0f, 10000.0f);
    m_Camera.m_Target = m_Player->GetPosition();
    m_Camera.m_Distace = m_camera_distace;
    m_Camera.m_VRotate = aqua::DegToRad(m_camera_v_rotate);

    // タイマーのセットアップ
    m_WhiteOutTimer.Setup(m_white_out_time);

    // ホワイトアウト用の画像を生成しておく
    m_WhiteOutSprite.Create("data\\texture\\white.png");
    // 画像のアルファ値を0にして最初は透明にする
    m_WhiteOutSprite.color.alpha = (unsigned char)0.0f;
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
    m_Camera.Update();

    // プレイヤーが死んだ時点でゲームを終了
    if (m_Player->GetDead())
        GameFinish();
    // ゲームクリアされたらホワイトアウト処理をする
    if (m_GameClear)
        WhiteOut();
}

void CGameMain::GameFinish(void)
{
    if (m_GameClear)
        // シーンを切り替える
        Push(SCENE_ID::RESULT);
    else
        Change(SCENE_ID::RESULT);
}

void CGameMain::WhiteOut(void)
{
    // タイマーをアップデート
    m_WhiteOutTimer.Update();

    float alpha = 0.0f;

    // イージングでアルファ値を変化させる
    alpha = aqua::easing::InCubic(m_WhiteOutTimer.GetTime(), m_WhiteOutTimer.GetLimit(), 0.0f, 255.0f);

    m_WhiteOutSprite.color.alpha = (unsigned char)alpha;

    // タイマーが終了したらゲームを終了
    if (m_WhiteOutTimer.Finished())
    {
        m_WhiteOutSprite.color.alpha = (unsigned char)255.0f;
        GameFinish();
    }
}


/*
 *  描画
 */
void
CGameMain::
Draw(void)
{
    IGameObject::Draw();
    m_WhiteOutSprite.Draw();
}

/*
 *  解放
 */
void
CGameMain::
Finalize(void)
{
    IGameObject::Finalize();
    m_WhiteOutSprite.Delete();
}
