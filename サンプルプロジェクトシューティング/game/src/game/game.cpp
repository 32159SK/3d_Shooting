
/*!
 *  @file       game.cpp
 *  @brief      �Q�[���Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2021/02/06
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "game.h"

#include "game_object/sample_scene/sample_scene.h"

const unsigned int CGame::m_clear_color = 0xff7f7f7f;

/*
 *  �R���X�g���N�^
 */
CGame::
CGame( aqua::IGameObject* parent )
    : aqua::IGameObject( parent, "Game" )
{
}

/*
 *  ������
 */
void
CGame::
Initialize(void)
{
    // �ŏ��ɍ��I�u�W�F�N�g�Q

    aqua::CreateGameObject<CSmpleScene>(this);

    IGameObject::Initialize();
}

/*
 *  �`��
 */
void
CGame::
Draw(void)
{
    // ��ʂ̃N���A
    aqua::Clear(m_clear_color);

    // �`�悵�����I�u�W�F�N�g�Q

    IGameObject::Draw();
}
