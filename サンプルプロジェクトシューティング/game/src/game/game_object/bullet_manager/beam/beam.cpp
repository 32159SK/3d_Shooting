
#include "beam.h"

const float CBeam::m_max_range = 270.0f;
const float CBeam::m_charge_time = 4.0f;

CBeam::CBeam(aqua::IGameObject* parent)
	:IGameObject(parent,"Beam")
	, m_Damage(0)
	, m_Rotate(0.0f)
	, m_Radius(0.0f)
	, m_DamageFlag(false)
	, m_Finished(false)
	, m_StartPos(aqua::CVector3::ZERO)
	, m_EndPos(aqua::CVector3::ZERO)
	, m_Dir(aqua::CVector3::ZERO)
	, m_Attri(UNIT_TYPE::PLAYER)
	, m_BeamState(BEAM_STATE::CHARGE)
	, m_Effect(nullptr)
	, m_EffectManager(nullptr)
	, m_User(nullptr)
{
}

void CBeam::Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 dir, IUnit* user, CSoundManager* sm, CEffectManager* em)
{
	// 引数からビームの発射点や向き、使用者を設定
	m_StartPos = pop_pos;
	m_Radius = bullet_info.radius;
	m_Damage = bullet_info.damage;
	m_Attri = attri;
	m_Dir = dir;
	m_User = user;
	m_SoundManager = sm;
	m_EffectManager = em;

	// 向きを正規化
	m_Dir.Normalize();

	// 向きから回転角度を算出
	m_Rotate = aqua::RadToDeg(atan2(m_Dir.x, m_Dir.z));

	// 終点座標の仮決め
	m_EndPos = aqua::CVector3(0.0f, 0.0f, m_max_range);

	// 行列を使って始点を中心とした回転処理を行い、正確な終点座標を求める
	aqua::CMatrix mat;
	mat.RotationY(aqua::DegToRad(m_Rotate));
	mat.Translate(m_StartPos);
	m_EndPos *= mat;

	// コライダー用のカプセルクラスの設定
	m_Capsule.Setup(m_StartPos, m_EndPos, m_Radius);

	// エフェクトの再生
	m_Effect = m_EffectManager->CreateGetEffect(EFFECT_ID::BEAM, m_StartPos, m_Rotate);

	// タイマーのセット
	m_Timer.Setup(m_charge_time);

	// カプセルを描画する必要はない(あくまでもコライダー代わり)のでvisibleをfalseにする
	m_Capsule.visible = false;

	// 予測線の設定
	m_PredictionLine.Setup(m_StartPos, m_EndPos, aqua::CColor::RED);

	// ビーム使用中は動けないよう使用者の行動可能フラグを偽にする
	m_User->SetMoveFlag(false);

	// サウンド管理クラスを取得
	m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");

	// チャージ音のSEを再生開始
	m_SoundManager->Play(SOUND_ID::s_CHARGE);
}

void CBeam::Draw(void)
{
	m_Capsule.Draw();
	m_PredictionLine.Draw();
}

void CBeam::Update(void)
{
	switch (m_BeamState)
	{
	case CBeam::BEAM_STATE::CHARGE:Charge();break;
	case CBeam::BEAM_STATE::FIRING:Firing();break;
	case CBeam::BEAM_STATE::DESTROY:Destroy();break;
	}
	// 使用者が死ぬ、もしくはキャンセル(照射中に移動等)で中断
	if (!m_User || m_User->GetDead() || m_User->GetMoveFlag())
		m_BeamState = BEAM_STATE::DESTROY;

}

void CBeam::Charge(void)
{
	// チャージ中はダメージ判定なし
	m_DamageFlag = false;
	// タイマーを更新して終了したら状態を移行
	m_Timer.Update();
	if (m_Timer.Finished())
		m_BeamState = BEAM_STATE::FIRING;
}

void CBeam::Firing(void)
{
	// 発射関数内でダメージフラグが偽なのは最初のみなのでこのタイミングでSEを切り替える
	if (!m_DamageFlag)
	{
		m_SoundManager->Stop(SOUND_ID::s_CHARGE);
		m_SoundManager->Play(SOUND_ID::s_BEAM);
	}
	// ダメージ判定を有効にする
	m_DamageFlag = true;
	// 予測線の可視化をやめる
	m_PredictionLine.visible = false;
	
	// エフェクトの再生が終了したら状態を移行
	if (m_Effect->Finished())
		m_BeamState = BEAM_STATE::DESTROY;
}

void CBeam::Destroy(void)
{
	// SEが再生中なら止める
	if (m_SoundManager->IsPlaying(SOUND_ID::s_CHARGE))
		m_SoundManager->Stop(SOUND_ID::s_CHARGE);
	else if (m_SoundManager->IsPlaying(SOUND_ID::s_BEAM))
		m_SoundManager->Stop(SOUND_ID::s_BEAM);

	// ダメージ判定を無効
	m_DamageFlag = false;

	// エフェクトの描画を無効
	m_Effect->visible = false;

	// 使用者nullまたは死んでいないなら使用者を再度行動可能にする
	if (!m_User || !m_User->GetDead())
		m_User->SetMoveFlag(true);
	m_Finished = true;
	DeleteObject();
}
