
/*
 *  @file       game_main.h
 *  @brief      ゲームメインシーン
 *  @author
 *  @date
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include"..\scene.h"

class CFloor;
class CPlayer;
class CEnemyManager;

 /*
  *  @class      CGameMain
  *
  *  @brief      ゲームメインシーン
  */
class CGameMain
    : public IScene
{
public:
    /*
     *  @brief      コンストラクタ
     */
    CGameMain(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    ~CGameMain(void) = default;

    /*
     *  @brief      初期化
     */
    void            Initialize(void);

    /*
     *  @brief      更新
     */
    void            Update(void);

    /*
     *  @brief      描画
     */
    void            Draw(void);

    /*
     *  @brief      解放
     */
    void            Finalize(void);

    /*
     *  @brief      カメラ取得(外部からカメラに干渉するためのゲッター)
     */
    aqua::CCamera*  GetCamera(void) { return &m_Camera; }

    /*
     *  @brief      ゲームクリアセッター
     */
    void            SetGameClear(bool game_clear) { m_GameClear = game_clear; }

protected:
    /*
     *  @brief      状態ID
     */
    enum STATE
    {
        STATE_GAME_START,       //! ゲーム開始
        STATE_GAME_PLAY,        //! ゲーム中
        STATE_GAME_FINISH,      //! ゲーム終了
    };

    static const float  m_camera_distace;       // カメラの距離
    static const float  m_camera_v_rotate;      // カメラの垂直回転

    STATE               m_State;                // 状態ID
    aqua::CCamera       m_Camera;               // カメラ
    CFloor*             m_Floor;                // 床
    CPlayer*            m_Player;               // プレイヤー
    CEnemyManager*      m_EnemyManager;         // 敵管理クラス
    CSoundManager*      m_SoundManager;         // サウンド管理クラス
private:
    /*
     *  @brief      ゲーム中
     */
    void            GamePlay(void);

    /*
     *  @brief      ゲーム終了
     */
    void            GameFinish(void);

    /*
     *  @brief      ホワイトアウト
     */
    void            WhiteOut(void);

    static const float  m_white_out_time;       // ホワイトアウトにかける時間

    bool                m_GameClear;            // ゲームクリアフラグ
    aqua::CTimer        m_WhiteOutTimer;        // ホワイトアウト用タイマー
    aqua::CSprite       m_WhiteOutSprite;       // ホワイトアウト用スプライト
};
