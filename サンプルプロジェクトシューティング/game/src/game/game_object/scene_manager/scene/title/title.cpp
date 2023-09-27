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
     */
const aqua::CVector2 CTitleScene::m_basis_position[] = {
    { aqua::CVector2(300.0f  , 600.0f) },  // 「スタート」のボタン
    { aqua::CVector2(700.0f  , 600.0f) }   // 「チュートリアル」のボタン
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

    // スタートスプライトの生成
    m_StartSprite.Create("data\\texture\\title\\start.png");
    m_StartSprite.SetCenterPosition(m_basis_position[0]);

    // チュートリアルスプライトの生成
    m_TutorialSprite.Create("data\\texture\\title\\tutorial.png");
    m_TutorialSprite.SetCenterPosition(m_basis_position[1]);

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
    // スプライトの描画
    m_BackgroundSprite.Draw();
    m_StartSprite.Draw();
    m_TutorialSprite.Draw();
}

/*
 *  解放
 */
void
CTitleScene::
Finalize(void)
{
    // スプライトの解放
    m_BackgroundSprite.Delete();
    m_StartSprite.Delete();
    m_TutorialSprite.Delete();
}


/*
 *  操作処理
 */
void CTitleScene::Operation(void)
{
    // 多用するのでnamespaceで簡略
    using namespace aqua::mouse;

    // マウス座標をVector2型で取得
    aqua::CVector2 mpos = aqua::CVector2(GetCursorPos().x, GetCursorPos().y);

    // 画像の端を格納する変数を宣言
    float top[2];
    float left[2];
    float bottom[2];
    float right[2];

    // スタート画像の端の座標を求める
    top[0] = m_StartSprite.position.y;
    left[0] = m_StartSprite.position.x;
    bottom[0] = m_StartSprite.position.y + m_StartSprite.GetTextureHeight();
    right[0] = m_StartSprite.position.x + m_StartSprite.GetTextureWidth();

    // チュートリアル画像の端の座標を求める
    top[1] = m_TutorialSprite.position.y;
    left[1] = m_TutorialSprite.position.x;
    bottom[1] = m_TutorialSprite.position.y + m_StartSprite.GetTextureHeight();
    right[1] = m_TutorialSprite.position.x + m_StartSprite.GetTextureWidth();

    // スタート画像の上で左クリックでゲームメインシーンに
    if ((mpos.x > left[0] && mpos.y > top[0] && mpos.x < right[0] && mpos.y < bottom[0]) && Released(BUTTON_ID::LEFT))
        Change(SCENE_ID::GAMEMAIN);
    // チュートリアル画像の上で左クリックでチュートリアルシーンに
    else if ((mpos.x > left[1] && mpos.y > top[1] && mpos.x < right[1] && mpos.y < bottom[1]) && Released(BUTTON_ID::LEFT))
        Change(SCENE_ID::TUTORIAL);
}