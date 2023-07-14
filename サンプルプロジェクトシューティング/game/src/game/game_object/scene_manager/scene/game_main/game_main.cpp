
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

const float CGameMain::m_white_out_time = 7.0f;
const float CGameMain::m_camera_distace = 150.0f;
const float CGameMain::m_camera_v_rotate = 60.0f;

CGameMain::CGameMain(aqua::IGameObject* parent)
    : IScene(parent, "GameMainScene")
    , m_State(STATE::STATE_GAME_START)
    , m_Floor(nullptr)
    , m_Player(nullptr)
    , m_EnemyManager(nullptr)
    , m_GameClear(false)
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
    // ���̐���
    m_Floor = aqua::CreateGameObject<CFloor>(this);

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

    // �G�t�F�N�g�Ǘ��N���X
    aqua::CreateGameObject<CEffectManager>(this);
    // �����Ȃ��ŏ������ł�����̂͂�����
    IGameObject::Initialize();

    // ���[�_�[�N���X�̏�����
    rd->Initialize(m_Player);

    // �v���C���[�̏��������G�Ǘ��N���X�̃Z�b�g
    m_Player->Initialize(aqua::CVector3::ZERO, 10.0f, 10.0f, 10.0f, aqua::CColor::BLUE,st_m, bm);
    m_Player->SetEnemyManager(m_EnemyManager);
    // �G�Ǘ��N���X�̏��������v���C���[�A�e�Ǘ��N���X�̃Z�b�g
    m_EnemyManager->Initialize(bm, m_Player, st_m, rd);

    // �J�����̃Z�b�g�A�b�v
    m_Camera.SetCamera(50.0f, 10000.0f);
    m_Camera.m_Target = m_Player->GetPosition();
    m_Camera.m_Distace = m_camera_distace;
    m_Camera.m_VRotate = aqua::DegToRad(m_camera_v_rotate);

    // �^�C�}�[�̃Z�b�g�A�b�v
    m_WhiteOutTimer.Setup(m_white_out_time);

    // �z���C�g�A�E�g�p�̉摜�𐶐����Ă���
    m_WhiteOutSprite.Create("data\\texture\\white.png");
    // �摜�̃A���t�@�l��0�ɂ��čŏ��͓����ɂ���
    m_WhiteOutSprite.color.alpha = (unsigned char)0.0f;
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
    m_Camera.Update();

    // �v���C���[�����񂾎��_�ŃQ�[�����I��
    if (m_Player->GetDead())
        GameFinish();
    // �Q�[���N���A���ꂽ��z���C�g�A�E�g����������
    if (m_GameClear)
        WhiteOut();
}

void CGameMain::GameFinish(void)
{
    if (m_GameClear)
        // �V�[����؂�ւ���
        Push(SCENE_ID::RESULT);
    else
        Change(SCENE_ID::RESULT);
}

void CGameMain::WhiteOut(void)
{
    // �^�C�}�[���A�b�v�f�[�g
    m_WhiteOutTimer.Update();

    float alpha = 0.0f;

    // �C�[�W���O�ŃA���t�@�l��ω�������
    alpha = aqua::easing::InCubic(m_WhiteOutTimer.GetTime(), m_WhiteOutTimer.GetLimit(), 0.0f, 255.0f);

    m_WhiteOutSprite.color.alpha = (unsigned char)alpha;

    // �^�C�}�[���I��������Q�[�����I��
    if (m_WhiteOutTimer.Finished())
    {
        m_WhiteOutSprite.color.alpha = (unsigned char)255.0f;
        GameFinish();
    }
}


/*
 *  �`��
 */
void
CGameMain::
Draw(void)
{
    IGameObject::Draw();
    m_WhiteOutSprite.Draw();
}

/*
 *  ���
 */
void
CGameMain::
Finalize(void)
{
    IGameObject::Finalize();
    m_WhiteOutSprite.Delete();
}
