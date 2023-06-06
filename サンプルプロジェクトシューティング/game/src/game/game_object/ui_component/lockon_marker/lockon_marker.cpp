#include "../../game_object.h"
#include "lockon_marker.h"

CLockOnMarker::CLockOnMarker(aqua::IGameObject* parent)
	: IUIComponent(parent,"LockOnMarker")
{
}

void CLockOnMarker::Initialize(void)
{
	m_Sprite.Create("data\\texture\\ui\\lock_on.png");

	// ゲームメインシーン取得
	m_GameMain = (CGameMain*)aqua::FindGameObject("GameMainScene");
	m_Camera = m_GameMain->GetCamera();

	m_Player = (CPlayer*)GetParent();
}

void CLockOnMarker::Update(void)
{
	// 敵がnullまたはロックオンしていないなら処理しない
	if (!m_LockOnEnemy || !m_Player->GetLockOnFlag())
		return;

	// ワールド座標をスクリーン座標に変換する夢のような関数
	aqua::CVector3 pos = ConvWorldPosToScreenPos(m_LockOnEnemy->GetPosition());

	// スプライトの中心座標をロックオンしている敵のスクリーン座標に合わせる
	m_Sprite.SetCenterPosition(aqua::CVector2(pos.x, pos.y));
}

void CLockOnMarker::Draw(void)
{
	if (m_LockOnEnemy && m_Player->GetLockOnFlag())
		m_Sprite.Draw();
}

void CLockOnMarker::Finalize(void)
{
	m_Sprite.Delete();
}
