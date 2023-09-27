
/*
 *  @file       scene_manager.cpp
 *  @brief      �V�[���Ǘ�
 *  @author
 *  @date
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "../game_object.h"
#include "scene_manager.h"
#include "scene/title/title.h"
#include "scene/game_main/game_main.h"
#include "scene/result/result.h"
#include "scene/tutorial/tutorial.h"

const float CSceneManager::m_fade_speed = 255.0f;

//�R���X�g���N�^
CSceneManager::CSceneManager(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "SceneManager")
    , m_CurrentSceneID(SCENE_ID::DUMMY)
    , m_NextSceneID(SCENE_ID::DUMMY)
    , m_PushSceneID(SCENE_ID::DUMMY)
    , m_State(STATE::SCENE_IN)
    , m_PushFlag(false)
{
}

//������
void CSceneManager::Initialize(void)
{
    // �t�F�[�h�p�X�v���C�g����
    m_FadeSprite.Create("data\\texture\\white.png");

    m_FadeSprite.color = aqua::CColor::BLACK;

    // �X�v���b�V���V�[�����n�߂ɐ���
    Create(SCENE_ID::TITLE);

    // �V�[���C����Ԃ�ݒ�
    m_State = STATE::SCENE_IN;

    // �v�b�V���t���OOFF
    m_PushFlag = false;

}

//�X�V
void CSceneManager::Update(void)
{
    //��Ԃ𕪊�
    switch (m_State)
    {
    case STATE::SCENE_IN:       SceneIn();         break;   //�J�n
    case STATE::SCENE_UPDATA:   SceneUpdate();     break;   //�X�V
    case STATE::SCENE_OUT:      SceneOut();        break;   //�I��
    case STATE::SCENE_CHANGE:   SceneChange();     break;   //�ύX
    }


    IGameObject::Update();
}

//�`��
void CSceneManager::Draw(void)
{
    //�Q�[���I�u�W�F�N�g��`��
    IGameObject::Draw();

    m_FadeSprite.Draw();
}

//���
void CSceneManager::Finalize(void)
{
    //�Q�[���I�u�W�F�N�g�����
    IGameObject::Finalize();

    m_FadeSprite.Delete();
}

//�V�[���̕ύX
void CSceneManager::Change(SCENE_ID id)
{
    // ���̃V�[��ID
    m_NextSceneID = id;
}

//�V�[�����X�^�b�N����
void CSceneManager::Push(SCENE_ID id)
{
    // ���t���[�����ɂ��łɃv�b�V������Ă���
    if (m_PushFlag || m_PushSceneID != SCENE_ID::DUMMY) return;

    // �v�b�V���t���O��ON
    m_PushFlag = true;

    // �X�^�b�N����V�[��ID��ۑ�
    m_PushSceneID = id;
}

//�X�^�b�N�����V�[�������o��
void CSceneManager::Pop(void)
{
    // �q�̃V�[����1�̏ꍇ�̓|�b�v�ł��Ȃ�
    if (m_ChildObjectList.size() <= 1)
        return;

    // �����̃V�[���̃C�e���[�^�擾
    aqua::GAME_OBJECT_LIST::reverse_iterator it = m_ChildObjectList.rbegin();

    // �V�[���N���X�ɃL���X�g
    IScene* scene = (IScene*)(*it);

    // �����̃V�[�����폜�Ώۂɐݒ�
    scene->DeleteObject();

    // �ЂƂO�̃V�[�����擾
    scene = (IScene*)(*(++it));

    // �ЂƂO�̃V�[�����A�N�e�B�u��ԂɕύX
    scene->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);
}

//���݂̃V�[�������Z�b�g����
void CSceneManager::Reset(void)
{
    //���̃V�[��ID�Ɍ��݂̃V�[��ID
    m_NextSceneID = m_CurrentSceneID;

    //���݂̃V�[��ID�Ƀ_�~�[
    m_CurrentSceneID = SCENE_ID::DUMMY;
}

//�V�[���̐���
void CSceneManager::Create(SCENE_ID id)
{
    //�V�[���̍\���̂̃|�C���^���쐬
    IScene* scene = nullptr;

    // id���ƂɐV�����V�[���𐶐�
    switch (id)
    {
    case SCENE_ID::TITLE:       scene = aqua::CreateGameObject<CTitleScene>(this);      break;  //�^�C�g���V�[��
    case SCENE_ID::GAMEMAIN:    scene = aqua::CreateGameObject<CGameMain>(this);        break;  //�Q�[�����C���V�[��
    case SCENE_ID::RESULT:      scene = aqua::CreateGameObject<CResultScene>(this);     break;  //���U���g�V�[��
    case SCENE_ID::TUTORIAL:    scene = aqua::CreateGameObject<CTutorial>(this);        break;  //�`���[�g���A���V�[��
    }

    AQUA_ASSERT(scene, "�V�[���������ł��܂���ł����B");

    // �V�[����������
    scene->Initialize();
}

//���݂̃V�[�����폜
void CSceneManager::Delete(void)
{
    //�Q�[���I�u�W�F�N�g�����
    IGameObject::Finalize();
}

//�V�[���J�n���o
void CSceneManager::SceneIn(void)
{
    float alpha = (float)m_FadeSprite.color.alpha;

    alpha -= m_fade_speed * aqua::GetDeltaTime();

    if (alpha < 0.0f)
    {
        alpha = 0.0f;
        //��Ԃ��X�V�ɂ���
        m_State = STATE::SCENE_UPDATA;
    }

    m_FadeSprite.color.alpha = (unsigned char)alpha;
}

//�V�[���̍X�V
void CSceneManager::SceneUpdate(void)
{
    // �v�b�V���������s���Ă����ꍇ
    if (m_PushFlag)
    {
        // �V�����V�[���𐶐����ăX�^�b�N����
        Create(m_PushSceneID);

        // ���g�p���̓_�~�[ID�����Ă���
        m_PushSceneID = SCENE_ID::DUMMY;

        // �V�[���̃v�b�V�����I������
        m_PushFlag = false;
    }

    //�Q�[���I�u�W�F�N�g���X�V
    IGameObject::Update();

    // �V�[���̕ύX�����m
    if (m_CurrentSceneID != m_NextSceneID)
        //��Ԃ��I���ɂ���
        m_State = STATE::SCENE_OUT;
}

//�V�[���I�����o
void CSceneManager::SceneOut(void)
{
    float alpha = (float)m_FadeSprite.color.alpha;

    alpha += m_fade_speed * aqua::GetDeltaTime();

    if (alpha > (float)aqua::CColor::MAX_COLOR)
    {
        alpha = (float)aqua::CColor::MAX_COLOR;

        //��Ԃ�ύX�ɂ���
        m_State = STATE::SCENE_CHANGE;
    }

    m_FadeSprite.color.alpha = (unsigned char)alpha;
}

//�V�[���̕ύX
void CSceneManager::SceneChange(void)
{
    // ���݂̃V�[�����폜
    Delete();

    // ���̃V�[���𐶐�
    Create(m_NextSceneID);

    // �V�[��ID��ۑ�
    m_CurrentSceneID = m_NextSceneID;

    // ��Ԃ��ڍs
    m_State = STATE::SCENE_IN;
}
