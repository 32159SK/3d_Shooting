
/*
 *  @file       stage_manager.cpp
 *  @brief      �X�e�[�W�Ǘ��N���X
 *  @author     Kazuto Shimazaki
 *  @date       2021/06/24
 *
 *  Copyright (c) 201
 *  @since      1.03-2019, Kazuya Maruyama. All rights reserved.
 */

#include "../game_object.h"
#include "stage_manager.h"


/*
 *  �R���X�g���N�^
 */
CStageManager::
CStageManager(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "StageManager")
{
}

/*
 *  ������
 */
void
CStageManager::
Initialize(void)
{
}




/*
 *  �X�V
 */
void
CStageManager::
Update(void)
{
    IGameObject::Update();
}

/*
 *  �`��
 */
void
CStageManager::
Draw(void)
{
    IGameObject::Draw();
}

/*
 *  ���
 */
void
CStageManager::
Finalize(void)
{
    IGameObject::Finalize();
}