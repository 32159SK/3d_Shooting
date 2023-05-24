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
    void        Initialize(CCSVReader* csv_reader);

    /*
     *  @brief      更新
     */
    void        Update(void);

    /*
     *  @brief      描画
     */
    void        Draw(void);

    /*
     *  @brief      解放
     */
    void        Finalize(void);


    void        WaveChange(int wave);

    bool        StageObjectCollision(aqua::CVector3 position, aqua::CVector3 destination);

private:
    void        Create(void);

    static const float              m_default_size;         //!< 標準サイズ

    struct POS_NUMBER
    {
        int z = 0;
        int x = 0;
    };

    int                             m_Stage[4][10][10];

    int                             m_WaveCount;

    POS_NUMBER                      m_SwichPoint[4];

    CCSVReader* m_CSVReader;
};
