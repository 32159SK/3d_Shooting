
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
#include"../../scene/game_main/game_main.h"

class CFloor;
class CPlayer;
class CEnemyManager;

/*
 *  @class      CTutorial
 *
 *  @brief      tutorialシーン
 */
class CTutorial
    : public CGameMain
{
public:
    /*
     *  @brief      コンストラクタ
     */
    CTutorial(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    ~CTutorial(void) = default;

    /*
     *  @brief      初期化
     */
    void            Initialize(void)override;

    /*
     *  @brief      更新
     */
    void            Update(void)override;

    /*
     *  @brief      描画
     */
    void            Draw(void)override;

    /*
     *  @brief      解放
     */
    void            Finalize(void)override;

    /*
     *  @brief      カメラ取得(外部からカメラに干渉するためのゲッター)
     */
    aqua::CCamera* GetCamera(void) { return &m_Camera; }


private:
    /*
     *  @brief      チュートリアル開始
     */
    void            TutorialStart(void);

    /*
     *  @brief      チュートリアル中
     */
    void            TutorialPlay(void);

    /*
     *  @brief      チュートリアル終了
     */
    void            TutorialFinish(void);

    /*
     *  @brief      移動チュートリアル
     */
    void            TutorialMove(void);

    /*
     *  @brief      マウスチュートリアル
     */
    void            TutorialMouse(void);

    /*
     *  @brief      ロックオンチュートリアル
     */
    void            TutorialLockOn(void);

    /*
     *  @brief      射撃チュートリアル
     */
    void            TutorialShot(void);

    /*
     *  @brief      ビームチュートリアル
     */
    void            TutorialBeam(void);

    /*!
     *  @brief      チュートリアルテキスト読み込み
     */
    void            TextDataLoad(void);

    /*!
     *  @brief      チュートリアルメッセージセットアップ
     */
    bool            MessageSetUp(void);

    // 状態
    enum class STATE
    {
        START,      // 開始
        PLAY,       // プレイ
        END         // 終了
    };

    // チュートリアル段階
    enum class TUTORIAL_PHASE
    {
        MOVE,       // 移動
        MOUSE,      // マウス操作
        SHOT,       // 射撃
        LOCKON,     // ロックオン
        BEAM        // ビーム
    };

    static const int            m_max_text_count;       // チュートリアルテキストの総数
    static const int            m_lock_on_text_num;     // ロックオンテキストの番号
    static const float          m_tutorial_move_length; // チュートリアル中移動距離
    static const float          m_mouse_move_time;      // マウスの操作時間
    static const float          m_shot_time;            // 射撃操作時間
    static const std::string    m_tutorial_path;        // チュートリアルテキストデータのパス

    int                         m_TextDrawCount;        // テキストの描画回数カウント
    float                       m_MoveLength;           // 移動距離
    bool                        m_EnemyPop;             // 敵出現確認フラグ
    bool                        m_ShotFlag;             // 射撃操作確認
    bool                        m_NotBeamFiring;        // ビーム照射中確認フラグ

    STATE                       m_State;                // 状態
    TUTORIAL_PHASE              m_Phase;                // 段階
    aqua::CVector3              m_PlayerPos;            // プレイヤー座標
    aqua::CPoint                m_MousePos;             // マウス座標
    aqua::CTimer                m_TutorialTimer;        // チュートリアル確認用タイマー
    std::vector<std::string>    m_TutorialText;         // チュートリアルテキストのリスト

    CEnemy* m_TutorialEnemy;                            // チュートリアル用敵
    CTutorialMessage*           m_TutorialMessage;      // チュートリアルテキスト描画クラス
};
