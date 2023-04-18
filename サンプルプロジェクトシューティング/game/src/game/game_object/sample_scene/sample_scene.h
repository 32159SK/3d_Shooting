
#pragma once

#include"aqua.h"
#include"../camera_control/camera_control.h"

// サンプルシーン
class CSmpleScene : public aqua::IGameObject
{
public:

	// コンストラクタ
	CSmpleScene(aqua::IGameObject* parent);

	// デストラクタ
	~CSmpleScene(void) = default;

	// 初期化
	void	Initialize(void)override;

	// 更新
	void	Update(void)override;

	// 描画
	void	Draw(void)override;

	// 解放
	void	Finalize(void)override;

private:
	aqua::CCamera	m_Camera;
	aqua::CModel	m_Model;
	aqua::CSpherePrimitive m_Sphere;
	aqua::CLinePrimitive3D m_Line;
	aqua::CCapsulePrimitive m_Capsule;
	aqua::CCubePrimitive	m_Cube;
	CCameraControl* m_CamControler;
};