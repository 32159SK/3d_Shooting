/*
 *  @file       stage_manager.h
 *  @brief      ステージ管理クラス
 *  @author
 *  @date       2023/05/12
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "stage_object/stage_object.h"
#include "stage_object/stage_object_id.h"


class CPlayer;

/*
 *  @class      CStageManager
 *
 *  @brief      ステージ管理クラス
 *
 *  @author     
 *
 *  @date       2023/05/12
 *
 *  @since      1.0
 */
class CStageManager : public aqua::IGameObject
{
public:

    /*!
     *  @brief      コンストラクタ
     */
    CStageManager(aqua::IGameObject* parent);


    /*
     *  @brief      デストラクタ
     */
    ~CStageManager(void) = default;

    /*
     *  @brief      初期化
     */
    void        Initialize(void)override;

    /*
     *  @brief      更新
     */
    void        Update(void)override;

    /*
     *  @brief      描画
     */
    void        Draw(void)override;

    /*
     *  @brief      解放
     */
    void        Finalize(void)override;

    /*
     *  @brief      ウェーブ切り替え
     */
    void        WaveChange(int wave);

    /*
     *  @brief      解放
     */
    bool        StageObjectCollision(aqua::CVector3 position, aqua::CVector3 destination, bool this_bullet);

    /*
     *  @brief      向き取得
     */
    aqua::CCubePrimitive::COLL_DIRE GetCollDire(void) { return m_LastCollObject->GetCollDire(); }

    /*
     *  @brief      解放
     */
    int         GetEnemyCount(void) { return m_EnemyCount; }

    /*
     *  @brief      敵出現座標
     */
    aqua::CVector3 GetEnemyPopPos(int pos_number) { return m_EnemyPopPos[pos_number]; }

private:

    void        StageLoad(void);

    void        Create(void);

    static const float              m_default_size;         //!< 標準サイズ
    static const std::string        m_file_path;
    struct POS_NUMBER
    {
        int z = 0;
        int x = 0;
    };

    int                             m_Stage[21][21];

    int                             m_WaveCount;

    int                             m_EnemyCount;

    std::vector<aqua::CVector3>     m_EnemyPopPos;

    CPlayer*                        m_Player;

    IStageObject*                   m_LastCollObject;   // 最後に接触したオブジェクト
};
