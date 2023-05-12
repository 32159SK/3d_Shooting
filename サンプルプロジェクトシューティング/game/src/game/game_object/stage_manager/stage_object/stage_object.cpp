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

/*
 *  �R���X�g���N�^
 */
IStageObject::
IStageObject(aqua::IGameObject* parent, const std::string& name)
    : IGameObject(parent, name)
    , m_StageObjectID(NORMAL_BLOCK)
    , m_ActiveFlag(true)
    , m_CollisionFlag(false)
{
}

/*
 *  �f�X�g���N�^
 */
IStageObject::
~IStageObject(void)
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

}

/*
 *  �X�V
 */
void
IStageObject::
Update(void)
{
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

    m_Cube.Draw();
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
 *  �ʒu�ݒ�
 */
void
IStageObject::
SetPosition(const aqua::CVector3& position)
{
    m_Position = position;
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
