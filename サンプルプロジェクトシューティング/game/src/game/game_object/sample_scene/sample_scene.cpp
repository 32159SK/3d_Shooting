#include "sample_scene.h"


// コンストラクタ
CSmpleScene::
CSmpleScene(aqua::IGameObject* parent)
{
}

// 初期化
void
CSmpleScene::
Initialize(void)
{
	m_Camera.SetCamera(0.1,10000.0,aqua::CVector3(0,0,-100), aqua::CVector3::ZERO);
	//m_Model.Load("data\\DxChara.x");
	//m_Model.scale = aqua::CVector3(0.01f, 0.01f, 0.01f);
	//m_Model.position = aqua::CVector3::ZERO;

	m_Sphere.Setup(aqua::CVector3(-20.0f, 0.0f, 0.0f), 5.0f, 10, aqua::CColor::BLUE, aqua::CColor::RED, true);

	m_Line.Setup(aqua::CVector3(20.0f,-10.0f,0.0f), aqua::CVector3(20.0f, 100.0f, 0.0f));

	m_Capsule.Setup(aqua::CVector3(20.0f,0.0f,0.0f), aqua::CVector3(50.0f, 0.0f, 0.0f), 10.0f, 10, aqua::CColor::MAGENTA, aqua::CColor::CYAN);

	//m_Cube.Setup(aqua::CVector3(20.0f,0.0f,0.0f), aqua::CVector3(70.0f, 60.0f, 0.0f), aqua::CColor::BLACK, aqua::CColor::WHITE);

	m_Cube.Setup(aqua::CVector3::ZERO, 5.0f, 5.0f, 5.0f, aqua::CColor::RED, aqua::CColor::WHITE, true);

	m_CamControler = new CCameraControl(&m_Camera);
}

// 更新
void
CSmpleScene::
Update(void)
{
	m_CamControler->Move();
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::FOUR))
		m_Cube.position -= aqua::CVector3(1.0f, 0.0f, 0.0f);
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::SIX))
		m_Cube.position += aqua::CVector3(1.0f, 0.0f, 0.0f);

	if (m_Cube.CheckCollision(m_Line.pointA, m_Line.pointB)
		||m_Cube.CheckCollision(m_Sphere.position,m_Sphere.radius))
		m_Cube.color = aqua::CColor::BLUE;
	else
		m_Cube.color = aqua::CColor::RED;
}

// 描画
void 
CSmpleScene::
Draw(void)
{
	//m_Model.Draw();
	m_Sphere.Draw();
	//m_Capsule.Draw();
	m_Line.Draw();
	m_Cube.Draw();
}

// 解放
void
CSmpleScene::
Finalize(void)
{
	//m_Model.Unload();
}
