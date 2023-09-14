
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
     *  @brief      マウスアイコン描画処理読み込み
     */
    void            MouseIconDraw(void);

    /*!
     *  @brief      チュートリアルメッセージセットアップ
     */
    void            MessageSetUp(void);

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
        LOCKON,     // チュートリアル
        SHOT,       // 射撃
        BEAM        // ビーム
    };

    static const float          m_tutorial_move_length; // チュートリアル中移動距離
    static const float          m_key_icon_size;        // キーアイコンのサイズ
    static const float          m_mouse_icon_width;     // マウスアイコンの幅
    static const std::string    m_tutorial_path;        // チュートリアルテキストデータのパス
    static const std::string    m_key_icon_path;        // キーアイコンのパス
    static const std::string    m_mouse_path;           // マウスアイコンのパス
    static const aqua::CVector2 m_icon_pos;         // キーアイコンの描画座標
    static const aqua::CVector2 m_key_icon_formation[]; // キーアイコンの並び

    int                         m_TextDrawCount;        // テキストの描画回数カウント
    float                       m_MoveLength;           // 移動距離
    bool                        m_NotBeamFiring;        // ビーム照射中確認フラグ

    STATE                       m_State;                // 状態
    TUTORIAL_PHASE              m_Phase;                // 段階
    aqua::CVector3              m_PlayerPos;            // プレイヤー座標
    aqua::CSprite               m_KeyIcon[4];           // キーアイコンスプライト(WASDで四つ)
    aqua::CSprite               m_MouseIcon[3];         // マウスアイコンスプライト(非操作クリックホイールで三つ)
    std::vector<std::string>    m_TutorialText;         // チュートリアルテキストのリスト

    CTutorialMessage*           m_TutorialMessage;      // チュートリアルテキスト描画クラス
};
