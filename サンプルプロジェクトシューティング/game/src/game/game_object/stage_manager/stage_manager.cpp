
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
#include "stage_object/brittle_block/brittle_block.h"

const float CStageManager::m_default_size = 25.0f;
const std::string CStageManager::m_file_path = "data\\csv\\stage_";

/*
 *  コンストラクタ
 */
CStageManager::
CStageManager(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "StageManager")
    , m_WaveCount(0)
    , m_EnemyCount(0)
    , m_LastCollObject(nullptr)
{
}

/*
 *  初期化
 */
void CStageManager::Initialize(void)
{
    m_Player = (CPlayer*)aqua::FindGameObject("Player");
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

    //m_EnemyCount = 0;
    // 最初のwaveでないなら一旦ステージをリセットする
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

bool CStageManager::StageObjectCollision(aqua::CVector3 position, aqua::CVector3 destination,bool this_bullet)
{
    bool collision = false;
    // (処理重そう)
    for (auto it : m_ChildObjectList)
    {
        IStageObject* stage_obj = (IStageObject*)it;
        // どれかに当たってることが確認でき次第for文を抜ける
        if (stage_obj->CollisionCheck(position, destination,this_bullet))
        {
            collision = true;
            m_LastCollObject = stage_obj;
            break;
        }
    }
    return collision;
}

void CStageManager::StageLoad(void)
{
    aqua::CCSVLoader csv;
    csv.Load(m_file_path + std::to_string(m_WaveCount) + ".csv");

    // 行
    for (int i = 0; i < 21; ++i)
        // 列
        for (int k = 0; k < 21; ++k)
            m_Stage[i][k] = std::stoi(csv.GetString(i, k));


    csv.Unload();

}

void CStageManager::Create(void)
{
    StageLoad();

    // 生成するステージオブジェクトのUTSUWAを準備
    IStageObject* stage_object = nullptr;
    STAGE_OBJECT_ID object_id = STAGE_OBJECT_ID::NULL_OBJECT;

    for (int z = 0; z < 21; ++z)
    {
        for (int x = 0; x < 21; ++x)
        {
            // オブジェクトのIDはm_Stageがintで持っているのでそれを使用
            object_id = (STAGE_OBJECT_ID)m_Stage[z][x];
            switch (object_id)
            {
            case NULL_OBJECT:  continue;  break;    // なんもないなら次へ
            case NORMAL_BLOCK: stage_object = aqua::CreateGameObject<CNormalBlock>(this);  break;
            case BRITTLE_BLOCK:stage_object = aqua::CreateGameObject<CBrittleBlock>(this); break;
            case ENEMY_POP_POS: m_EnemyPopPos.push_back(aqua::CVector3((float)x * m_default_size - m_default_size / 2.0f * 20.0f,
                0.0f, (float)(20.0f - z) * m_default_size - m_default_size / 2.0f * 20.0f)); m_EnemyCount++; continue; break;
            case PLAYER_START_POS: m_Player->SetPosition(aqua::CVector3((float)x * m_default_size - m_default_size / 2.0f * 20.0f,0.0f, (float)(20.0f - z) * m_default_size - m_default_size / 2.0f * 20.0f));; continue; break;
            default:
                break;
            }
            // 外周の壁
            if (z == 0 || z == 20 || x == 0 || x == 20)
                stage_object->SetEdge();
            stage_object->Initialize(object_id, x, z);
        }
    }
}
