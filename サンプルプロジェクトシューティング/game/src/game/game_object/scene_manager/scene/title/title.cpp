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
    , m_OperateStyle(OPERATE_STYLE::COMPOUND)
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

    // 選択画像の生成
    m_ChoiceSprite[0].Create("data\\texture\\title\\compound_button.png");
    m_ChoiceSprite[1].Create("data\\texture\\title\\mouse_button.png");


    for (int i = 0; i < 2; ++i)
        m_ChoiceSprite[i].position = m_basis_position[i];

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


    for (int i = 0; i < 2; ++i)
        m_ChoiceSprite[i].Draw();

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


    for (int i = 0; i < 2; ++i)
        m_ChoiceSprite[i].Delete();

    //m_LicenseLabel.Delete();
}


/*
 *  操作処理
 */
void CTitleScene::Operation(void)
{

    // 二択なのでややこしい書き方はするだけ無駄と判断
    if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::RIGHT))
    {
        m_OperateStyle = OPERATE_STYLE::MOUSE_ONRY;     // 操作方法をマウスのみに
        m_SoundManager->Play(SOUND_ID::s_SELECT);
    }
    else if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::LEFT))
    {
        m_OperateStyle = OPERATE_STYLE::COMPOUND;       // 操作方法をキーマウに
        m_SoundManager->Play(SOUND_ID::s_SELECT);
    }

    // Zキー  ( 決定 )
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
    {
        CDataRelay* data_relay = (CDataRelay*)aqua::FindGameObject("DataRelay");
        data_relay->SetOPerateStyle(m_OperateStyle);
        Change(SCENE_ID::GAMEMAIN);
    }
}