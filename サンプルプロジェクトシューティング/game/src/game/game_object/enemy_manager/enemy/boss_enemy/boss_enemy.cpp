#include "../../../game_object.h"
#include "boss_cannon/boss_cannon.h"
#include "boss_enemy.h"

const float CBossEnemy::m_all_range_ct = 10.0f;
const float CBossEnemy::m_dead_time = 6.0f;
const float CBossEnemy::m_rotate_speed = 0.3f;
const int CBossEnemy::m_cannon_count[] = { 4,8 };
const int CBossEnemy::m_position_pattern = 45;
const int CBossEnemy::m_max_summon = 10;
const aqua::CVector3 CBossEnemy::m_base_cannon_pos[] =
{
	 aqua::CVector3(-40.0f,0.0f,0.0f)
	,aqua::CVector3(40.0f,0.0f,0.0f)
	,aqua::CVector3(0.0f,0.0f,40.0f)
	,aqua::CVector3(0.0f,0.0f,-40.0f)
	,aqua::CVector3(40.0f,0.0f,40.0f)
	,aqua::CVector3(40.0f,0.0f,-40.0f)
	,aqua::CVector3(-40.0f,0.0f,40.0f)
	,aqua::CVector3(-40.0f,0.0f,-40.0f)
};
const std::string CBossEnemy::m_model_file_path = "data\\model\\boss_enemy.mv1";


CBossEnemy::CBossEnemy(aqua::IGameObject* parent)
	: CEnemy(parent, "BossEnemy")
	, m_PhaseLife{ 0 }
	, m_SummonCount(0)
	, m_AllRangeAttacking(false)
	, m_Phase(BOSS_PHASE::FIRST)
	, m_CannonPos{ aqua::CVector3::ZERO }
	, m_Cannon{ nullptr }
	, m_EnemyManager(nullptr)
{
}

void CBossEnemy::
Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)
{
	m_Model.Load("data\\model\\boss_enemy.mv1");
	m_ShotBullet = BULLET_TYPE::PENETRATE;

	CEnemy::Initialize(pop_pos, enemy_info, st_m, bm);
	// 親(敵管理)クラスを取得
	m_EnemyManager = (CEnemyManager*)IGameObject::GetParent();

	// ゲームメインシーンを探査
	m_GameMain = (CGameMain*)aqua::FindGameObject("GameMainScene");

	// AR攻撃CT計測タイマーのセット
	m_AllRangeCT.Setup(m_all_range_ct);

	// 死亡タイマーのセット
	m_DeadTimer.Setup(m_dead_time);


	for (int i = 0; i < BOSS_PHASE::DEAD; i++)
		m_PhaseLife[i] = m_Life + m_Life * (i + 1);

	CannonSetUp();
}

void CBossEnemy::Update(void)
{
	// 
	m_Life = m_PhaseLife[m_Phase];

	IGameObject::Update();

	if (m_DeadFlag || !m_MoveFlag)
		return;

	Move();

	Shot();
}


void CBossEnemy::SetCannonPosition(void)
{
	// 自身がnull・形態が死のいずれかであれば処理しない
	if (!this||m_Phase == BOSS_PHASE::DEAD)
		return;

	for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
		if (m_Cannon[i] && !m_Cannon[i]->GetDead())
			m_Cannon[i]->SetPosition(m_CannonPos[i]);
}

void CBossEnemy::Shot(void)
{
	// 射撃タイマーの更新
	m_ShotCT.Update();

	// CTが開けていれば砲撃をさせる
	if (m_ShotCT.Finished())
	{
		switch (m_Phase)
		{
		case CBossEnemy::FIRST:
			m_ShotBullet = BULLET_TYPE::BEAM;
			// ランダムで撃つ弾を切り替える
			m_ShotBullet = (BULLET_TYPE)aqua::Rand((int)m_ShotBullet);
			break;
		case CBossEnemy::SECOND:m_ShotBullet = BULLET_TYPE::PENETRATE; break;
		}
		for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
			if (m_Cannon[i] && !m_Cannon[i]->GetDead() && m_Cannon[i]->GetFinish())
			{
				m_Cannon[i]->SetBulletType(m_ShotBullet);
				m_Cannon[i]->Shot();
			}
		m_ShotCT.Reset();
	}
}

void CBossEnemy::Move(void)
{
	if (m_DeadFlag && m_Phase != BOSS_PHASE::DEAD)
		return;
	// ボスの形態に合わせた処理
	switch (m_Phase)
	{
	case CBossEnemy::FIRST: FirstPhase();	break;
	case CBossEnemy::SECOND:SecondPhase();	break;
	case CBossEnemy::DEAD:  Dead();			break;
	}
}

void CBossEnemy::Damage(int damage)
{
	m_PhaseLife[m_Phase] -= damage;

	// 形態ごとのライフが0以下なら形態移行
	if (m_PhaseLife[m_Phase] <= 0)
		PhaseChange();
	else
		m_SoundManager->Play(SOUND_ID::s_DAMAGE);
}

void CBossEnemy::Dead(void)
{
	// ここを通るのは最初のみ
	if (!m_DeadFlag)
	{
		m_DeadFlag = true;
		// 死亡演出
		m_EffectManager->Create(EFFECT_ID::BOSS_DEAD, m_Position);
		// SEを再生
		m_SoundManager->Play(SOUND_ID::s_BOSS_DEAD);
		m_GameMain->SetGameClear(true);
	}
	
	// 死亡タイマーの更新
	m_DeadTimer.Update();

	if (m_DeadTimer.Finished())
		DeleteObject();
}

void CBossEnemy::FirstPhase(void)
{
	// プレイヤーと自身の距離
	aqua::CVector3 v = m_Player->GetPosition() - m_Position;

	// ベクトルのノーマライズ
	v.Normalize();

	// 2点から回転角度を求める
	m_Cube.m_HRotate = aqua::RadToDeg(atan2(v.x, v.z));


	// 行列を使って始点を中心とした回転処理を行い砲の座標を決める
	aqua::CMatrix mat;
	mat.RotationY(aqua::DegToRad(m_Cube.m_HRotate));
	mat.Translate(m_Position);
	for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
		m_CannonPos[i] = -m_base_cannon_pos[i] * mat;
	SetCannonPosition();
}

void CBossEnemy::SecondPhase(void)
{

	aqua::CMatrix mat;
	mat.RotationY(aqua::DegToRad(m_Rotate));
	mat.Translate(m_Position);

	for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
		m_CannonPos[i] = -m_base_cannon_pos[i] * mat;

	SetCannonPosition();

	m_Rotate += m_rotate_speed;
	// オールレンジ攻撃をしていないなら以下の処理を
	if (!m_AllRangeAttacking)
	{
		// 
		m_AllRangeCT.Update();


		for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
		{
			// 砲が生きているなら座標と弾種を代入し直す
			if (m_Cannon[i] && !m_Cannon[i]->GetDead())
				m_Cannon[i]->SetBulletType(m_ShotBullet);
		}
		// CTが終了していたらオールレンジ攻撃を行う
		if (m_AllRangeCT.Finished())
			AllRangeAttack();
	}
	else
	{
		for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
			// 帰るタイミングはどれも一律で同じなのでどれか一つでも終えていればオールレンジ攻撃の終了
			if (m_Cannon[i] && !m_Cannon[i]->GetDead() && i <= 3)
				if (m_Cannon[i]->GetFinish())
					m_AllRangeAttacking = false;
	}




}

void CBossEnemy::PhaseChange(void)
{
	// 状態が死亡ならこれ以上遷移させる必要はない
	if (m_Phase == BOSS_PHASE::DEAD)
		return;
	// 自身の形態を次の形態へ変更
	m_Phase = (BOSS_PHASE)((int)m_Phase + 1);

	if (m_Phase != BOSS_PHASE::DEAD)
		CannonSetUp();
}

void CBossEnemy::CannonSetUp(void)
{
	// 砲の再生成・追加と弾種の変更
	for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
	{
		if (m_Cannon[i])
			m_Cannon[i]->Dead();
		m_Cannon[i] = (CBossCannon*)m_EnemyManager->CreateBossParts(m_base_cannon_pos[i], ENEMY_ID::BOSS_CANNON);
		m_Cannon[i]->SetBulletType(m_ShotBullet);
		m_Cannon[i]->SetBossEnemy(this);
		m_Cannon[i]->SetCannonNumber(i);
		m_CannonPos[i] = m_Position + m_base_cannon_pos[i];
	}
}

void CBossEnemy::AllRangeAttack(void)
{
	m_AllRangeAttacking = true;
	// この時点でタイマーをリセット(この関数を再度呼ぶのを防ぐ目的、ARA中はタイマーの更新がかからないのでCTも問題はない)
	m_AllRangeCT.Reset();

	float shot_angle[8] = { 0.0f };

	for (;;)
	{
		for (int i = 0; i < m_cannon_count[0]; ++i)
			// 乱数で角度を取る
			shot_angle[i] = (float)aqua::Rand(m_cannon_count[m_Phase]);

		// 角度がどれも被ってないか確認する
		if (shot_angle[0] != shot_angle[1] && shot_angle[0] != shot_angle[2] && shot_angle[0] != shot_angle[3] &&
			shot_angle[1] != shot_angle[2] && shot_angle[1] != shot_angle[3] && shot_angle[2] != shot_angle[3])
			break;
	}


	// 生きている"半分"の砲にオールレンジ攻撃をさせる
	for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
		if (m_Cannon[i] && !m_Cannon[i]->GetDead() && i<= 3)
		{
			m_Cannon[i]->SetBulletType(BULLET_TYPE::BEAM);
			m_Cannon[i]->SetAllRange(shot_angle[i]);
		}

}
