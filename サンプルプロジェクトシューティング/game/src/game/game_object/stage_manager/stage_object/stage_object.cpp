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

const float IStageObject::m_default_size = 25.0f;
const float IStageObject::m_transition_time = 3.0f;

/*
 *  コンストラクタ
 */
IStageObject::
IStageObject(aqua::IGameObject* parent, const std::string& name)
    : IGameObject(parent, name)
    , m_StageObjectID(NORMAL_BLOCK)
    , m_ObjectState(OBJECT_STATE::GO_IN)
    , m_ActiveFlag(true)
    , m_CollisionFlag(false)
    , m_StageEdge(false)
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

    //	座標設定
    m_Position = aqua::CVector3::ZERO;

    m_Position.x = x * m_default_size - m_default_size / 2 * 20;

    m_Position.z = (20 - z) * m_default_size - m_default_size / 2 * 20;
}

/*
 *  更新
 */
void
IStageObject::
Update(void)
{
    switch (m_ObjectState)
    {
    case IStageObject::GO_IN:   GoIn(); break;
    case IStageObject::PLAY:    break;
    case IStageObject::GO_OUT:  GoOut();break;
    default:
        break;
    }

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

bool IStageObject::CollisionCheck(aqua::CVector3 position, aqua::CVector3 destination)
{
    return false;
}

void IStageObject::GoIn(void)
{
}

void IStageObject::GoOut(void)
{
}
