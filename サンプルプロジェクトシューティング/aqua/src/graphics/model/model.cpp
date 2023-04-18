
/*!
 *  @file       model.cpp
 *  @brief      3D���f���N���X
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/13
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include <windows.h>
#include "model.h"
#include "model_manager\model_manager.h"

 /*
  *  �R���X�g���N�^
  */
aqua::CModel::
CModel(void)
    : m_ModelResource(nullptr)
    , position(aqua::CVector3::ZERO)
    , scale(aqua::CVector3::ONE)
    , rotation(aqua::CVector3::ZERO)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
aqua::CModel::
CModel(const aqua::CModel& model)
    : m_ModelResource(nullptr)
{
    if (m_ModelResource)
        m_ModelResource->RemoveReference();

    m_ModelResource = model.m_ModelResource;

    // �Q�ƃJ�E���^���Z
    m_ModelResource->AddReference();
}

/*
 *  ���f���ǂݍ���
 */
void
aqua::CModel::
Load(const std::string& file_name)
{
    // ���f�����\�[�X�ޔ�
    core::CModelResource* model = m_ModelResource;

    // ���f���}�l�[�W�����烂�f���擾
    m_ModelResource = core::CModelManager::GetInstance().Load(file_name);

    if (model)
    {
        int count = model->RemoveReference();

        // �O�̃��f���̎Q�ƃJ�E���^���Ȃ��Ȃ�������
        if (count <= 0)
            core::CModelManager::GetInstance().Unload(model);
    }

    MV1SetScale(m_ModelResource->GetResourceHandle(), scale);

}

/*
 *  ���f�����
 */
void
aqua::CModel::
Unload(void)
{
    // ���f�����
    if (m_ModelResource)
        core::CModelManager::GetInstance().Unload(m_ModelResource);

    m_ModelResource = nullptr;
}

/*
 *  ���f���`��
 */
void aqua::CModel::Draw(void)
{
    // �e�N�X�`�����ǂݍ��܂�Ă��Ȃ���Ε`�悵�Ȃ�
    if (!m_ModelResource->IsEnable()) return;

    // ��\���̎��͕`�悵�Ȃ�
    if (!visible) return;

    // ���f�����\�[�X�n���h���擾
    int handle = m_ModelResource->GetResourceHandle();

    if (handle < 0) return;

    MV1SetScale(handle, scale);

    MV1SetPosition(handle, position);

    MV1SetRotationXYZ(handle, rotation);

    // �`��
    MV1DrawModel(handle);
}

/*
 *  ������Z�q�̃I�[�o�[���[�h
 */
aqua::CModel&
aqua::CModel::
operator=(const aqua::CModel& model)
{
    // ���f���������Ă�����Q�Ƃ����Z
    if (m_ModelResource)
        m_ModelResource->RemoveReference();

    m_ModelResource = model.m_ModelResource;

    // �Q�ƃJ�E���^���Z
    m_ModelResource->AddReference();

    return *this;
}

/*
 *  ���f������
 */
void
aqua::CModel::
Create (bool alpha_channel)
{
    // ���f�����\�[�X�ޔ�
    core::CModelResource* model = m_ModelResource;

    // ���f���}�l�[�W�����烂�f���擾
    m_ModelResource = core::CModelManager::GetInstance().Create(alpha_channel);

    if (model)
    {
        int count = model->RemoveReference();

        // �O�̃��f���̎Q�ƃJ�E���^���Ȃ��Ȃ�������
        if (count <= 0)
            core::CModelManager::GetInstance().Delete(model);
    }
}

/*
 *  ���f�����
 */
void
aqua::CModel::
Delete(void)
{
    // ���f�����
    if (m_ModelResource)
        core::CModelManager::GetInstance().Delete(m_ModelResource);

    m_ModelResource = nullptr;
}
