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

    /*
     *  @brief      操作時の文字の規定位置
     *  @param[in]  [0] = タイトルスプライト
     *  @param[in]  [1] = 「スタート」のボタン
     *  @param[in]  [2] = 「キーマウ操作」のボタン
     *  @param[in]  [3] = 「マウス操作」のボタン
     */
const aqua::CVector2 CTitleScene::m_basis_position[] = {
    { aqua::CVector2(320.0f  , 520.0f) },  // 「キーマウ操作」のボタン
    { aqua::CVector2(640.0f  , 520.0f) }   // 「マウス操作」のボタン
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
    // 前のBGMを停止させて新規にBGM再生
    m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");
    if (m_SoundManager)
    {
        m_SoundManager->BGMStop();
        m_SoundManager->Play(SOUND_ID::b_TITLE);
    }

    // 背景スプライトの生成
    m_BackgroundSprite.Create("data\\texture\\title\\title_background.png");
    m_BackgroundSprite.position = aqua::CVector2::ZERO;

    // BGMを再生
    m_SoundManager->Play(SOUND_ID::b_TITLE);
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



    //m_LicenseLabel.Delete();
}


/*
 *  操作処理
 */
void CTitleScene::Operation(void)
{

    // Zキー  ( 決定 )
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
    {
        CDataRelay* data_relay = (CDataRelay*)aqua::FindGameObject("DataRelay");
        Change(SCENE_ID::GAMEMAIN);
    }
}