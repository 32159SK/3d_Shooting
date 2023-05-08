
#include "../../game_object.h"
#include "rader.h"

const std::string CRader::m_unit_path = "data\\texture\\unit_icon.png";

CRader::CRader(aqua::IGameObject* parent)
	: IUIComponent(parent, "Rader")
	, m_EnemyCount(0)
{
}

void CRader::Initialize(CPlayer* player)
{
	m_Player = player;

	// レーダー画像の生成
	m_RaderSprite.Create("data\\texture\\rader.png");
	m_RaderSprite.position = aqua::CVector2::ZERO;
	// レーダー画像のサイズの取得
	m_RaderSize.x = m_RaderSprite.GetTextureWidth();
	m_RaderSize.y = m_RaderSprite.GetTextureHeight();


	// プレイヤーの自機表示アイコンの生成
	m_PlayerSprite.Create(m_unit_path);
	m_PlayerSprite.color = aqua::CColor::BLUE;
	m_PlayerSprite.anchor = aqua::CVector2(m_PlayerSprite.GetTextureWidth() / 2, m_PlayerSprite.GetTextureHeight() / 2);
	m_PlayerSprite.position = SetRaderPos(m_Player->GetPosVector2())- m_PlayerSprite.anchor;

	m_Enemy = new CEnemy * [100];
}

void CRader::Update(void)
{

	for (int i = 0; i < m_EnemyCount; ++i)
		if (!m_Enemy[i]&&!m_Enemy[i]->GetDead())
			m_EnemySprite[i].visible = false;
		else
			m_EnemySprite[i].position = SetRaderPos(aqua::CVector2(m_Enemy[i]->GetPosVector2().x - m_Player->GetPosVector2().x,
				 m_Player->GetPosVector2().y-m_Enemy[i]->GetPosVector2().y))-m_EnemySprite[i].anchor;
}

void CRader::Draw(void)
{
	m_RaderSprite.Draw();
	for (int e = 0; e < m_EnemyCount; ++e)
		m_EnemySprite[e].Draw();
	m_PlayerSprite.Draw();
}

void CRader::Finalize(void)
{
	m_RaderSprite.Delete();
	m_PlayerSprite.Delete();
	for (int e = 0; e < m_EnemyCount; ++e)
		m_EnemySprite[e].Delete();
}

void CRader::SetEnemy(CEnemy* enemy)
{
	if (!enemy)
		return;
	// 末尾にエネミーポインタを追加
	m_Enemy[m_EnemyCount] = enemy;
	m_EnemyCount++;

	// スプライトクラスのメンバ変数を新しく定義
	aqua::CSprite ene_sp;
	ene_sp.Create(m_unit_path);
	ene_sp.anchor = aqua::CVector2(ene_sp.GetTextureWidth() / 2, ene_sp.GetTextureHeight() / 2);
	ene_sp.color = aqua::CColor::RED;
	// スプライトの末尾に追加
	m_EnemySprite.push_back(ene_sp);
}

aqua::CVector2 CRader::SetRaderPos(aqua::CVector2 pos)
{
	return pos/10.0f + m_RaderSize / 2.0f;
}
