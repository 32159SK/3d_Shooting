#include "../game_main/game_main.h"
#include "result.h"
/*
 *  @file       result_scene.cpp
 *  @brief
 *  @author
 *  @date       2021/02/13
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

CResultScene::CResultScene(aqua::IGameObject* parent)
    : IScene(parent, "Result")
{
}

void CResultScene::Initialize(void)
{
    CGameMain* game_main = (CGameMain*)aqua::FindGameObject("GameMainScene");
    bool game_clear = game_main->GetGameClear();

    if (game_clear)
    {


    }
    // 背景スプライトの生成
    m_BackgroundSprite.Create("data\\texture\\result_background.png");
    m_ResultSprite[0].Create("data\\texture\\result\\game_over.png");

    m_ResultSprite[1].Create("data\\texture\\result\\retry.png");

    m_BackgroundSprite.position = aqua::CVector2::ZERO;
    m_ResultSprite[0].position = aqua::CVector2((aqua::GetWindowWidth() - m_ResultSprite[0].GetTextureWidth()) / 2.0f, 200.0f);
    m_ResultSprite[1].position = aqua::CVector2((aqua::GetWindowWidth() - m_ResultSprite[1].GetTextureWidth()) / 2.0f, 600.0f);


    

}

void CResultScene::Update(void)
{
    // 
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
        //リザルトシーンからタイトルシーンに移行
        Change(SCENE_ID::TITLE);
}

void CResultScene::Draw(void)
{
    // 背景スプライトの描画
    m_BackgroundSprite.Draw();

    for (int i = 0; i < 2; i++)
        m_ResultSprite[i].Draw();
}

void CResultScene::Finalize(void)
{
    // 背景スプライトの描画
    m_BackgroundSprite.Delete();

    for (int i = 0; i < 2; i++)
        m_ResultSprite[i].Delete();
}