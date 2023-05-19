/*
 *  @file       stage_object.h
 *  @brief      �X�e�[�W�I�u�W�F�N�g
 *  @author
 *  @date
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "stage_object_id.h"

 /*
  *  @class      IStageObject
  *
  *  @brief      �X�e�[�W�I�u�W�F�N�g�N���X
  *
  *  @author     
  *
  *  @date       
  *
  *  @since      1.0
  */

class CStageManager;

class IStageObject : public aqua::IGameObject
{
public:

    /*
     *  @brief      �R���X�g���N�^
     */
    IStageObject(aqua::IGameObject* parent, const std::string& name);

    /*
     *  @brief      �f�X�g���N�^
     */
    ~IStageObject(void) = default;

    /*!
     *  @brief      ������
     *
     *  @param[in]  id �X�e�[�W��̃}�b�v�`�b�vID
     */
    virtual void        Initialize(const STAGE_OBJECT_ID& id, int x, int z);

    /*
     *  @brief      �X�V
     */
    virtual void        Update(void);

    /*
     *  @brief      �`��
     */
    virtual void        Draw(void);

    /*
     *  @brief      ���
     */
    virtual void        Finalize(void);

    /*
     *  @brief      �X�e�[�W�I�u�W�F�N�gID�擾
     *
     *  @return     �X�e�[�W�I�u�W�F�N�gID
     */
    STAGE_OBJECT_ID     GetStageObjectID(void) const;


    /*
     *  @brief      �X�e�[�W�I�u�W�F�N�gID�ݒ�
     *
     *  @param[in]  stage_object_id     �X�e�[�W�I�u�W�F�N�gID
     */
    void                SetStageObjectID(STAGE_OBJECT_ID stage_object_id);

    /*
     *  @brief      �A�N�e�B�u��ԃ`�F�b�N
     *
     *  @retval     true    �A�N�e�B�u
     *  @retval     false   ��A�N�e�B�u
     */
    bool                IsActive(void) const;

    /*
     *  @brief      �A�N�e�B�u�t���O�ݒ�
     *
     *  @param[in]  active  �A�N�e�B�u���
     */
    void                SetActive(bool active);


    virtual bool        CollisionCheck(aqua::CVector3 position, aqua::CVector3 destination);

protected:

    virtual void        GoIn(void);

    virtual void        GoOut(void);

    // �X�e�[�W�I�u�W�F�N�g�̏��
    enum OBJECT_STATE
    {
        GO_IN,
        PLAY,
        GO_OUT,
        FINISH
    };

    static const float            m_default_size;         //!< �W���T�C�Y
    static const float            m_transition_time;      //!< �I�u�W�F�N�g�̑J�ڎ���
    STAGE_OBJECT_ID               m_StageObjectID;        //!< �X�e�[�W�I�u�W�F�N�gID
    OBJECT_STATE                  m_ObjectState;
    aqua::CVector3                m_Position;             //!< �ʒu
    aqua::CTimer                  m_Timer;                //!< �I�u�W�F�N�g�̑J�ڃ^�C�}�[
    bool                          m_ActiveFlag;           //!< �A�N�e�B�u�t���O
    bool                          m_CollisionFlag;        //!< �Փ˃t���O


};