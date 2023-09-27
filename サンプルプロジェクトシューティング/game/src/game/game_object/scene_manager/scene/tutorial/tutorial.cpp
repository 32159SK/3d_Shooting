#include "../../../game_object.h"
#include "tutorial.h"

const int	CTutorial::m_max_text_count = 12;
const int	CTutorial::m_lock_on_text_num = 7;
const float CTutorial::m_tutorial_move_length = 250.0f;
const float CTutorial::m_mouse_move_time = 1.0f;
const float CTutorial::m_shot_time = 4.0f;
const std::string CTutorial::m_tutorial_path = "data\\csv\\tutorial_text.csv";

CTutorial::CTutorial(aqua::IGameObject* parent)
	:CGameMain(parent)
	,m_TextDrawCount(0)
	,m_MoveLength(0.0f)
	,m_EnemyPop(false)
	,m_ShotFlag(false)
	,m_NotBeamFiring(true)
	,m_PlayerPos(aqua::CVector3::ZERO)
	,m_State(STATE::START)
	,m_Phase(TUTORIAL_PHASE::MOVE)
	,m_TutorialEnemy(nullptr)
	,m_TutorialMessage(nullptr)
{
}

void CTutorial::Initialize(void)
{
	// 基底クラスとなっているgゲームメインシーンの初期化を呼ぶ
	CGameMain::Initialize();

	// チュートリアルテキストのロード
	TextDataLoad();
}

void CTutorial::Update(void)
{
	// 状態に応じて処理を分ける
	switch (m_State)
	{
	case CTutorial::STATE::START:	TutorialStart();	break;
	case CTutorial::STATE::PLAY:	TutorialPlay();		break;
	case CTutorial::STATE::END:		TutorialFinish();	break;
	}

	// 子オブジェクトの更新
	IGameObject::Update();

	// Zキーでいつでもタイトルシーンに戻れる
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
		Change(SCENE_ID::TITLE);
}

void CTutorial::Draw(void)
{
	IGameObject::Draw();
}

void CTutorial::Finalize(void)
{
	IGameObject::Finalize();
}

void CTutorial::TutorialStart(void)
{
	// 子オブジェクトを探査しステージ管理のポインタ取得
	CStageManager* sm = (CStageManager*)IGameObject::FindChild("StageManager");
	// チュートリアルセット
	m_Player->SetTutorial();
	m_EnemyManager->SetTutorial();
	sm->SetTutorial();
	// ウェーブ切り替え処理を呼び出し、ステージを生成
	sm->WaveChange(0);

	// 最初のメッセージを描画
	MessageSetUp();

	// 状態を遷移
	m_State = STATE::PLAY;
}

void CTutorial::TutorialPlay(void)
{
	// カメラの更新
	m_Camera.m_Target = m_Player->GetPosition();
	m_Camera.Update();


	// 段階に応じて処理を分ける
	switch (m_Phase)
	{
	case CTutorial::TUTORIAL_PHASE::MOVE:	TutorialMove();		break;
	case CTutorial::TUTORIAL_PHASE::MOUSE:	TutorialMouse();	break;
	case CTutorial::TUTORIAL_PHASE::SHOT:	TutorialShot();		break;
	case CTutorial::TUTORIAL_PHASE::LOCKON:	TutorialLockOn();	break;
	case CTutorial::TUTORIAL_PHASE::BEAM:	TutorialBeam();		break;
	}

}

void CTutorial::TutorialFinish(void)
{
}

void CTutorial::TutorialMove(void)
{
	// プレイヤーの現在座標がこのクラスで記録している座標と異なる→移動している
	if (m_Player->GetPosition() != m_PlayerPos)
	{
		// 差分を移動距離として加算
		m_MoveLength += abs(aqua::CVector3::Length(m_Player->GetPosition() - m_PlayerPos));
		// 座標を再保存
		m_PlayerPos = m_Player->GetPosition();
	}
	
	// 移動距離が一定値を超えたらメッセージを表示し次の段階へ
	if (m_MoveLength > m_tutorial_move_length)
	{
		// メッセージのセットアップ成否
		if (MessageSetUp())
		{
			// 次の段階へ
			m_Phase = TUTORIAL_PHASE::MOUSE;

			// マウス座標をこの段階で保存しておく
			m_MousePos = aqua::mouse::GetCursorPos();
			// タイマーのセットアップ
			m_TutorialTimer.Setup(m_mouse_move_time);
		}
	}
}

void CTutorial::TutorialMouse(void)
{
	// マウス座標がこのクラスで記録している座標と異なる→移動している
	if (aqua::mouse::GetCursorPos() != m_MousePos)
	{
		// タイマーを更新
		m_TutorialTimer.Update();

		// タイマーが終了
		if (m_TutorialTimer.Finished())
			// メッセージのセットアップ
			MessageSetUp();

		// マウス座標を再保存
		m_MousePos = aqua::mouse::GetCursorPos();
	}

	// タイマーが終了
	else if (m_TutorialTimer.Finished() && MessageSetUp())
	{
		// 次の段階へ
		m_Phase = TUTORIAL_PHASE::SHOT;

		// タイマーの再設定
		m_TutorialTimer.Setup(m_shot_time);
	}
}

void CTutorial::TutorialShot(void)
{
	// マウス左クリック
	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
		m_ShotFlag = true;

	// 射撃がされたらタイマーの更新
	if (m_ShotFlag)
		m_TutorialTimer.Update();

		// タイマーが終了
	if (m_TutorialTimer.Finished() && MessageSetUp())
	{
		// 次の段階へ
		m_Phase = TUTORIAL_PHASE::LOCKON;

		// タイマーのリセット
		m_TutorialTimer.Reset();
	}
}

void CTutorial::TutorialLockOn(void)
{
	m_TutorialTimer.Update();

	// タイマーが終了しているかつ一定の回数以上メッセージを描画しない
	if (m_TutorialTimer.Finished() && m_TextDrawCount < m_lock_on_text_num)
	{
		// 敵を出現させていない
		if (!m_EnemyPop && MessageSetUp())
		{
			// ロックオン確認用の敵を出現させる(ボス部位生成を流用してポインタを受け取れるようにする)
			m_TutorialEnemy = m_EnemyManager->CreateBossParts(aqua::CVector3::ZERO, ENEMY_ID::FIXED);
			// 出現させたのでフラグを真に
			m_EnemyPop = true;

			// タイマーのリセット
			m_TutorialTimer.Reset();
		}
		// タイマーが終了したら新しいメッセージを流す
		else if(m_EnemyPop)
		{
			MessageSetUp();			// タイマーのリセット
			m_TutorialTimer.Reset();
		}
	}

	// 敵が死んでかつ描画回数が合っておりメッセージの描画が行えたら次の段階へ
	if (m_TutorialEnemy->GetDead() && m_TextDrawCount == m_lock_on_text_num &&MessageSetUp())
		m_Phase = TUTORIAL_PHASE::BEAM;
}

void CTutorial::TutorialBeam(void)
{
	// 弾種を常にビームに
	m_Player->SetBulletType(BULLET_TYPE::BEAM);

	// 行動フラグと一致しない
	if (m_Player->GetMoveFlag() != m_NotBeamFiring && MessageSetUp())
	{
		// ビーム確認フラグに行動フラグを代入
		// これで一致しないのはビームを撃つor終了した最初のフレームのみになる(この部分の処理はビーム前後でしか行いたくない)
		m_NotBeamFiring = m_Player->GetMoveFlag();
	}
	
	// メッセージの描画回数がテキスト総数を超えるなら状態を遷移
	if (m_TextDrawCount > m_max_text_count)
		m_State = STATE::END;
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

bool CTutorial::MessageSetUp(void)
{
	// 他のメッセージが存在し、それが終了していないなら処理をせず偽を返す
	if (m_TutorialMessage && !m_TutorialMessage->GetEnd())
		return false;
	else if(m_TutorialMessage)
		// 中身を削除する(null時は通らない)
		m_TutorialMessage->DeleteObject();

	// メッセージ描画用クラスを生成する
	m_TutorialMessage = aqua::CreateGameObject<CTutorialMessage>(this);
	m_TutorialMessage->Initialize(m_TutorialText[m_TextDrawCount]);

	// カウントを増やす
	m_TextDrawCount++;
	return true;
}
