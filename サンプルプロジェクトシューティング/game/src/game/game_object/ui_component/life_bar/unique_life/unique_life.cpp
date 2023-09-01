#include "../../../game_object.h"
#include "unique_life.h"

CUniqueLifeBar::CUniqueLifeBar(aqua::IGameObject* parent)
	: CLifeBar(parent)
{
}

void CUniqueLifeBar::Initialize(void)
{
	m_Unit = (IUnit*)GetParent();

	// ゲームオブジェクトの名前(プレイヤーなら"Player")を取得
	m_UnitName = m_Unit->GetGameObjectName();

	// 取得した名前をパスに含めてスプライトを生成
	m_Sprite[0].Create("data\\texture\\ui\\life_bar\\" + m_UnitName + "_life_bar.png");
	m_Sprite[1].Create("data\\texture\\ui\\life_bar\\" + m_UnitName + "_life_gauge.png");

	// 描画位置の変数
	aqua::CVector2 pos = aqua::CVector2::ZERO;

	// 名前に応じて位置を決める
	if (m_UnitName == "Player")
	{
		// プレイヤーなら画面右下
		pos.x = (float)aqua::GetWindowWidth() - m_Sprite[1].GetTextureWidth();
		pos.y = (float)aqua::GetWindowHeight() - m_Sprite[1].GetTextureHeight();
	}
	else
	{
		// プレイヤーでない → ボスのライフバーなので画面上部中央
		pos.x = ((float)aqua::GetWindowWidth() - m_Sprite[1].GetTextureWidth()) / 2.0f;
	}
	// スプライトに描画位置を代入
	m_Sprite[1].position = pos;
	m_Sprite[0].position = pos;

}

void CUniqueLifeBar::Update(void)
{

}

void CUniqueLifeBar::CalcLifeBar(void)
{
	if (!this || m_Unit->GetDead())
		return;
	float rect = m_Sprite[0].GetTextureWidth() / m_Unit->GetMaxLife();
	// 名前に応じて位置を決める
	if (m_UnitName == "Player")
	{
		float left = rect * (m_Unit->GetMaxLife() - m_Unit->GetLife());

		// プレイヤーなら左から
		m_Sprite[0].rect.left = left;
		m_Sprite[0].position.x = m_Sprite[1].position.x + left;
	}
	else
		// ボスのライフバーは右から
		m_Sprite[0].rect.right = rect * m_Unit->GetLife();
}

