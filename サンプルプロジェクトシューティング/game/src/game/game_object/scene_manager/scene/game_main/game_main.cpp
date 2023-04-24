
/*
 *  @file       game_main.cpp
 *  @brief      �Q�[�����C���V�[��
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/20
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#include "../../../game_object.h"
#include "game_main.h"


CGameMain::CGameMain(aqua::IGameObject* parent)
    : IScene(parent, "GameMainScene")
    , m_State(STATE::STATE_GAME_START)
    , m_CamContorl(nullptr)
{
}

/*
 *  �f�X�g���N�^
 */
CGameMain::
~CGameMain(void)
{
}

/*
 *  ������
 */
void
CGameMain::
Initialize(void)
{
    // �e�Ǘ��N���X�̐���
    CBulletManager* bm = aqua::CreateGameObject<CBulletManager>(this);
    // �v���C���[�̐���
    CPlayer* player = aqua::CreateGameObject<CPlayer>(this);
    // �G�Ǘ��N���X�̐���
    CEnemyManager* em = aqua::CreateGameObject<CEnemyManager>(this);
    
    // �v���C���[�̏��������e�Ǘ��N���X�̃Z�b�g
    player->Initialize(aqua::CVector3(0.0f, 10.0f, -50.0f), 10.0f, 10.0f, 10.0f, aqua::CColor::BLUE, bm);
    // �G�Ǘ��N���X�̏��������v���C���[�A�e�Ǘ��N���X�̃Z�b�g
    em->Initialize(bm, player);

    m_Camera.SetCamera(0.1, 10000.0, aqua::CVector3(0, 0, -100), player->GetPosition());
    m_CamContorl = new CCameraControl(&m_Camera);
}

/*
 *  �X�V
 */
void
CGameMain::
Update(void)
{
    IGameObject::Update();

    //��Ԃ𕪊�
    switch (m_State)
    {
    case STATE_GAME_START:  GameStart();   break;
    case STATE_GAME_PLAY:   GamePlay();    break;
    }
    m_State = STATE_GAME_PLAY;


}

/*
 *  �Q�[���J�n
 */
void
CGameMain::
GameStart(void)
{


}

/*
 *  �Q�[����
 */
void
CGameMain::
GamePlay(void)
{
    m_CamContorl->Move();
}

void CGameMain::GameFinish(void)
{
}


/*
 *  �`��
 */
void
CGameMain::
Draw(void)
{
    IGameObject::Draw();
}

/*
 *  ���
 */
void
CGameMain::
Finalize(void)
{
    IGameObject::Finalize();
}
