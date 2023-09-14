#include "../game_object.h"
#include "player.h"

const float CPlayer::m_shot_ct = 0.5f;
const float CPlayer::m_change_shotCT = 0.5f;
const float CPlayer::m_ago_pos_time = 0.2f;
const float CPlayer::m_invincible_time = 2.0f;
const float CPlayer::m_flash_time = 0.1f;
const float CPlayer::m_lock_range = 200.0f;
const float CPlayer::m_width = 10.0f;
const float CPlayer::m_height = 10.0f;
const float CPlayer::m_depth = 10.0f;
const float CPlayer::m_speed = 1.0f;
const float CPlayer::m_font_size = 30.0f;
const int   CPlayer::m_max_life = 20;

CPlayer::CPlayer(aqua::IGameObject* parent)
	: IUnit(parent, "Player", "Player")
	, m_Invincible(false)
	, m_AgoPosition(aqua::CVector3::ZERO)
	, m_Floor(nullptr)
	, m_EnemyManager(nullptr)
	, m_LockOnEnemy(nullptr)
	, m_LockOnMarker(nullptr)
{
}

void CPlayer::Initialize(aqua::CVector3 pop_pos, CStageManager* st_m, CBulletManager* bm)
{
	// ライフバーの生成
	m_LifeBar = aqua::CreateGameObject<CUniqueLifeBar>(this);

	// ロックオンマーカークラスを生成しポインタを入れる
	m_LockOnMarker = aqua::CreateGameObject<CLockOnMarker>(this);

	// ライフ最大値を代入
	m_MaxLife = m_max_life;
	m_Life = m_MaxLife;

	// 基本的なユニットの初期化を基底クラスの初期化を呼び出して行う
	IUnit::Initialize(pop_pos, m_width, m_height, m_depth,st_m, bm);
	
	// その他基本設定
	m_UnitType = UNIT_TYPE::PLAYER;
	m_ShotBullet = BULLET_TYPE::NORMAL;
	m_BulletManager->SetPlayer(this);
	m_Speed = m_speed;

	// 無敵時間の設定
	m_InvincibleTimer.Setup(m_invincible_time);

	// フラッシュタイマーの設定
	m_FlashTimer.Setup(m_flash_time);

	// 切り替えタイマーのセットアップ
	m_ChangeCT.Setup(m_change_shotCT);
	// 射撃間隔タイマーのセットアップ
	m_ShotCT.Setup(m_shot_ct);
	
	// 追尾座標間隔タイマーのセットアップ
	m_AgoPosTimer.Setup(m_ago_pos_time);

	// ロックオンタイマーのセットアップ
	m_LockonTimer.Setup(0.1f);

	// モデルのロード
	m_Model.Load("data\\model\\player.mv1");

	// 床のポインタを取る
	m_Floor = (CFloor*)aqua::FindGameObject("Floor");

	// 弾アイコンの描画位置変数を宣言
	aqua::CVector2 icon_pos = aqua::CVector2::ZERO;

	// 弾のアイコンの生成
	for (int i = 0; i < (int)BULLET_TYPE::MAX; ++i)
	{
		// 弾種名を管理クラスから受け取り、それを用いてファイルパスにする
		m_BulletIcon[i].Create("data\\texture\\ui\\icon\\" + m_BulletManager->GetBulletName((BULLET_TYPE)i) + ".png");
		// X座標は一番端、Y座標はライフバーの上にする
		icon_pos.x = (float)(aqua::GetWindowWidth() - m_BulletIcon[i].GetTextureWidth());
		icon_pos.y = m_LifeBar->GetFramePosition().y - m_BulletIcon[i].GetTextureHeight();
		// 最後に計算した座標を代入
		m_BulletIcon[i].position = icon_pos;
	}
}

void CPlayer::Update(void)
{
	// キューブの水平回転角度を合わせる
	m_Cube.m_HRotate = m_Rotate;

	// 追尾座標間隔タイマーの更新
	m_AgoPosTimer.Update();

	// 射撃
	Shot();
	
	// 無敵状態ならタイマーを更新
	if (m_Invincible)
	{
		m_InvincibleTimer.Update();
		// ここでフラッシュタイマーも更新
		m_FlashTimer.Update();
		// 自機が死んでいないかつ、フラッシュタイマーが終了したら自機の可視化フラグを入れ替えタイマーをリセット
		if (!m_DeadFlag && m_FlashTimer.Finished())
		{
			m_Model.visible = !m_Model.visible;
			m_FlashTimer.Reset();
		}
	}
	// 終了時に無敵を解除しタイマーをリセット
	if (m_InvincibleTimer.Finished())
	{
		// 可視化フラグを戻し、タイマーもリセットしておく
		m_Model.visible = true;
		m_FlashTimer.Reset();
		m_Invincible = false;
		m_InvincibleTimer.Reset();
	}

	// 移動
	Move();

	// 自身の子オブジェクト(この場合はライフバー)の更新
	IGameObject::Update();

	// ここで敵が追尾する用のポジションを取っておく
	if (m_AgoPosTimer.Finished())
	{
		m_AgoPosition = m_Position;
		m_AgoPosTimer.Reset();
	}

	// 当たり判定のキューブと座標を合わせる
	m_Cube.position = m_Position;

	// モデルの座標と回転角度を合わせる
	m_Model.position = m_Cube.position;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CPlayer::Draw(void)
{
	IUnit::Draw();
	// 弾アイコンの描画(現在選択中の弾種のみ描画する)
	for (int i = 0; i < (int)BULLET_TYPE::MAX; ++i)
		if (i == (int)m_ShotBullet)
			m_BulletIcon[i].Draw();
}

void CPlayer::Finalize(void)
{
	IUnit::Finalize();
	// 弾アイコンの解放
	for (int i = 0; i < (int)BULLET_TYPE::MAX; ++i)
		m_BulletIcon[i].Delete();
}

bool CPlayer::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)
{
	// 無敵なら処理をやめる
	if (m_Invincible)
		return false;
	// 基底ユニットクラスの被弾確認を呼び出し当たっていたら無敵フラグを真にする
	if (IUnit::CheckHitBullet(type, sphere, damage))
	{
		m_Invincible = true;
		return true;
	}
	else
		return false;
}

bool CPlayer::CheckHitBeam(UNIT_TYPE type, aqua::CCapsulePrimitive capsule, int damage)
{
	// 無敵なら処理をやめる
	if (m_Invincible)
		return false;
	// 基底ユニットクラスの被弾確認を呼び出す
	if (IUnit::CheckHitBeam(type, capsule, damage))
		return true;
	else
		return false;
}

void CPlayer::LifeHeal(int heal_value)
{
	// 回復値と現在残ライフの計が上限を超えるなら上限に合わせる
	if (m_max_life <= m_Life + heal_value)
		m_Life = m_max_life;
	else
		m_Life += heal_value;	// 越えなければそのまま回復値分加算する

	// 回復後の値でライフバーを再計算
	m_LifeBar->CalcLifeBar();
}

void CPlayer::Shot(void)
{
	// 弾種切り替えタイマーと射撃タイマーの更新
	m_ChangeCT.Update();
	m_ShotCT.Update();

	if (!m_MoveFlag)
		return;

	// 弾の種類の切り替え
	if (m_ChangeCT.Finished())
	{
		// ホイールの入力値を取得
		float wheel_value = (float)aqua::mouse::GetWheel();

		// マイナスであれば前の弾に変更(例REFLECT→NOMAL)
		if (wheel_value > 0 && m_ShotBullet != BULLET_TYPE::NORMAL)
		{
			m_ShotBullet = (BULLET_TYPE)((int)m_ShotBullet - 1);
			m_ChangeCT.Reset();
			// SEを再生
			m_SoundManager->Play(SOUND_ID::s_SELECT);
		}
		// プラスであれば次の弾に変更(例NOMAL→REFLECT)
		else if (wheel_value < 0 && (int)m_ShotBullet < (int)BULLET_TYPE::MAX - 1)
		{
			// +1の弾に変更(例NOMAL→FAST)
			m_ShotBullet = (BULLET_TYPE)((int)m_ShotBullet + 1);
			m_ChangeCT.Reset();
			// SEを再生
			m_SoundManager->Play(SOUND_ID::s_SELECT);
		}

	}

	// 正面座標
	aqua::CVector3 front;

	front.x = sin(aqua::DegToRad(m_Rotate));
	front.z = cos(aqua::DegToRad(m_Rotate));

	if (m_ShotCT.Finished() && (aqua::mouse::Button(aqua::mouse::BUTTON_ID::LEFT)))
	{
		// ビームでなければSEを再生(ビームはチャージ音等が特殊なのでビームクラス内で再生)
		if (m_ShotBullet != BULLET_TYPE::BEAM)
			m_SoundManager->Play(SOUND_ID::s_SHOT);
		// 自機の正面から弾を撃つ
			m_BulletManager->Create(m_Position + front * 10.0f, front * 10.5f, m_UnitType, m_ShotBullet, this);
			m_ShotCT.Reset();
	}
}

void CPlayer::Move(void)
{
	// 行動不可(ビーム待機中)
	if (!m_MoveFlag)
	{
		// マウス中央ボタン(ホイール押し込み)でキャンセル
		if (aqua::mouse::Button(aqua::mouse::BUTTON_ID::MIDDLE))
		{
			// イメージ的には無理やり中断するので自傷ダメージ
			Damage(2);
			m_EffectManager->Create(EFFECT_ID::BEAM_HIT, m_Position,0.0f,8.0f);
			m_MoveFlag = true;
		}
		else
			return;
	}

	// 操作
	Operation();

	// ロックオン
	LockOn();

	// マウス追従
	MouseTrack();
}

void CPlayer::Damage(int damage)
{
	// チュートリアル中はダメージを受けない
	if (m_TutorialMode)
		return;

	// それ以外は基底クラスと同じ
	IUnit::Damage(damage);
}

void CPlayer::Dead(void)
{
	IUnit::Dead();
	m_Model.visible = false;
}

void CPlayer::Operation(void)
{
	using namespace aqua::keyboard;
	const float to_delta = 60.0f * aqua::GetDeltaTime();

	// 移動速度は更新の度にリセット
	m_Velocity = aqua::CVector3::ZERO;

	if (Button(KEY_ID::W)) m_Velocity += aqua::CVector3::FRONT;
	if (Button(KEY_ID::S)) m_Velocity += aqua::CVector3::BACK;
	if (Button(KEY_ID::A)) m_Velocity += aqua::CVector3::LEFT;
	if (Button(KEY_ID::D)) m_Velocity += aqua::CVector3::RIGHT;

	m_Velocity.Normalize();
	m_Velocity *= (m_Speed * to_delta);

	// 壁と当たってたらそこで止まる
	if (m_StageManager->StageObjectCollision(m_Position, m_Position + m_Velocity * m_Width, false))
		return;


	// 座標に移動速度を加算する
	m_Position += m_Velocity;
	AQUA_DEBUG_LOG("X:" + std::to_string(m_Position.x) + ",Z" + std::to_string(m_Position.z));
}

void CPlayer::MouseTrack(void)
{
	// マウス座標を手前と奥で2点取り、3次元のベクトルクラスで変数に入れる
	aqua::CVector3 mpos_A = aqua::CVector3((float)aqua::mouse::GetCursorPos().x
		, (float)aqua::mouse::GetCursorPos().y, 0.0f) ;
	aqua::CVector3 mpos_B = aqua::CVector3((float)aqua::mouse::GetCursorPos().x
		, (float)aqua::mouse::GetCursorPos().y, 1.0f) ;

	// スクリーン座標をワールド座標に変換する関数を使い、2点を変換
	mpos_A = ConvScreenPosToWorldPos(mpos_A);
	mpos_B = ConvScreenPosToWorldPos(mpos_B);

	// 床と2点のマウス座標でレイキャストを行い接触座標を求める
	m_Floor->Raycast(mpos_A, mpos_B);
	aqua::CVector3 raycast = m_Floor->GetRaycastPos();

	// ロックオンしていないならマウスを追従して回転
	if (!m_LockON)
	{
		// レイキャスト座標と自身の座標の差分を求める
		aqua::CVector3 v = raycast - m_Position;

		// ベクトルのノーマライズ
		v.Normalize();

		// 2点から回転値を求める
		m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));
	}
}

void CPlayer::LockOn(void)
{
	// ロックオンタイマーの更新
	m_LockonTimer.Update();

	// タイマーが終了しているかつ、キーが入力された
	if (aqua::mouse::Released(aqua::mouse::BUTTON_ID::RIGHT) && m_LockonTimer.Finished())
	{
		m_LockON = !m_LockON;
		// 一度ロックオンした同じ敵を近くないのに再度ロックオンしないようnullを与える
		m_LockOnEnemy = nullptr;
		m_LockOnMarker->SetTarget(m_LockOnEnemy);
		m_LockonTimer.Reset();
	}

	// そもそもロックオンしてない(余計な処理をしないようif文は分ける)
	if (!m_LockON)
		return;

	// エネミーがnullまたは、取得したエネミーが死んだ
	if (!m_LockOnEnemy || m_LockOnEnemy->GetDead())
	{
		m_LockOnEnemy = m_EnemyManager->GetNearest(m_Position);
		m_LockOnMarker->SetTarget(m_LockOnEnemy);
		return;
	}

	// プレイヤーと自身の距離
	aqua::CVector3 v = m_LockOnEnemy->GetPosition() - m_Position;

	// 範囲外ならロックオンを終了
	if (m_lock_range < abs(aqua::CVector3::Length(v)))
	{
		m_LockOnEnemy = nullptr;
		m_LockOnMarker->SetTarget(m_LockOnEnemy);
		m_LockON = false;
		return;
	}

	// ベクトルのノーマライズ
	v.Normalize();

	// 2点から回転角度を求める
	m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));
}

