/*
 *  @file       title_scene.cpp
 *  @brief      タイトルシーン
 *  @author     Miyu Hujita
 *  @date       2021/07/01
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include"..\title\title.h"
#include "..\..\..\sound_manager\sound_manager.h"

const float CTitleScene::m_un_operation_time = 0.4f;             // 操作不可能時間
const float CTitleScene::m_dump_width = 64.0f;            // 見えてない部分
const aqua::CVector2 CTitleScene::m_frame_thick = { 12.0f, 9.0f };   // 枠の太さ

    /*
     *  @brief      操作時の文字の規定位置
     *
     *  @param[in]  [0] = タイトルスプライト
     *  @param[in]  [1] = 「スタート」のボタン
     */
const aqua::CVector2 CTitleScene::m_basis_position[] = {
    { aqua::CVector2(260.0f  , 480.0f) },  // 「スタート」のボタン
};

/*
 *  コンストラクタ
 */
CTitleScene::
CTitleScene(aqua::IGameObject* parent)
    : IScene(parent, "TitleScene")
{
}

/*
 *  初期化
 */
void
CTitleScene::
Initialize(void)
{
    //// 前のBGMを停止させて新規にBGM再生
    //m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");
    //if (m_SoundManager) { m_SoundManager->BGMStop(); m_SoundManager->Play(SOUND_ID::b_TITLE); }

    // 背景スプライトの生成
    m_BackgroundSprite.Create("data\\texture\\title_background2.png");
    m_BackgroundSprite.position = aqua::CVector2::ZERO;

    // 絶対に背景かこっちかを変えてやるからな
    m_StartSprite.Create("data\\texture\\ui\\menu\\start.png");
    m_StartSprite.scale = aqua::CVector2(2.0f, 2.0f);
    m_StartSprite.position = m_basis_position[0];

}

/*
 *  更新
 */
void
CTitleScene::
Update(void)
{
    Operation();
}

/*
 *  描画
 */
void
CTitleScene::
Draw(void)
{
    // 背景スプライトの描画
    m_BackgroundSprite.Draw();


    m_StartSprite.Draw();

}

/*
 *  解放
 */
void
CTitleScene::
Finalize(void)
{
    // 背景スプライトの解放
    m_BackgroundSprite.Delete();


    m_StartSprite.Delete();

    //m_LicenseLabel.Delete();
}


/*
 *  操作処理
 */
void CTitleScene::Operation(void)
{
    // Zキー  ( 決定 )
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
        Change(SCENE_ID::GAMEMAIN);
}