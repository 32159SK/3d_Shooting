
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
#include "enemy/enemy_id.h"
#include "../ui_component/rader/rader.h"

 /*!
  *  @brief      エネミーのポップテーブル
  */
struct ENEMY_POP_LIST
{
    int   wave = 1;
    ENEMY_ID pop_e_id = ENEMY_ID::MOB;
};

/*!
 *  @brief      エネミーの情報
 */
struct ENEMY_INFO
{
    ENEMY_ID id = ENEMY_ID::MOB;
    int   life = 1;
    float width = 5.0f;
    float height = 5.0f;
    float depth = 5.0f;
    float speed = 1.0f;
    float shot_ct = 1.5f;
};


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
    void        Initialize(CBulletManager* bm, CPlayer* player,CStageManager* st_m ,CRader* rader);

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
     *  @brief      チュートリアルモード
     */
    void        SetTutorial(void) { m_TutorialMode = true; }

    /*!
     *  @brief      敵選出
     */
    CEnemy*     GetNearest(aqua::CVector3 player_pos);

    /*!
     *  @brief      ボスの部位生成
     */
    CEnemy*     CreateBossParts(aqua::CVector3 pop_pos, ENEMY_ID enemy_id);

private:
    /*!
     *  @brief      データ読み込み
     */
    void        EnemyDataLoad(void);
    /*!
     *  @brief      ウェーブ切り替え
     */
    void        WaveChange(void);

    static const int m_max_wave;                // 最大ウェーブ数
    static const int m_heal_value;              // waveクリア時の回復値
    static const std::string m_enemy_info_path; // エネミー情報のファイルパス
    static const std::string m_pop_list_path;   // 出現リストのファイルパス

    int             m_EnemyCount;               // 敵数カウント
    int             m_WaveCount;                // ウェーブ数のカウント
    bool            m_TutorialMode;             // チュートリアルモードフラグ
    bool            m_Finish;                   // 終了判定

    CPlayer*        m_Player;                   // プレイヤーのポインタ
    CBulletManager* m_BulletManagar;            // 弾管理クラスのポインタ
    CStageManager*  m_StageManager;             // ステージ管理クラスのポインタ
    CRader*         m_Rader;                    // レーダークラスのポインタ
    std::vector<ENEMY_POP_LIST> m_PopList;      // 出現リスト
    std::vector<ENEMY_INFO> m_EnemyInfo;        // エネミー情報リスト
};
