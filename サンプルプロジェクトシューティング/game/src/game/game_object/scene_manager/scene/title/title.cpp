/*
 *  @file       title_scene.cpp
 *  @brief      �^�C�g���V�[��
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/20
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include"..\title\title.h"
#include"../../../game_object.h"

/*
 *  �R���X�g���N�^
 */
CTitleScene::
CTitleScene(aqua::IGameObject* parent)
    : IScene(parent, "TitleScene")
{
}

/*
 *  ������
 */
void
CTitleScene::
Initialize(void)
{
    AQUA_DEBUG_LOG("�^�C�g���V�[��");
}

/*
 *  �X�V
 */
void
CTitleScene::
Update(void)
{
    Operation();
}

/*
 *  �`��
 */
void
CTitleScene::
Draw(void)
{
}

/*
 *  ���
 */
void
CTitleScene::
Finalize(void)
{
}


/*
 *  ���쏈��
 */
void CTitleScene::Operation(void)
{
    // Z�L�[  ( ���� )
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
        Change(SCENE_ID::GAMEMAIN);
}