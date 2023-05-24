
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
#include "stage_object/normal_block/normal_block.h"

const float CStageManager::m_default_size = 25.0f;

/*
 *  コンストラクタ
 */
CStageManager::
CStageManager(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "StageManager")
    , m_WaveCount(0)
{
}

/*
 *  初期化
 */
void CStageManager::Initialize(CCSVReader* csv_reader)
{
    m_CSVReader = csv_reader;

    m_SwichPoint[0] = { 0,0 };
    m_SwichPoint[1] = { 10,0 };
    m_SwichPoint[2] = { 0,10 };
    m_SwichPoint[3] = { 10,10 };
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

void CStageManager::WaveChange(int wave)
{
    m_WaveCount = wave;

    if (m_WaveCount > 1)
    {

        for (auto it : m_ChildObjectList)
        {
            IStageObject* stage_obj = (IStageObject*)it;
            stage_obj->DeleteObject();
        }
    }
    
    Create();
}

bool CStageManager::StageObjectCollision(aqua::CVector3 position, aqua::CVector3 destination)
{
    bool collision = false;
    // 仮(処理重そう)
    for (auto it : m_ChildObjectList)
    {
        IStageObject* stage_obj = (IStageObject*)it;

        // どれかに当たってることが確認でき次第for文を抜ける
        if (stage_obj->CollisionCheck(position, destination))
        {
            collision = true;
            break;
        }
    }
    return collision;
}

void CStageManager::Create(void)
{
    //m_CSVReader->Initialize(FILE_TYPE::STAGE, "stage_" + std::to_string(m_WaveCount));

    int s_rand = 0;

    for (int n = 0; n < 4; ++n)
    {
        s_rand = aqua::Rand(5, 1);
        m_CSVReader->Initialize(FILE_TYPE::STAGE, "stage_parts" + std::to_string(s_rand));
        for (int z = 0; z < 10; ++z)
            for (int x = 0; x < 10; ++x)
            {
                m_Stage[n][z][x] = m_CSVReader->GetStage(z, x);
            }
    }
    // 生成するステージオブジェクトのUTSUWAを準備
    IStageObject* stage_object = nullptr;
    STAGE_OBJECT_ID object_id = STAGE_OBJECT_ID::NULL_OBJECT;

    // 外周の壁は先に生成
    for (int z = 0; z < 21; ++z)
        for (int x = 0; x < 21; ++x)
            if (z == 0 || z == 20 || x == 0 || x == 20)
            {
                stage_object = aqua::CreateGameObject<CNormalBlock>(this);
                stage_object->SetEdge();
                stage_object->Initialize(object_id, x, z);
            }

    for (int n = 0; n < 4; ++n)
    {
        for (int z = 0; z < 10; ++z)
        {
            for (int x = 0; x < 10; ++x)
            {
                // オブジェクトのIDはm_Stageがintで持っているのでそれを使用
                object_id = (STAGE_OBJECT_ID)m_Stage[n][z][x];
                switch (object_id)
                {
                case NULL_OBJECT:  continue;  break;    // なんもないなら次へ
                case NORMAL_BLOCK: stage_object = aqua::CreateGameObject<CNormalBlock>(this);  break;
                case BRITTLE_BLOCK:break;
                default:
                    break;
                }
                stage_object->Initialize(object_id, x + m_SwichPoint[n].x, z + m_SwichPoint[n].z);
            }
        }
    }
}
