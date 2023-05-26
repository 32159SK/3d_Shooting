
#include "model_manager.h"

#include "../model_resource/model_resource.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"

/*
 *  インスタンスの取得
 */
aqua::core::CModelManager&
aqua::core::CModelManager::
GetInstance(void)
{
	static CModelManager instance;

	return instance;
}

/*
 *  テクスチャクラスの読み込み
 */
aqua::core::CModelResource*
aqua::core::CModelManager::
Load(const std::string& file_name)
{
    // テクスチャ検索
    CModelResource* model = Find(file_name);

    // テクスチャが見つからなかった
    if (!model)
    {
        // 新しくテクスチャ生成
        model = AQUA_NEW CModelResource();

        // 読み込み
        model->Load(file_name);

        // テクスチャリストに追加
        m_ModelList.push_back(model);
    }
    else
    {
        CModelResource* dup = AQUA_NEW CModelResource();
        
        dup->Duplicate(model);

        m_ModelList.push_back(dup);

        model = dup;
    }

    // 参照カウンタ加算
    model->AddReference();

    return model;
}

/*
 *  テクスチャクラスの解放
 */
void
aqua::core::CModelManager::
Unload(CModelResource* model)
{
    if (!model) return;

    if (m_ModelList.empty()) return;

    // 参照カウンタ減算
    // 参照がなくなったら解放
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
 *  テクスチャ生成
 */
aqua::core::CModelResource*
aqua::core::CModelManager::
Create(bool alpha_channel)
{
    CModelResource* model = nullptr;

    // 新しくモデル生成
    model = AQUA_NEW CModelResource();

    // モデルリストに追加
    m_ModelList.push_back(model);

    // 参照カウンタ加算
    model->AddReference();

    return model;
}

/*
 *  テクスチャ解放
 */
void
aqua::core::CModelManager::
Delete(CModelResource* model)
{
    if (!model) return;

    if (m_ModelList.empty()) return;

    // 参照カウンタ減算
    // 参照がなくなったら解放
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
 *  テクスチャクラスの検索
 */
aqua::core::CModelResource*
aqua::core::CModelManager::
Find(const std::string& file_name)
{
    if (m_ModelList.empty()) return NULL;

    MODEL_LIST::iterator it = m_ModelList.begin();
    MODEL_LIST::iterator end = m_ModelList.end();

    // ファイル名が一致したテクスチャクラスを返す
    while (it != end)
    {
        if ((*it)->GetResourceName() == file_name)
            return (*it);

        ++it;
    }

    return NULL;
}

/*
 *  テクスチャリストのクリア
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
            // テクスチャ解放
            (*it)->Unload();

            AQUA_SAFE_DELETE((*it));
        }

        ++it;
    }

    // テクスチャリスト解放
    m_ModelList.clear();
}

/*
 *  コンストラクタ
 */
aqua::core::CModelManager::
CModelManager(void)
{
}

/*
 *  代入演算子
 */
aqua::core::CModelManager&
aqua::core::CModelManager::
operator=(const CModelManager& rhs)
{
    (void)rhs;

    return *this;
}
