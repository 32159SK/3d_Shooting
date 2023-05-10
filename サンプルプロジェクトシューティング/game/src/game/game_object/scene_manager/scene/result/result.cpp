/*
 *  @file       title_scene.cpp
 *  @brief      �^�C�g���V�[��
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/20
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include"../result/result.h"
#include"../../../game_object.h"

 /*
  *  �R���X�g���N�^
  */
CResultScene::
CResultScene(aqua::IGameObject* parent)
    : IScene(parent, "ResultScene")
{
}

/*
 *  ������
 */
void
CResultScene::
Initialize(void)
{
    AQUA_DEBUG_LOG("���U���g�V�[��");
}

/*
 *  �X�V
 */
void
CResultScene::
Update(void)
{
    Operation();
}

/*
 *  �`��
 */
void
CResultScene::
Draw(void)
{
}

/*
 *  ���
 */
void
CResultScene::
Finalize(void)
{
}


/*
 *  ���쏈��
 */
void CResultScene::Operation(void)
{
    // Z�L�[  ( ���� )
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
        Change(SCENE_ID::TITLE);
}