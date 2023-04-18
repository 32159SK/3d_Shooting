
/*!
 *  @file       model.cpp
 *  @brief      3Dモデルクラス
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
  *  コンストラクタ
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
 *  コピーコンストラクタ
 */
aqua::CModel::
CModel(const aqua::CModel& model)
    : m_ModelResource(nullptr)
{
    if (m_ModelResource)
        m_ModelResource->RemoveReference();

    m_ModelResource = model.m_ModelResource;

    // 参照カウンタ加算
    m_ModelResource->AddReference();
}

/*
 *  モデル読み込み
 */
void
aqua::CModel::
Load(const std::string& file_name)
{
    // モデルリソース退避
    core::CModelResource* model = m_ModelResource;

    // モデルマネージャからモデル取得
    m_ModelResource = core::CModelManager::GetInstance().Load(file_name);

    if (model)
    {
        int count = model->RemoveReference();

        // 前のモデルの参照カウンタがなくなったら解放
        if (count <= 0)
            core::CModelManager::GetInstance().Unload(model);
    }

    MV1SetScale(m_ModelResource->GetResourceHandle(), scale);

}

/*
 *  モデル解放
 */
void
aqua::CModel::
Unload(void)
{
    // モデル解放
    if (m_ModelResource)
        core::CModelManager::GetInstance().Unload(m_ModelResource);

    m_ModelResource = nullptr;
}

/*
 *  モデル描画
 */
void aqua::CModel::Draw(void)
{
    // テクスチャが読み込まれていなければ描画しない
    if (!m_ModelResource->IsEnable()) return;

    // 非表示の時は描画しない
    if (!visible) return;

    // モデルリソースハンドル取得
    int handle = m_ModelResource->GetResourceHandle();

    if (handle < 0) return;

    MV1SetScale(handle, scale);

    MV1SetPosition(handle, position);

    MV1SetRotationXYZ(handle, rotation);

    // 描画
    MV1DrawModel(handle);
}

/*
 *  代入演算子のオーバーロード
 */
aqua::CModel&
aqua::CModel::
operator=(const aqua::CModel& model)
{
    // モデルを持っていたら参照を減算
    if (m_ModelResource)
        m_ModelResource->RemoveReference();

    m_ModelResource = model.m_ModelResource;

    // 参照カウンタ加算
    m_ModelResource->AddReference();

    return *this;
}

/*
 *  モデル生成
 */
void
aqua::CModel::
Create (bool alpha_channel)
{
    // モデルリソース退避
    core::CModelResource* model = m_ModelResource;

    // モデルマネージャからモデル取得
    m_ModelResource = core::CModelManager::GetInstance().Create(alpha_channel);

    if (model)
    {
        int count = model->RemoveReference();

        // 前のモデルの参照カウンタがなくなったら解放
        if (count <= 0)
            core::CModelManager::GetInstance().Delete(model);
    }
}

/*
 *  モデル解放
 */
void
aqua::CModel::
Delete(void)
{
    // モデル解放
    if (m_ModelResource)
        core::CModelManager::GetInstance().Delete(m_ModelResource);

    m_ModelResource = nullptr;
}
