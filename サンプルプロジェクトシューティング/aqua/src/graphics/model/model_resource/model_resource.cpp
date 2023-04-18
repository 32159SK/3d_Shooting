#include <DxLib.h>
#include <ctime>
#include "model_resource.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"
#include "../model_manager/model_manager.h"

/*
 *  �R���X�g���N�^
 */
aqua::core::CModelResource::CModelResource(void)
	: IResourceObject(aqua::core::RESOURCE_TYPE::LOAD_MODEL)
{
}

/*
 *  ���f���̓ǂݍ���
 */
void aqua::core::CModelResource::Load(const std::string& file_name)
{
	if (m_Enabel)return;

	m_ResourceHandle = MV1LoadModel(file_name.c_str());

	AQUA_DX_ASSERT(m_ResourceHandle, file_name + "�̓ǂݍ��݂Ɏ��s���܂����B");

	m_ResourceName = file_name;

	m_Enabel = true;

	m_TotalAnimeNum = MV1GetAnimNum(m_ResourceHandle);

}

/*
 *  ���f���̕���
 */
void aqua::core::CModelResource::Duplicate(const CModelResource* model)
{
	if (m_Enabel)return;

	if (model == nullptr) return;

	m_ResourceHandle = MV1DuplicateModel(model->GetResourceHandle());

	AQUA_DX_ASSERT(m_ResourceHandle, "���f���̕����Ɏ��s���܂����B");

	m_ResourceName = model->GetResourceName();

	m_Enabel = true;

	m_TotalAnimeNum = MV1GetAnimNum(m_ResourceHandle);
}

/*
 *  ���f���̉��
 */

void aqua::core::CModelResource::Unload(void)
{
	MV1DeleteModel(m_ResourceHandle);

	m_ResourceHandle = AQUA_UNUSED_HANDLE;

	m_ResourceName.clear();

	m_ReferenceCount = 0;

	m_ResourceType = RESOURCE_TYPE::DUMMY;

	m_Enabel = false;
}

/*
 *  ���A�j���[�V������
 */
int aqua::core::CModelResource::GetTotalAnimeNum(void)
{
	return m_TotalAnimeNum;
}
