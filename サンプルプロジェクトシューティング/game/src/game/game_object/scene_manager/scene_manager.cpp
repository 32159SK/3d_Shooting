
/*
 *  @file       scene_manager.cpp
 *  @brief      シーン管理
 *  @author
 *  @date
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "../game_object.h"
#include "scene_manager.h"
#include "scene/title/title.h"
#include "scene/game_main/game_main.h"
#include "scene/result/result.h"
#include "scene/tutorial/tutorial.h"

const float CSceneManager::m_fade_speed = 255.0f;

//コンストラクタ
CSceneManager::CSceneManager(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "SceneManager")
    , m_CurrentSceneID(SCENE_ID::DUMMY)
    , m_NextSceneID(SCENE_ID::DUMMY)
    , m_PushSceneID(SCENE_ID::DUMMY)
    , m_State(STATE::SCENE_IN)
    , m_PushFlag(false)
{
}

//初期化
void CSceneManager::Initialize(void)
{
    // フェード用スプライト生成
    m_FadeSprite.Create("data\\texture\\white.png");

    m_FadeSprite.color = aqua::CColor::BLACK;

    // スプラッシュシーンを始めに生成
    Create(SCENE_ID::TITLE);

    // シーンイン状態を設定
    m_State = STATE::SCENE_IN;

    // プッシュフラグOFF
    m_PushFlag = false;

}

//更新
void CSceneManager::Update(void)
{
    //状態を分岐
    switch (m_State)
    {
    case STATE::SCENE_IN:       SceneIn();         break;   //開始
    case STATE::SCENE_UPDATA:   SceneUpdate();     break;   //更新
    case STATE::SCENE_OUT:      SceneOut();        break;   //終了
    case STATE::SCENE_CHANGE:   SceneChange();     break;   //変更
    }


    IGameObject::Update();
}

//描画
void CSceneManager::Draw(void)
{
    //ゲームオブジェクトを描画
    IGameObject::Draw();

    m_FadeSprite.Draw();
}

//解放
void CSceneManager::Finalize(void)
{
    //ゲームオブジェクトを解放
    IGameObject::Finalize();

    m_FadeSprite.Delete();
}

//シーンの変更
void CSceneManager::Change(SCENE_ID id)
{
    // 次のシーンID
    m_NextSceneID = id;
}

//シーンをスタックする
void CSceneManager::Push(SCENE_ID id)
{
    // 同フレーム中にすでにプッシュされている
    if (m_PushFlag || m_PushSceneID != SCENE_ID::DUMMY) return;

    // プッシュフラグをON
    m_PushFlag = true;

    // スタックするシーンIDを保存
    m_PushSceneID = id;
}

//スタックしたシーンを取り出す
void CSceneManager::Pop(void)
{
    // 子のシーンが1つの場合はポップできない
    if (m_ChildObjectList.size() <= 1)
        return;

    // 末尾のシーンのイテレータ取得
    aqua::GAME_OBJECT_LIST::reverse_iterator it = m_ChildObjectList.rbegin();

    // シーンクラスにキャスト
    IScene* scene = (IScene*)(*it);

    // 末尾のシーンを削除対象に設定
    scene->DeleteObject();

    // ひとつ前のシーンを取得
    scene = (IScene*)(*(++it));

    // ひとつ前のシーンをアクティブ状態に変更
    scene->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);
}

//現在のシーンをリセットする
void CSceneManager::Reset(void)
{
    //次のシーンIDに現在のシーンID
    m_NextSceneID = m_CurrentSceneID;

    //現在のシーンIDにダミー
    m_CurrentSceneID = SCENE_ID::DUMMY;
}

//シーンの生成
void CSceneManager::Create(SCENE_ID id)
{
    //シーンの構造体のポインタを作成
    IScene* scene = nullptr;

    // idごとに新しくシーンを生成
    switch (id)
    {
    case SCENE_ID::TITLE:       scene = aqua::CreateGameObject<CTitleScene>(this);      break;  //タイトルシーン
    case SCENE_ID::GAMEMAIN:    scene = aqua::CreateGameObject<CGameMain>(this);        break;  //ゲームメインシーン
    case SCENE_ID::RESULT:      scene = aqua::CreateGameObject<CResultScene>(this);     break;  //リザルトシーン
    case SCENE_ID::TUTORIAL:    scene = aqua::CreateGameObject<CTutorial>(this);        break;  //チュートリアルシーン
    }

    AQUA_ASSERT(scene, "シーンが生成できませんでした。");

    // シーンを初期化
    scene->Initialize();
}

//現在のシーンを削除
void CSceneManager::Delete(void)
{
    //ゲームオブジェクトを解放
    IGameObject::Finalize();
}

//シーン開始演出
void CSceneManager::SceneIn(void)
{
    float alpha = (float)m_FadeSprite.color.alpha;

    alpha -= m_fade_speed * aqua::GetDeltaTime();

    if (alpha < 0.0f)
    {
        alpha = 0.0f;
        //状態を更新にする
        m_State = STATE::SCENE_UPDATA;
    }

    m_FadeSprite.color.alpha = (unsigned char)alpha;
}

//シーンの更新
void CSceneManager::SceneUpdate(void)
{
    // プッシュ処理が行われていた場合
    if (m_PushFlag)
    {
        // 新しいシーンを生成してスタックする
        Create(m_PushSceneID);

        // 未使用時はダミーIDを入れておく
        m_PushSceneID = SCENE_ID::DUMMY;

        // シーンのプッシュが終了した
        m_PushFlag = false;
    }

    //ゲームオブジェクトを更新
    IGameObject::Update();

    // シーンの変更を検知
    if (m_CurrentSceneID != m_NextSceneID)
        //状態を終了にする
        m_State = STATE::SCENE_OUT;
}

//シーン終了演出
void CSceneManager::SceneOut(void)
{
    float alpha = (float)m_FadeSprite.color.alpha;

    alpha += m_fade_speed * aqua::GetDeltaTime();

    if (alpha > (float)aqua::CColor::MAX_COLOR)
    {
        alpha = (float)aqua::CColor::MAX_COLOR;

        //状態を変更にする
        m_State = STATE::SCENE_CHANGE;
    }

    m_FadeSprite.color.alpha = (unsigned char)alpha;
}

//シーンの変更
void CSceneManager::SceneChange(void)
{
    // 現在のシーンを削除
    Delete();

    // 次のシーンを生成
    Create(m_NextSceneID);

    // シーンIDを保存
    m_CurrentSceneID = m_NextSceneID;

    // 状態を移行
    m_State = STATE::SCENE_IN;
}
