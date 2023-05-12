/*
 *  @file       stage_object.cpp
 *  @brief      ステージオブジェクト
 *  @author
 *  @date
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#include "../../game_object.h"
#include "stage_object.h"

/*
 *  コンストラクタ
 */
IStageObject::
IStageObject(aqua::IGameObject* parent, const std::string& name)
    : IGameObject(parent, name)
    , m_StageObjectID(NORMAL_BLOCK)
    , m_ActiveFlag(true)
    , m_CollisionFlag(false)
{
}

/*
 *  デストラクタ
 */
IStageObject::
~IStageObject(void)
{
}

/*
 *  初期化
 */
void
IStageObject::
Initialize(const STAGE_OBJECT_ID& id, int x, int z)
{
    // アクティブフラグをON
    m_ActiveFlag = true;

    // コリジョンフラグをOFF
    m_CollisionFlag = false;

}

/*
 *  更新
 */
void
IStageObject::
Update(void)
{
    // アクティブフラグOFFなら終了
    if (!m_ActiveFlag)
        return;
}

/*
 *  描画
 */
void
IStageObject::
Draw(void)
{
    // アクティブフラグOFFなら終了
    if (!m_ActiveFlag)
        return;

    m_Cube.Draw();
}

/*
 *  解放
 */
void
IStageObject::
Finalize(void)
{
    // アクティブフラグをOFF
    m_ActiveFlag = false;
}

/*
 *  ステージオブジェクトID取得
 */
STAGE_OBJECT_ID
IStageObject::
GetStageObjectID(void) const
{
    return m_StageObjectID;
}

/*
 *  ステージオブジェクトID設定
 */
void
IStageObject::
SetStageObjectID(STAGE_OBJECT_ID id)
{
    m_StageObjectID = id;
}

/*
 *  位置設定
 */
void
IStageObject::
SetPosition(const aqua::CVector3& position)
{
    m_Position = position;
}

/*
 *  アクティブ状態チェック
 */
bool
IStageObject::
IsActive(void) const
{
    return m_ActiveFlag;
}

/*
 *  アクティブフラグ設定
 */
void
IStageObject::
SetActive(bool active)
{
    m_ActiveFlag = active;
}
