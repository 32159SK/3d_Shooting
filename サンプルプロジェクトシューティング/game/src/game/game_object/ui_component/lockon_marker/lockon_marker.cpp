#include "../../game_object.h"
#include "lockon_marker.h"

CLockOnMarker::CLockOnMarker(aqua::IGameObject* parent)
	: IUIComponent(parent,"LockOnMarker")
{
}

void CLockOnMarker::Initialize(void)
{
	// 画像の生成
	m_Sprite.Create("data\\texture\\ui\\lock_on.png");

	// ゲームメインシーン取得
	m_GameMain = (CGameMain*)aqua::FindGameObject("GameMainScene");
	// ゲームメインシーンからカメラのポインタを取得
	m_Camera = m_GameMain->GetCamera();
	// 親クラスを使用者としてポインタを取得
	m_User = (IUnit*)GetParent();
}

void CLockOnMarker::Update(void)
{
	// 対象がnullまたはロックオンしていないなら処理しない
	if (!m_Target || !m_User->GetLockOnFlag())
		return;

	// ワールド座標をスクリーン座標に変換する夢のような関数
	aqua::CVector3 pos = ConvWorldPosToScreenPos(m_Target->GetPosition());

	// スプライトの中心座標をロックオンしている敵のスクリーン座標に合わせる
	m_Sprite.SetCenterPosition(aqua::CVector2(pos.x, pos.y));
}

void CLockOnMarker::Draw(void)
{
	// 対象がnullでないかつ使用者がロックオン中
	if (m_Target && m_User->GetLockOnFlag())
		m_Sprite.Draw();
}

void CLockOnMarker::Finalize(void)
{
	// スプライトの削除
	m_Sprite.Delete();
}
