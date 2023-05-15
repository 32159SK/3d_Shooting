
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
#include "bullet/bullet.h"

 /*!
  *  @class      CBulletManager
  *
  *  @brief      エネミー管理クラス
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/04/18
  *
  *  @version    1.0
  */


class CBulletManager
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     */
    CBulletManager(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CBulletManager(void) = default;

    /*!
     *  @brief      初期化
     */
    void        Initialize(CCSVReader* csv_r);

    /*!
     *  @brief      更新
     */
    void        Update(void) override;

    /*!
     *  @brief      描画
     */
    void        Draw(void) override;

    /*!
     *  @brief      弾の生成
     */
    void        Create(aqua::CVector3 shot_pos, aqua::CVector3 shot_front, UNIT_TYPE unit_type, BULLET_TYPE bullet_type, IUnit* user);

    /*!
     *  @brief      解放
     */
    void        Finalize(void) override;

    /*!
     *  @brief      敵セッター
     */
    void        SetEnemy(CEnemy* enemy) { m_Enemy.push_back(enemy); }

    /*!
     *  @brief      自機セッター
     */
    void        SetPlayer(CPlayer* player) { m_Player = player; }

    void        EnemyReset(void) { m_Enemy.clear(); }
private:

    void        CheakHit(void);

    CCSVReader*             m_CSVReader;
    CPlayer*                m_Player;
    std::vector<BULLET_INFO> m_BulletInfo;
    std::vector<CEnemy*>    m_Enemy;
};
