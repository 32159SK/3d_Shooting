
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
#include "bullet/bullet_info.h"


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

class CBeam;

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
    void        Initialize(void)override;

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
     *  @brief      ビームを生成しポインタを渡す
     */
    CBeam*      CreateGetBeam(aqua::CVector3 shot_pos, aqua::CVector3 shot_front, UNIT_TYPE unit_type,IUnit* user);

    /*!
     *  @brief      解放
     */
    void        Finalize(void) override;

    /*!
     *  @brief      敵セッター
     */
    void        SetEnemy(CEnemy* enemy) { m_EnemyList.push_back(enemy); }

    /*!
     *  @brief      自機セッター
     */
    void        SetPlayer(CPlayer* player) { m_Player = player; }

    /*
     *  @brief      リセット
     */
    void        EnemyReset(void);

    /*
     *  @brief      リセット
     */
    void        EnemyReset(CEnemy* enemy);

    void        WaveChange(void);

    /*
     *  @brief      弾種名取得
     */
    std::string GetBulletName(BULLET_TYPE bullet_type) { return m_BulletInfo[(int)bullet_type].bullet_name; }
private:

    /*
     *  @brief      リセット
     */
    void        BulletDataLoad(void);

    /*
     *  @brief      ヒット判定
     */
    void        CheakHit(void);

    /*
     *  @brief      ビームのヒット判定
     */
    void        CheakHitBeam(CBeam* beam,int e_count);

    static const std::string m_bullet_info_path;

    CPlayer*                m_Player;           // プレイヤークラス
    CStageManager*          m_StageManager;     // ステージ管理クラス
    CEffectManager*         m_EffectManager;    // エフェクト管理クラス
    CSoundManager*          m_SoundManager;     // サウンド管理クラス
    std::vector<BULLET_INFO> m_BulletInfo;      // 弾情報のリスト
    std::vector<CEnemy*>    m_EnemyList;        // 現在生存している敵のリスト
};
