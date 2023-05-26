
#include "model_manager.h"

#include "../model_resource/model_resource.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"

/*
 *  �C���X�^���X�̎擾
 */
aqua::core::CModelManager&
aqua::core::CModelManager::
GetInstance(void)
{
	static CModelManager instance;

	return instance;
}

/*
 *  �e�N�X�`���N���X�̓ǂݍ���
 */
aqua::core::CModelResource*
aqua::core::CModelManager::
Load(const std::string& file_name)
{
    // �e�N�X�`������
    CModelResource* model = Find(file_name);

    // �e�N�X�`����������Ȃ�����
    if (!model)
    {
        // �V�����e�N�X�`������
        model = AQUA_NEW CModelResource();

        // �ǂݍ���
        model->Load(file_name);

        // �e�N�X�`�����X�g�ɒǉ�
        m_ModelList.push_back(model);
    }
    else
    {
        CModelResource* dup = AQUA_NEW CModelResource();
        
        dup->Duplicate(model);

        m_ModelList.push_back(dup);

        model = dup;
    }

    // �Q�ƃJ�E���^���Z
    model->AddReference();

    return model;
}

/*
 *  �e�N�X�`���N���X�̉��
 */
void
aqua::core::CModelManager::
Unload(CModelResource* model)
{
    if (!model) return;

    if (m_ModelList.empty()) return;

    // �Q�ƃJ�E���^���Z
    // �Q�Ƃ��Ȃ��Ȃ�������
    if (model->RemoveReference() > 0) return;

    MODEL_LIST::iterator it = m_ModelList.begin();
    MODEL_LIST::iterator end = m_ModelList.end();

    while (it != end)
    {
        if ((*it)->GetResourceHandle() == model->GetResourceHandle())
        {
            (*it)->Unload();

            AQUA_SAFE_DELETE((*it));

            m_ModelList.erase(it);

            break;
        }

        ++it;
    }
}

/*
 *  �e�N�X�`������
 */
aqua::core::CModelResource*
aqua::core::CModelManager::
Create(bool alpha_channel)
{
    CModelResource* model = nullptr;

    // �V�������f������
    model = AQUA_NEW CModelResource();

    // ���f�����X�g�ɒǉ�
    m_ModelList.push_back(model);

    // �Q�ƃJ�E���^���Z
    model->AddReference();

    return model;
}

/*
 *  �e�N�X�`�����
 */
void
aqua::core::CModelManager::
Delete(CModelResource* model)
{
    if (!model) return;

    if (m_ModelList.empty()) return;

    // �Q�ƃJ�E���^���Z
    // �Q�Ƃ��Ȃ��Ȃ�������
    if (model->RemoveReference() > 0) return;

    MODEL_LIST::iterator it = m_ModelList.begin();
    MODEL_LIST::iterator end = m_ModelList.end();

    while (it != end)
    {
        if ((*it) == model)
        {
            (*it)->Unload();

            AQUA_SAFE_DELETE((*it));

            m_ModelList.erase(it);

            break;
        }

        ++it;
    }
}

/*
 *  �e�N�X�`���N���X�̌���
 */
aqua::core::CModelResource*
aqua::core::CModelManager::
Find(const std::string& file_name)
{
    if (m_ModelList.empty()) return NULL;

    MODEL_LIST::iterator it = m_ModelList.begin();
    MODEL_LIST::iterator end = m_ModelList.end();

    // �t�@�C��������v�����e�N�X�`���N���X��Ԃ�
    while (it != end)
    {
        if ((*it)->GetResourceName() == file_name)
            return (*it);

        ++it;
    }

    return NULL;
}

/*
 *  �e�N�X�`�����X�g�̃N���A
 */
void
aqua::core::CModelManager::
Clear(void)
{
    if (m_ModelList.empty()) return;

    MODEL_LIST::iterator it = m_ModelList.begin();
    MODEL_LIST::iterator end = m_ModelList.end();

    while (it != end)
    {
        if ((*it))
        {
            // �e�N�X�`�����
            (*it)->Unload();

            AQUA_SAFE_DELETE((*it));
        }

        ++it;
    }

    // �e�N�X�`�����X�g���
    m_ModelList.clear();
}

/*
 *  �R���X�g���N�^
 */
aqua::core::CModelManager::
CModelManager(void)
{
}

/*
 *  ������Z�q
 */
aqua::core::CModelManager&
aqua::core::CModelManager::
operator=(const CModelManager& rhs)
{
    (void)rhs;

    return *this;
}
