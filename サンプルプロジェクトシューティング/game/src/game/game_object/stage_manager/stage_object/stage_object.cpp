/*
 *  @file       stage_object.cpp
 *  @brief      �X�e�[�W�I�u�W�F�N�g
 *  @author
 *  @date
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#include "../../game_object.h"
#include "stage_object.h"

const float IStageObject::m_default_size = 25.0f;
const float IStageObject::m_transition_time = 3.0f;

/*
 *  �R���X�g���N�^
 */
IStageObject::
IStageObject(aqua::IGameObject* parent, const std::string& name)
    : IGameObject(parent, name)
    , m_StageObjectID(NORMAL_BLOCK)
    , m_ObjectState(OBJECT_STATE::GO_IN)
    , m_ActiveFlag(true)
    , m_CollisionFlag(false)
    , m_StageEdge(false)
{
}

/*
 *  ������
 */
void
IStageObject::
Initialize(const STAGE_OBJECT_ID& id, int x, int z)
{
    // �A�N�e�B�u�t���O��ON
    m_ActiveFlag = true;

    // �R���W�����t���O��OFF
    m_CollisionFlag = false;

    //	���W�ݒ�
    m_Position = aqua::CVector3::ZERO;

    m_Position.x = x * m_default_size - m_default_size / 2 * 20;

    m_Position.z = (20 - z) * m_default_size - m_default_size / 2 * 20;
}

/*
 *  �X�V
 */
void
IStageObject::
Update(void)
{
    switch (m_ObjectState)
    {
    case IStageObject::GO_IN:   GoIn(); break;
    case IStageObject::PLAY:    break;
    case IStageObject::GO_OUT:  GoOut();break;
    default:
        break;
    }

    // �A�N�e�B�u�t���OOFF�Ȃ�I��
    if (!m_ActiveFlag)
        return;
}

/*
 *  �`��
 */
void
IStageObject::
Draw(void)
{
    // �A�N�e�B�u�t���OOFF�Ȃ�I��
    if (!m_ActiveFlag)
        return;
}

/*
 *  ���
 */
void
IStageObject::
Finalize(void)
{
    // �A�N�e�B�u�t���O��OFF
    m_ActiveFlag = false;
}

/*
 *  �X�e�[�W�I�u�W�F�N�gID�擾
 */
STAGE_OBJECT_ID
IStageObject::
GetStageObjectID(void) const
{
    return m_StageObjectID;
}

/*
 *  �X�e�[�W�I�u�W�F�N�gID�ݒ�
 */
void
IStageObject::
SetStageObjectID(STAGE_OBJECT_ID id)
{
    m_StageObjectID = id;
}

/*
 *  �A�N�e�B�u��ԃ`�F�b�N
 */
bool
IStageObject::
IsActive(void) const
{
    return m_ActiveFlag;
}

/*
 *  �A�N�e�B�u�t���O�ݒ�
 */
void
IStageObject::
SetActive(bool active)
{
    m_ActiveFlag = active;
}

bool IStageObject::CollisionCheck(aqua::CVector3 position, aqua::CVector3 destination)
{
    return false;
}

void IStageObject::GoIn(void)
{
}

void IStageObject::GoOut(void)
{
}
