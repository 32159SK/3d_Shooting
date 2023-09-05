
#include "../../game_object.h"
#include "rader.h"

const std::string CRader::m_unit_path = "data\\texture\\ui\\rader\\unit_icon.png";

CRader::CRader(aqua::IGameObject* parent)
	: IUIComponent(parent, "Rader")
	, m_EnemyCount(0)
{
}

void CRader::Initialize(CPlayer* player)
{
	m_Player = player;

	// レーダー画像の生成
	m_RaderSprite.Create("data\\texture\\ui\\rader\\rader.png");
	m_RaderSprite.position = aqua::CVector2::ZERO;
	// レーダー画像のサイズの取得
	m_RaderSize.x = (float)m_RaderSprite.GetTextureWidth();
	m_RaderSize.y = (float)m_RaderSprite.GetTextureHeight();


	// プレイヤーの自機表示アイコンの生成
	m_PlayerSprite.Create(m_unit_path);
	m_PlayerSprite.color = aqua::CColor::BLUE;
	m_PlayerSprite.anchor = aqua::CVector2(float(m_PlayerSprite.GetTextureWidth() / 2),float(m_PlayerSprite.GetTextureHeight() / 2));
	m_PlayerSprite.position = SetRaderPos(m_Player->GetPosVector2())- m_PlayerSprite.anchor;

	m_Enemy = new CEnemy * [100];
}

void CRader::Update(void)
{
	// 
	for (int i = 0; i < m_EnemyCount; ++i)
		if (m_Enemy[i]==nullptr || m_Enemy[i]->GetDead())
			m_EnemySprite[i].visible = false;
		else
		{
			// レーダー上のエネミーの座標
			m_EnemySprite[i].position = SetRaderPos(aqua::CVector2(m_Enemy[i]->GetPosVector2().x - m_Player->GetPosVector2().x,
				m_Player->GetPosVector2().y - m_Enemy[i]->GetPosVector2().y)) - m_EnemySprite[i].anchor;
			// エネミーの向きに合わせて回転
			m_EnemySprite[i].rotation = aqua::DegToRad(m_Enemy[i]->GetRotate());
		}
	// プレイヤーの向きに合わせて回転
	m_PlayerSprite.rotation = aqua::DegToRad(m_Player->GetRotate());
}

void CRader::Draw(void)
{
	m_RaderSprite.Draw();
	// 存在するエネミーで生きているもののみレーダー内で描画
	for (int i = 0; i < m_EnemyCount; ++i)
		if (m_Enemy[i] && !m_Enemy[i]->GetDead())
			m_EnemySprite[i].Draw();
	m_PlayerSprite.Draw();
}

void CRader::Finalize(void)
{
	m_RaderSprite.Delete();
	m_PlayerSprite.Delete();
	for (int i = 0; i < m_EnemyCount; ++i)
		m_EnemySprite[i].Delete();
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
	ene_sp.anchor = aqua::CVector2(float(ene_sp.GetTextureWidth() / 2),float(ene_sp.GetTextureHeight() / 2));
	ene_sp.color = aqua::CColor::RED;
	// スプライトの末尾に追加
	m_EnemySprite.push_back(ene_sp);
}

aqua::CVector2 CRader::SetRaderPos(aqua::CVector2 pos)
{
	return pos/10.0f + m_RaderSize / 2.0f;
}
