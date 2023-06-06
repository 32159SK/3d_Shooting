#include "../../game_object.h"
#include "life_bar.h"

CLifeBar::CLifeBar(aqua::IGameObject* parent)
	: IUIComponent(parent,"LifeBar")
	, m_Camera(nullptr)
	, m_GameMain(nullptr)
{
}

void CLifeBar::Initialize(void)
{
	m_Sprite[0].Create("data\\texture\\ui\\life_bar\\life_bar.png");
	m_Sprite[1].Create("data\\texture\\ui\\life_bar\\life_gage.png");

	// ゲームメインシーン取得
	m_GameMain = (CGameMain*)aqua::FindGameObject("GameMainScene");
	m_Camera = m_GameMain->GetCamera();

	m_Unit = (IUnit*)GetParent();
}

void CLifeBar::Update(void)
{
	// ワールド座標をスクリーン座標に変換する夢のような関数
	aqua::CVector3 pos = ConvWorldPosToScreenPos(m_Unit->GetPosition());
	
	CalcLifeBar();

	// スプライトの中心座標をユニットのスクリーン座標に合わせる
	m_Sprite[1].SetCenterPosition(aqua::CVector2(pos.x, pos.y - 30.0f));
	m_Sprite[0].position = m_Sprite[1].position;
}

void CLifeBar::Draw(void)
{
	m_Sprite[0].Draw();
	m_Sprite[1].Draw();

}

void CLifeBar::Finalize(void)
{
	m_Sprite[0].Delete();
	m_Sprite[1].Delete();
}

void CLifeBar::CalcLifeBar(void)
{
	float rect = m_Sprite[0].GetTextureWidth() / m_Unit->GetMaxLife();
	m_Sprite[0].rect.right = rect * m_Unit->GetLife();
}
