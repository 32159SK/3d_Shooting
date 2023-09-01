
/*
 *  @file       sound_manager.h
 *  @brief      サウンド管理
 *  @author     
 *  @date       2023/06/19
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"

 /*
  *  @brief      サウンドID
  */
enum SOUND_ID
{
    // (b_) BGM
    b_TITLE             // タイトル
    , b_GAME_MAIN       // ゲームメイン
    , b_GAME_CLEAR      // クリア
    , b_GAME_OVER       // ゲームオーバー

    // (s_) SE
    , s_SELECT          // 選択
    , s_SHOT            // 射撃
    , s_CHARGE          // ビームチャージ
    , s_BEAM            // ビーム発射
    , s_BROKEN          // ブロック破壊
    , s_DAMAGE          // ダメージ
    , s_DEAD            // 死亡
    , s_BOSS_DEAD       // ボス死亡
    , MAX
};

/*
 *  @class      CSoundManager
 *
 *  @brief      サウンド管理クラス
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2023/06/19
 *
 *  @since      1.0
 */
class CSoundManager
    : public aqua::IGameObject
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     */
    CSoundManager(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    ~CSoundManager(void) = default;

    /*
     *  @brief      初期化
     */
    void        Initialize(void) override;
    /*
     *  @brief      解放
     */
    void        Finalize(void) override;

    /*
     *  @brief      サウンド再生
     *
     *  @param[in]  id      サウンドID
     */
    void        Play(SOUND_ID id);

    /*
     *  @brief      サウンド再生(ボリューム指定)
     *
     *  @param[in]  id      サウンドID
     *  @param[in]  volume  音量( 0 ～ 255 )
     */
    void        Play(SOUND_ID id, int volume);

    /*
     *  @brief      サウンド停止
     *
     *  @param[in]  id      サウンドID
     */
    void        Stop(SOUND_ID id);

    /*
     *  @brief      BGM停止
     */
    void        BGMStop(void);

    /*
     *  @brief      SE再生確認
     *
     *  @param[in]  id      サウンドID
     */
    bool        IsPlaying(SOUND_ID id);

private:
    static const std::string    m_sound_file_names[];   // サウンドファイルパス
    static const int            m_bgm_volume = 172;     // BGMの基本音量
    static const int            m_se_volume = 255;      // SE, ジングルの基本音量

    aqua::CSoundPlayer* m_SoundPlayer;          // サウンドプレイヤー
};
