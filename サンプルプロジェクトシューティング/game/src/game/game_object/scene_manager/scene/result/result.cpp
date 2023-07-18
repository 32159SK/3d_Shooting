#include "../../../data_relay/data_relay.h"
#include "result.h"

/*
 *  @file       result_scene.cpp
 *  @brief
 *  @author
 *  @date       2023/07/06
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */


const std::string CResultScene::m_file_path[] =
{
    "data\\texture\\result\\",
    "game_over",
    "clear"
};

CResultScene::CResultScene(aqua::IGameObject* parent)
    : IScene(parent, "Result")
{
}

void CResultScene::Initialize(void)
{
    CDataRelay* data_relay = (CDataRelay*)aqua::FindGameObject("DataRelay");
    bool clear = data_relay->GetClearFlag();

    // boolはintで真1偽0に変換できるのでgame_clearを要素番号として活用
    std::string path = m_file_path[0] + m_file_path[(int)clear + 1];

    // 背景スプライトの生成
    m_BackgroundSprite.Create(path + "_background.png");
    m_ResultSprite[0].Create(path + ".png");
    m_ResultSprite[1].Create(path + "_retry.png");

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