/*
 *  @file       title_scene.cpp
 *  @brief      タイトルシーン
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/20
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include"..\title\title.h"
#include"../../../game_object.h"

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
    AQUA_DEBUG_LOG("タイトルシーン");
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
}

/*
 *  解放
 */
void
CTitleScene::
Finalize(void)
{
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