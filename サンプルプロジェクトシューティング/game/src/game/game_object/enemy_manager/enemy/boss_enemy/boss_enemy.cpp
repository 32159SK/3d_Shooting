#include "../../../game_object.h"
#include "boss_enemy.h"

const float CBossEnemy::m_summon_interval = 15.0f;
const std::string CBossEnemy::m_model_file_path = "data\\model\\boss_enemy_N.mv1";

CBossEnemy::CBossEnemy(aqua::IGameObject* parent)
	: CEnemy(parent)
{
}

void CBossEnemy::Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m, CBulletManager* bm)
{
	CEnemy::Initialize(pop_pos, wid, hei, dep, color, st_m, bm);
	m_Model.Load("data\\model\\fixed_enemy.mv1");
	m_Model.position = m_Position;
	m_ShotBullet = BULLET_TYPE::PENETRATE;
	m_Cube.visible = false;
	// 親(敵管理)クラスを取得
	m_EnemyManager = (CEnemyManager*)IGameObject::GetParent();

	m_SummonTimer.Setup(m_summon_interval);

	for (int i = 0; i < BOSS_PHASE::SECOND; i++)
		m_PhaseLife[i] = m_Life + m_Life / 2.0f * i;
}

void CBossEnemy::Update(void)
{
	IGameObject::Update();

	if (m_Player->GetTimeStop())
		return;


	m_ShotCT.Update();
	if (m_ShotCT.Finished())
	{
		Shot();
		m_ShotCT.Reset();
	}
	Move();

	m_Cube.m_HRotate = m_Rotate;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CBossEnemy::Draw(void)
{
	m_Model.Draw();
	CEnemy::Draw();
}

void CBossEnemy::Finalize(void)
{
	CEnemy::Finalize();
	m_Model.Unload();
}

bool CBossEnemy::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)
{
	return ;
}

void CBossEnemy::Shot(void)
{

	switch (m_Phase)
	{
	case CBossEnemy::FIRST:	m_ShotBullet = BULLET_TYPE::REFLECT;

		break;
	case CBossEnemy::SECOND:m_ShotBullet = BULLET_TYPE::BOSS;

		break;
		break;
	default:
		break;
	}


}

void CBossEnemy::Move(void)
{
	switch (m_Phase)
	{
	case CBossEnemy::FIRST: FirstPhase();	break;
	case CBossEnemy::SECOND:SecondPhase();	break;
	case CBossEnemy::DEAD:  Dead();			break;
	default:
		break;
	}

}

void CBossEnemy::Damage(int damage)
{
	m_PhaseLife[m_Phase] -= damage;

	// 形態ごとのライフが0以下なら形態移行
	if (m_PhaseLife[m_Phase] <= 0)
		PhaseChange();
}

void CBossEnemy::Dead(void)
{
	m_DeadTimer.Update();
	m_DeadFlag = true;
	m_Cube.visible = false;
	m_EffectManager->Create(EFFECT_ID::DEAD, m_Position);
	// 死亡演出用タイマー
	if (m_DeadTimer.Finished())
		DeleteObject();
}

void CBossEnemy::FirstPhase(void)
{
}

void CBossEnemy::SecondPhase(void)
{
	// タイマーの更新
	m_SummonTimer.Update();

	// 生成タイマーが終了
	if (m_SummonTimer.Finished())
		SummonEnemy();

	// プレイヤーと自身の距離
	aqua::CVector3 v = m_Player->GetPosition() - m_Position;

	// ベクトルのノーマライズ
	v.Normalize();

	// 2点から回転角度を求める
	m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));

}

void CBossEnemy::PhaseChange(void)
{
	// 自身の形態を次の形態へ変更
	m_Phase = (BOSS_PHASE)((int)m_Phase + 1);

	// モデルをアンロード
	m_Model.Unload();

	// 
	std::string model_path = m_model_file_path;

	model_path.replace(model_path.find("N"), 1, std::to_string((int)m_Phase + 1));

	m_Model.Load(model_path);

	m_Model.position = m_Position;
	m_Rotate = 0.0f;
}

void CBossEnemy::SummonEnemy(void)
{
	// 敵管理クラスの子の数が2未満(ボスしか生き残っていない)なら雑魚を召喚
	if (m_EnemyManager->GetChildList()->size() < 2)
	{
		m_EnemyManager->Create(m_FortPos[0], ENEMY_ID::MOB);
		m_EnemyManager->Create(m_FortPos[2], ENEMY_ID::MOB);
		m_SummonTimer.Reset();
	}
}
