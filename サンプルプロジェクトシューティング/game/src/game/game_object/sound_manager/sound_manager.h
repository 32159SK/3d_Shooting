
/*
 *  @file       sound_manager.h
 *  @brief      �T�E���h�Ǘ�
 *  @author     
 *  @date       2023/06/19
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"

 /*
  *  @brief      �T�E���hID
  */
enum SOUND_ID
{
    // (b_) BGM
    b_TITLE           // �^�C�g��BGM
    , b_GAMEMAIN        // �Q�[�����C��BGM


    // (s_) SE
    , s_SELECT          // �I����
    , MAX
};

/*
 *  @class      CSoundManager
 *
 *  @brief      �T�E���h�Ǘ��N���X
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
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     */
    CSoundManager(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    ~CSoundManager(void) = default;

    /*
     *  @brief      ������
     */
    void        Initialize(void) override;
    /*
     *  @brief      ���
     */
    void        Finalize(void) override;

    /*
     *  @brief      �T�E���h�Đ�
     *
     *  @param[in]  id      �T�E���hID
     */
    void        Play(SOUND_ID id);

    /*
     *  @brief      �T�E���h�Đ�(�{�����[���w��)
     *
     *  @param[in]  id      �T�E���hID
     *  @param[in]  volume  ����( 0 �` 255 )
     */
    void        Play(SOUND_ID id, int volume);

    /*
     *  @brief      �T�E���h��~
     *
     *  @param[in]  id      �T�E���hID
     */
    void        Stop(SOUND_ID id);

    /*
     *  @brief      BGM��~
     */
    void        BGMStop(void);

    /*
     *  @brief      SE�Đ��m�F
     *
     *  @param[in]  id      �T�E���hID
     */
    bool        IsPlaying(SOUND_ID id);

private:
    static const std::string    m_sound_file_names[];   // �T�E���h�t�@�C���p�X
    static const int            m_bgm_volume = 172;     // BGM�̊�{����
    static const int            m_se_volume = 255;      // SE, �W���O���̊�{����

    aqua::CSoundPlayer* m_SoundPlayer;          // �T�E���h�v���C���[
};
