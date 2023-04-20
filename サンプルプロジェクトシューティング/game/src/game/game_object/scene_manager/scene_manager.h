
/*
 *  @file       scene_manager.h
 *  @brief      �V�[���Ǘ�
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/20
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "scene\scene_id.h"
 /*
  *  @class      CSceneManager
  *
  *  @brief      �V�[���Ǘ��N���X
  *
  *  @author
  *
  *  @date
  *
  *  @version    1.0
  */
class CSceneManager
    : public aqua::IGameObject
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent  �e�I�u�W�F�N�g
     */
    CSceneManager(aqua::IGameObject* parent);

    /*
     *  @brief      �f�X�g���N�^
     */
    ~CSceneManager(void) = default;

    /*
     *  @brief      ������
     */
    void        Initialize(void) override;

    /*
     *  @brief      �X�V
     */
    void        Update(void) override;

    /*
     *  @brief      �`��
     */
    void        Draw(void) override;

    /*
     *  @brief      ���
     */
    void        Finalize(void) override;

    /*
     *  @brief      �V�[���̕ύX
     *
     *  @param[in]  id  �V�[��ID
     */
    void        Change(SCENE_ID id);

    /*
     *  @brief      �V�[�����X�^�b�N����
     *
     *  @param[in]  id  �V�[��ID
     */
    void        Push(SCENE_ID id);

    /*
     *  @brief      �X�^�b�N�����V�[�������o��
     */
    void        Pop(void);

    /*
     *  @brief      ���݂̃V�[�������Z�b�g����
     */
    void        Reset(void);

private:
    /*
     *  @brief      ���ID
     */
    enum class STATE
    {
        SCENE_IN,         //! �J�n
        SCENE_UPDATA,     //! �X�V
        SCENE_OUT,        //! �I��
        SCENE_CHANGE,     //! �ύX
    };

    /*
     *  @brief      �V�[���̐���
     *
     *  @param[in]  id  �V�[��ID
     */
    void        Create(SCENE_ID id);

    /*
     *  @brief      ���݂̃V�[�����폜
     */
    void        Delete(void);

    /*
     *  @brief      �V�[���J�n���o
     */
    void        SceneIn(void);

    /*
     *  @brief      �V�[���X�V
     */
    void        SceneUpdate(void);

    /*
     *  @brief      �V�[���I�����o
     */
    void        SceneOut(void);

    /*
     *  @brief      �V�[���ύX
     */
    void        SceneChange(void);

    static const float  m_fade_speed;       //! �t�F�[�h���x
    SCENE_ID            m_CurrentSceneID;   //! ���݂̃V�[��ID
    SCENE_ID            m_NextSceneID;      //! ���̃V�[��ID
    SCENE_ID            m_PushSceneID;      //! �v�b�V������V�[��ID
    STATE               m_State;            //! ���ID
    bool                m_PushFlag;         //! �V�[���̃v�b�V�����s��ꂽ
    aqua::CSprite       m_FadeSprite;       //! �t�F�[�h�p�X�v���C�g
};
