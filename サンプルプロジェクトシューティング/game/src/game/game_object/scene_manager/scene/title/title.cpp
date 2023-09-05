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
    { aqua::CVector2(100.0f  , 400.0f) },  // タイトルスプライト
    { aqua::CVector2(300.0f  , 600.0f) }   // 「スタート」のボタン
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
    m_StartSprite.SetCenterPosition(m_basis_position[1]);

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

    // 画像の端の座標を求める
    float top = m_StartSprite.position.y;
    float left = m_StartSprite.position.x;
    float bottom = m_StartSprite.position.y + m_StartSprite.GetTextureHeight();
    float right = m_StartSprite.position.x + m_StartSprite.GetTextureWidth();

    // 画像の上で左クリックでスタート
    if ((mpos.x > left && mpos.y > top && mpos.x < right && mpos.y < bottom) && Released(BUTTON_ID::LEFT))
        Change(SCENE_ID::GAMEMAIN);
}