#include "../../../game_object.h"
#include "tutorial.h"

const float CTutorial::m_tutorial_move_length = 150.0f;
const float CTutorial::m_key_icon_size = 100.0f;
const float CTutorial::m_mouse_icon_width = 150.0f;
const std::string CTutorial::m_tutorial_path = "data\\csv\\tutorial_text.csv";
const std::string CTutorial::m_key_icon_path = "data\\csv\\key_icon_";
const std::string CTutorial::m_mouse_path = "data\\csv\\mouse_icon_";
const aqua::CVector2 CTutorial::m_icon_pos = aqua::CVector2(aqua::GetWindowWidth() / 2.0f, aqua::GetWindowHeight() / 2.0f);
const aqua::CVector2 CTutorial::m_key_icon_formation[] =
{
	aqua::CVector2(1.0f,0.0f),	// W
	aqua::CVector2(0.0f,1.0f),	// A
	aqua::CVector2(1.0f,1.0f),	// S
	aqua::CVector2(2.0f,1.0f)	// D
};

CTutorial::CTutorial(aqua::IGameObject* parent)
	:CGameMain(parent)
	,m_TextDrawCount(0)
	,m_MoveLength(0.0f)
	,m_NotBeamFiring(true)
	,m_PlayerPos(aqua::CVector3::ZERO)
	,m_State(STATE::START)
	,m_Phase(TUTORIAL_PHASE::MOVE)
	,m_TutorialMessage(nullptr)
{
}

void CTutorial::Initialize(void)
{
	// 基底クラスとなっているgゲームメインシーンの初期化を呼ぶ
	CGameMain::Initialize();

	// スプライトの生成
	for (int i = 0; i < 4; ++i)
	{
		// iを加えてそれぞれのファイルパスにする
		m_KeyIcon[i].Create(m_key_icon_path + std::to_string(i) + ".png");
		// 描画座標の計算
		m_KeyIcon[i].position = m_key_icon_formation[i] * m_key_icon_size + m_icon_pos;
		
		// ついでにマウスアイコンも生成する
		if (i < 3)
		{
			// キーアイコン同様にiを加えてそれぞれのファイルパスにする
			m_MouseIcon[i].Create(m_mouse_path + std::to_string(i) + ".png");
			// マウスアイコンは全部同じ座標でOK(わざわざずらすメリットがない)
			m_MouseIcon[i].position = m_icon_pos;
		}
	}
}

void CTutorial::Update(void)
{
	// 子オブジェクトの更新
	IGameObject::Update();

	// 状態に応じて処理を分ける
	switch (m_State)
	{
	case CTutorial::STATE::START:	TutorialStart();	break;
	case CTutorial::STATE::PLAY:	TutorialPlay();		break;
	case CTutorial::STATE::END:		TutorialFinish();	break;
	}
}

void CTutorial::Draw(void)
{
	IGameObject::Draw();


	// キーアイコンの描画
	if(m_Phase== TUTORIAL_PHASE::MOVE)
		for (int i = 0; i < 4; ++i)
			m_KeyIcon[i].Draw();

	// マウスアイコン描画
	else if(m_Phase== TUTORIAL_PHASE::MOUSE
		|| m_Phase == TUTORIAL_PHASE::SHOT
		|| m_Phase == TUTORIAL_PHASE::LOCKON)
		MouseIconDraw();
}

void CTutorial::Finalize(void)
{
	IGameObject::Finalize();

	// アイコンの削除
	for (int i = 0; i < 4; ++i)
	{
		m_KeyIcon[i].Delete();
		if (i < 3)
			m_MouseIcon[i].Delete();
	}
}

void CTutorial::TutorialStart(void)
{
	// 子オブジェクトを探査しステージ管理のポインタ取得
	CStageManager* sm = (CStageManager*)IGameObject::FindChild("StageManager");
	// チュートリアルセット
	m_Player->SetTutorial();
	m_EnemyManager->SetTutorial();
	sm->SetTutorial();

	// 状態を遷移
	m_State = STATE::PLAY;
}

void CTutorial::TutorialPlay(void)
{
	// カメラの更新
	m_Camera.m_Target = m_Player->GetPosition();
	m_Camera.Update();
	// 子オブジェクトの更新
	IGameObject::Update();

	// 段階に応じて処理を分ける
	switch (m_Phase)
	{
	case CTutorial::TUTORIAL_PHASE::MOVE:	TutorialMove();		break;
	case CTutorial::TUTORIAL_PHASE::MOUSE:	TutorialMouse();	break;
	case CTutorial::TUTORIAL_PHASE::LOCKON:	TutorialLockOn();	break;
	case CTutorial::TUTORIAL_PHASE::SHOT:	TutorialShot();		break;
	case CTutorial::TUTORIAL_PHASE::BEAM:	TutorialBeam();		break;
	}

}

void CTutorial::TutorialFinish(void)
{
	// タイトルシーンに切り替える
	Change(SCENE_ID::TITLE);
}

void CTutorial::TutorialMove(void)
{
	// プレイヤーの現在座標がこのクラスで記録している座標と異なる→移動している
	if (m_Player->GetPosition() != m_PlayerPos)
		// 差分を移動距離として加算
		m_MoveLength += abs(aqua::CVector3::Length(m_Player->GetPosition() - m_PlayerPos));

	if (m_MoveLength > m_tutorial_move_length)
	{
		// 
		MessageSetUp();
	}
}

void CTutorial::TutorialMouse(void)
{
}

void CTutorial::TutorialLockOn(void)
{
	m_EnemyManager->Create(aqua::CVector3::ZERO, ENEMY_ID::MOB);
}

void CTutorial::TutorialShot(void)
{

}

void CTutorial::TutorialBeam(void)
{
	// 説明中は弾種を常にビームに
	m_Player->SetBulletType(BULLET_TYPE::BEAM);

	// 行動フラグと一致しない
	if (m_Player->GetMoveFlag() != m_NotBeamFiring)
	{
		// ビーム確認フラグに行動フラグを代入
		// これで一致しないのはビームを撃つor終了した最初のフレームのみになる(この部分の処理はビーム前後でしか行いたくない)
		m_NotBeamFiring = m_Player->GetMoveFlag();
		
		// メッセージ描画処理を行い、次の段階へ
		MessageSetUp();
	}
}

void CTutorial::TextDataLoad(void)
{
	// aqua内のCSVクラスを呼び出してロード
	aqua::CCSVLoader csv;
	csv.Load(m_tutorial_path);

	int file_row = csv.GetRows();

	for (int i = 0; i < file_row; ++i)
		// 読み込んだテキストを末尾に追加
		m_TutorialText.push_back(csv.GetString(i, 0));

	// CSVのアンロード
	csv.Unload();
}

void CTutorial::MouseIconDraw(void)
{
	// マウスアイコンの描画
	m_MouseIcon[0].Draw();
	// 他は"押されている時だけ"描画する
	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
		m_MouseIcon[1].Draw();
	// クリック画像
	else if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::RIGHT))
	{
		// 右クリックは反転
		m_MouseIcon[1].scale.x *= -1.0f;
		m_MouseIcon[1].Draw();
	}
	// ホイール画像
	else if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::MIDDLE)
		|| aqua::mouse::GetWheel() != 0.0f)
		m_MouseIcon[2].Draw();
}

void CTutorial::MessageSetUp(void)
{
	// 念のためnullでないなら処理しない
	if (m_TutorialMessage)
		return;

	// カウントを増やしメッセージ描画用クラスを生成する
	m_TextDrawCount++;

	m_TutorialMessage = aqua::CreateGameObject<CTutorialMessage>(this);
	m_TutorialMessage->Initialize(m_TutorialText[m_TextDrawCount]);
}
