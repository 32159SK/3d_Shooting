#include "../game_object.h"
#include "unit.h"

const float IUnit::m_beam_damage_interval =0.3f;

IUnit::
IUnit(aqua::IGameObject* parent, const std::string& object_name)
	: aqua::IGameObject(parent,object_name)
	, m_Height(0.0f)
	, m_Width(0.0f)
	, m_Depth(0.0f)
	, m_Speed(0.0f)
	, m_Angle(0.0f)
	, m_MaxLife(0)
	, m_Life(0)
	, m_DeadFlag(true)
	, m_MoveFlag(true)
	, m_LockON(false)
	, m_Rotate(0.0f)
	, m_Position(aqua::CVector3::ZERO)
	, m_Velocity(aqua::CVector3::ZERO)
	, m_EffectManager(nullptr)
	, m_SoundManager(nullptr)
	, m_BulletManager(nullptr)
	, m_StageManager(nullptr)
{
}

void IUnit::Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, CStageManager* st_m , CBulletManager* bm)
{
	// 各種基礎情報の設定
	m_Position = pop_pos;
	m_Width = wid;
	m_Height = hei;
	m_Depth = dep;
	m_BulletManager = bm;
	m_StageManager = st_m;
	m_DeadFlag = false;
	m_Color = aqua::CColor::BLACK;
	m_Cube.Setup(m_Position, m_Width, m_Height, m_Depth, m_Color);
	aqua::CreateGameObject<CLifeBar>(this);
	// エフェクト管理クラスを探査してポインタを受け取る
	m_EffectManager = (CEffectManager*)aqua::FindGameObject("EffectManager");
	m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");
	// ビームによるダメージの間隔用タイマーのセットアップ
	m_BeamInterval.Setup(m_beam_damage_interval);

	m_Cube.visible = false;

	IGameObject::Initialize();
}

void IUnit::Draw(void)
{
	m_Cube.Draw();
	m_Model.Draw();
	IGameObject::Draw();
}

void IUnit::Finalize(void)
{
	m_Model.Unload();
	IGameObject::Finalize();
}

void IUnit::Update(void)
{
	Move();
	m_Cube.position = m_Position;

	IGameObject::Update();
}

bool IUnit::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere,int damage)
{
	// 弾の所属が自身と同じなら処理しない
	if (m_UnitType == type)
		return false;
	// キューブクラスのコリジョン関数で判定チェック
	if (m_Cube.CheckCollision(sphere.position, sphere.radius))
		// 当たったらダメージ
		Damage(damage);
	return m_Cube.collision;
}

bool IUnit::CheckHitBeam(UNIT_TYPE type, aqua::CCapsulePrimitive capsule, int damage)
{
	// ビームダメージ間隔用タイマーの更新
	m_BeamInterval.Update();
	// タイマーが終了していないまたビームの所属が自身と同じなら処理しない
	if (!m_BeamInterval.Finished()|| m_UnitType == type)
		return false;
	// キューブクラスのコリジョン関数で判定チェック
	if (m_Cube.CheckCollision(capsule.Apos,capsule.Bpos,capsule.radius))
	{
		// 当たったらダメージ
		Damage(damage);

		// 被弾エフェクト
		m_EffectManager->Create(EFFECT_ID::BEAM_HIT, m_Position, 0.0f, 8.0f);

		// タイマーをリセット
		m_BeamInterval.Reset();
	}
	return m_Cube.collision;
}

bool IUnit::GetDead(void)
{
	if (!this)
		return false;
	return m_DeadFlag;
}

void IUnit::Shot(void)
{
}

void IUnit::Move(void)
{
}

void IUnit::Damage(int damage)
{
	// ライフをダメージ数値分減算
	m_Life -= damage;


	// ライフが0以下になったら死亡処理を行う
	if (m_Life <= 0)
		Dead();
	else
		// 0以下でなければダメージSEを再生しない
		m_SoundManager->Play(SOUND_ID::s_DAMAGE);

}

void IUnit::Dead(void)
{
	m_DeadFlag = true;
	m_Cube.visible = false;

	// 死亡エフェクトを再生
	m_EffectManager->Create(EFFECT_ID::DEAD, m_Position);
	// SEを再生
	m_SoundManager->Play(SOUND_ID::s_DEAD);
}
