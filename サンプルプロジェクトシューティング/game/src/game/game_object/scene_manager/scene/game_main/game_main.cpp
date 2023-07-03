
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

    // �e�Ǘ��N���X�̐���
    CBulletManager* bm = aqua::CreateGameObject<CBulletManager>(this);

    // �G�Ǘ��N���X�̐���
    m_EnemyManager = aqua::CreateGameObject<CEnemyManager>(this);

    // �v���C���[�̐���
    m_Player = aqua::CreateGameObject<CPlayer>(this);

    // ���[�_�[�N���X�̐���
    CRader* rd = aqua::CreateGameObject<CRader>(this);
    rd->Initialize(m_Player);
    st_m->Initialize(csv_r);

    // �G�t�F�N�g�Ǘ��N���X
    aqua::CreateGameObject<CEffectManager>(this);

    // �v���C���[�̏��������e�Ǘ��N���X�̃Z�b�g
    m_Player->Initialize(aqua::CVector3(0.0f, 0.0f, -50.0f), 10.0f, 10.0f, 10.0f, aqua::CColor::BLUE,st_m, bm);
    m_Player->SetEnemyManager(m_EnemyManager);
    // �G�Ǘ��N���X�̏��������v���C���[�A�e�Ǘ��N���X�̃Z�b�g
    m_EnemyManager->Initialize(csv_r, bm, m_Player, st_m, rd);
    // �e�Ǘ��N���X�̏�����
    bm->Initialize(csv_r,st_m);

    m_Camera.SetCamera(50.0f, 10000.0f);
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
    m_Camera.m_Target = m_Player->GetPosition();
    float wheel_value = (float)aqua::mouse::GetWheel();
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
