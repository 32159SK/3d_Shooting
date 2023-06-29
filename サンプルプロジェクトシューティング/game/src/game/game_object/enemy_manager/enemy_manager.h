
/*!
 *  @file       enemy_manager.h
 *  @brief      エネミー管理
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/18
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "enemy/enemy.h"
#include "../ui_component/rader/rader.h"

 /*!
  *  @class      CEnemyManager
  *
  *  @brief      エネミー管理クラス
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/04/18
  *
  *  @version    1.0
  */
class CEnemyManager
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     */
    CEnemyManager(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CEnemyManager(void) = default;

    /*!
     *  @brief      初期化
     */
    void        Initialize(CCSVReader* csv_r,CBulletManager* bm, CPlayer* player,CStageManager* st_m ,CRader* rader);

    /*!
     *  @brief      更新
     */
    void        Update(void) override;

    /*!
     *  @brief      描画
     */
    void        Draw(void) override;

    /*!
     *  @brief      エネミーの生成
     */
    void        Create(aqua::CVector3 pop_pos ,ENEMY_ID enemy_id);

    /*!
     *  @brief      解放
     */
    void        Finalize(void) override;

    /*!
     *  @brief      終了確認
     */
    bool        GetFinish(void) { return m_Finish; }

    /*!
     *  @brief      敵選出
     */
    CEnemy*     GetNearest(aqua::CVector3 player_pos);

    /*!
     *  @brief      ボスの部位生成
     */
    CEnemy*     CreateBossParts(aqua::CVector3 pop_pos, ENEMY_ID enemy_id);

private:

    void        WaveChange(void);

    static const int m_max_wave;

    int             m_EnemyCount;
    int             m_WaveCount;
    bool            m_Finish;

    CCSVReader*     m_CSVReader;
    CPlayer*        m_Player;
    CBulletManager* m_BulletManagar;
    CStageManager*  m_StageManager;
    CRader*         m_Rader;
    std::vector<ENEMY_POP_LIST> m_PopList;
    std::vector<ENEMY_INFO> m_EnemyInfo;
};
