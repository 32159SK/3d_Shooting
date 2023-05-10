/*
 *  @file       title_scene.cpp
 *  @brief      タイトルシーン
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/20
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include"../result/result.h"
#include"../../../game_object.h"

 /*
  *  コンストラクタ
  */
CResultScene::
CResultScene(aqua::IGameObject* parent)
    : IScene(parent, "ResultScene")
{
}

/*
 *  初期化
 */
void
CResultScene::
Initialize(void)
{
    AQUA_DEBUG_LOG("リザルトシーン");
}

/*
 *  更新
 */
void
CResultScene::
Update(void)
{
    Operation();
}

/*
 *  描画
 */
void
CResultScene::
Draw(void)
{
}

/*
 *  解放
 */
void
CResultScene::
Finalize(void)
{
}


/*
 *  操作処理
 */
void CResultScene::Operation(void)
{
    // Zキー  ( 決定 )
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
        Change(SCENE_ID::TITLE);
}