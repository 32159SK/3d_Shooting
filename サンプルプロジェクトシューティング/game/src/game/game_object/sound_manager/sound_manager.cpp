
/*
 *  @file       sound_manager.cpp
 *  @brief      サウンド管理
 *  @author     Kazuya Maruyama
 *  @date       2021/06/24
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#include "../game_object.h"
#include "sound_manager.h"

const std::string CSoundManager::m_sound_file_names[] =
{
    // ( b_ ) BGM
      "data\\sound\\b_title.mp3"     // タイトルBGM
    , "data\\sound\\b_game_main.mp3"   // ゲームメインBGM
    , "data\\sound\\b_game_clear.mp3"
    , "data\\sound\\b_game_over.mp3"
    // ( s_ ) SE
    , "data\\sound\\s_select.mp3"     // 選択音
    , "data\\sound\\s_shot.mp3"
    , "data\\sound\\s_charge.mp3"
    , "data\\sound\\s_beam.mp3"
    , "data\\sound\\s_damage.mp3"
    , "data\\sound\\s_dead.mp3"
    , "data\\sound\\s_boss_dead.mp3"
    , "data\\sound\\s_time_stop.mp3"
};

/*
 *  コンストラクタ
 */
CSoundManager::
CSoundManager(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "SoundManager")
    , m_SoundPlayer(nullptr)
{
}

/*
 *  初期化
 */
void
CSoundManager::
Initialize(void)
{
    if (!m_SoundPlayer) m_SoundPlayer = AQUA_NEW aqua::CSoundPlayer[(int)SOUND_ID::MAX];

    // BGMはループ再生設定
    for (int i = (int)SOUND_ID::b_TITLE; i < (int)SOUND_ID::s_SELECT; ++i)
    {
        m_SoundPlayer[i].Create(m_sound_file_names[i], true);
        m_SoundPlayer[i].SetVolume(m_bgm_volume);
    }

    // SEは単発
    for (int i = (int)SOUND_ID::s_SELECT; i < (int)SOUND_ID::MAX; ++i)
    {
        m_SoundPlayer[i].Create(m_sound_file_names[i], false);
        m_SoundPlayer[i].SetVolume(m_se_volume);
    }
}

/*
 *  解放
 */
void
CSoundManager::
Finalize(void)
{
    for (int i = 0; i < (int)SOUND_ID::MAX; ++i)
        m_SoundPlayer[i].Delete();

    AQUA_SAFE_DELETE_ARRAY(m_SoundPlayer);
}

/*
 *  サウンド再生
 */
void
CSoundManager::
Play(SOUND_ID id)
{
    if (!m_SoundPlayer) return;

    m_SoundPlayer[(int)id].Play();
}

/*
 *  サウンド再生(ボリューム指定)
 */
void
CSoundManager::
Play(SOUND_ID id, int volume)
{
    if (!m_SoundPlayer) return;

    // 音量に引数を代入
    m_SoundPlayer[(int)id].SetVolume(volume);

    // 再生
    m_SoundPlayer[(int)id].Play();
}

/*
 *  サウンド停止
 */
void
CSoundManager::
Stop(SOUND_ID id)
{
    if (!m_SoundPlayer) return;

    m_SoundPlayer[(int)id].Stop();
}

/*
 *  BGM停止
 */
void
CSoundManager::
BGMStop(void)
{
    if (!m_SoundPlayer) return;

    // 
    for (int i = (int)SOUND_ID::b_TITLE; i < (int)SOUND_ID::s_SELECT; ++i)
    {
        m_SoundPlayer[i].Stop();
    }
}

/*
 *  SE再生確認
 */
bool CSoundManager::IsPlaying(SOUND_ID id)
{
    return m_SoundPlayer[(int)id].IsPlaying();
}
