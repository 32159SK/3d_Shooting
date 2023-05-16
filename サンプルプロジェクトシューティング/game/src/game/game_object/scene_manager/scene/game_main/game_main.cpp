
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
    , m_Player(nullptr)
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
    // CSV�ǂݎ��N���X�̐���
    CCSVReader* csv_r = aqua::CreateGameObject<CCSVReader>(this);
    // ��
    aqua::CreateGameObject<CFloor>(this);

    // �����Ȃ��ŏ������ł�����̂͂�����
    IGameObject::Initialize();

    // �X�e�[�W�Ǘ��̐���
    CStageManager* st_m = aqua::CreateGameObject<CStageManager>(this);
    st_m->Initialize(csv_r);

    // �e�Ǘ��N���X�̐���
    CBulletManager* bm = aqua::CreateGameObject<CBulletManager>(this);
    bm->Initialize(csv_r,st_m);

    // �v���C���[�̐���
    m_Player = aqua::CreateGameObject<CPlayer>(this);

    // �G�Ǘ��N���X�̐���
    m_EnemyManager = aqua::CreateGameObject<CEnemyManager>(this);

    // ���[�_�[�N���X�̐���
    CRader* rd = aqua::CreateGameObject<CRader>(this);
    rd->Initialize(m_Player);


    // �v���C���[�̏��������e�Ǘ��N���X�̃Z�b�g
    m_Player->Initialize(aqua::CVector3(0.0f, 0.0f, -50.0f), 10.0f, 10.0f, 10.0f, aqua::CColor::BLUE,st_m, bm);

    // �G�Ǘ��N���X�̏��������v���C���[�A�e�Ǘ��N���X�̃Z�b�g
    m_EnemyManager->Initialize(csv_r, bm, m_Player, st_m, rd);

//    m_Camera.SetCamera(0.1, 10000.0, aqua::CVector3(0, 500.0f, -50.0f), m_Player->GetPosition());
    m_Camera.SetCamera(50.0, 10000.0);
    m_Camera.m_Target = m_Player->GetPosition();
    m_Camera.m_Distace = 100.0f;
    m_Camera.m_VRotate = aqua::DegToRad(50.0f);

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
    //m_CamContorl->Move();
    m_Camera.m_Target = m_Player->GetPosition();
    //m_Camera.m_Position = m_Camera.m_Target + aqua::CVector3(0.0f, 500.0f, -30.0f);
    //m_Camera.SetCamera();
    float wheel_value = aqua::mouse::GetWheel();
    if (wheel_value > 0) m_Camera.m_Distace -= 5.0f;
    else if (wheel_value < 0) m_Camera.m_Distace += 5.0f;
    m_Camera.Update();

    if (m_Player->GetDead()||m_EnemyManager->GetFinish())
        GameFinish();
}

void CGameMain::GameFinish(void)
{
    Change(SCENE_ID::RESULT);
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
