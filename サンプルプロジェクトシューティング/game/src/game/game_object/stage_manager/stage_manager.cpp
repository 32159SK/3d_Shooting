
/*
 *  @file       stage_manager.cpp
 *  @brief      ステージ管理クラス
 *  @author     Kazuto Shimazaki
 *  @date       2021/06/24
 *
 *  Copyright (c) 201
 *  @since      1.03-2019, Kazuya Maruyama. All rights reserved.
 */

#include "../game_object.h"
#include "stage_manager.h"


/*
 *  コンストラクタ
 */
CStageManager::
CStageManager(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "StageManager")
{
}

/*
 *  初期化
 */
void
CStageManager::
Initialize(void)
{
}




/*
 *  更新
 */
void
CStageManager::
Update(void)
{
    IGameObject::Update();
}

/*
 *  描画
 */
void
CStageManager::
Draw(void)
{
    IGameObject::Draw();
}

/*
 *  解放
 */
void
CStageManager::
Finalize(void)
{
    IGameObject::Finalize();
}