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
	, m_PhaseMaxLife{ 0 }
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
	IGameObject::m_GameObjectName = "BossEnemy";

	// ���C�t�o�[�̐���
	m_LifeBar = aqua::CreateGameObject<CUniqueLifeBar>(this);

	// ���f���̃��[�h
	m_Model.Load("data\\model\\boss_enemy.mv1");

	// ���e��̐ݒ�
	m_ShotBullet = BULLET_TYPE::PENETRATE;

	// ��{�I�ȃ��j�b�g�̏����������N���X�̏��������Ăяo���čs��
	CEnemy::Initialize(pop_pos, enemy_info, st_m, bm);
	// �e(�G�Ǘ�)�N���X���擾
	m_EnemyManager = (CEnemyManager*)IGameObject::GetParent();

	// �Q�[�����C���V�[����T��
	m_GameMain = (CGameMain*)aqua::FindGameObject("GameMainScene");

	// AR�U��CT�v���^�C�}�[�̃Z�b�g
	m_AllRangeCT.Setup(m_all_range_ct);

	// ���S�^�C�}�[�̃Z�b�g
	m_DeadTimer.Setup(m_dead_time);

	// �`�Ԃ��ƂɃ��C�t��ݒ�
	for (int i = 0; i < BOSS_PHASE::DEAD; i++)
	{
		m_PhaseMaxLife[i] = m_Life + m_Life * (i + 1);
		m_PhaseLife[i] = m_PhaseMaxLife[i];
	}

	// �C�̔z�u
	CannonSetUp();

	// �X�V
	Update();
}

void CBossEnemy::Update(void)
{
	IGameObject::Update();

	if (m_DeadFlag || !m_MoveFlag)
		return;

	Move();

	Shot();
}


void CBossEnemy::SetCannonPosition(float rotate)
{
	// ���g��null�E�`�Ԃ����̂����ꂩ�ł���Ώ������Ȃ�
	if (!this||m_Phase == BOSS_PHASE::DEAD)
		return;

	// �s����g���ă{�X�̍��W�𒆐S�Ƃ�����]�������s���C�̍��W�����߂�
	aqua::CMatrix mat;
	mat.RotationY(aqua::DegToRad(rotate));
	mat.Translate(m_Position);
	for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
		m_CannonPos[i] = -m_base_cannon_pos[i] * mat;

	for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
		if (m_Cannon[i] && !m_Cannon[i]->GetDead())
			m_Cannon[i]->SetPosition(m_CannonPos[i]);
}

void CBossEnemy::Shot(void)
{
	// �ˌ��^�C�}�[�̍X�V
	m_ShotCT.Update();

	// CT���J���Ă���ΖC����������
	if (m_ShotCT.Finished())
	{
		switch (m_Phase)
		{
		case CBossEnemy::FIRST:
			m_ShotBullet = BULLET_TYPE::BEAM;
			// �����_���Ō��e��؂�ւ���
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
	// �{�X�̌`�Ԃɍ��킹������
	switch (m_Phase)
	{
	case CBossEnemy::FIRST: FirstPhase();	break;
	case CBossEnemy::SECOND:SecondPhase();	break;
	case CBossEnemy::DEAD:  Dead();			break;
	}
}

void CBossEnemy::Damage(int damage)
{
	// �`�Ԃ��Ƃ̃��C�t�����炷
	m_PhaseLife[m_Phase] -= damage;

	// �`�Ԃ��Ƃ̃��C�t��0�ȉ��Ȃ�`�Ԉڍs
	if (m_PhaseLife[m_Phase] <= 0)
		PhaseChange();
	else
	{
		m_SoundManager->Play(SOUND_ID::s_DAMAGE);
		// ���C�t�o�[�̌v�Z����
		m_LifeBar->CalcLifeBar();
	}
}

void CBossEnemy::Dead(void)
{
	// ������ʂ�͍̂ŏ��̂�
	if (!m_DeadFlag)
	{
		m_DeadFlag = true;
		// ���S���o
		m_EffectManager->Create(EFFECT_ID::BOSS_DEAD, m_Position);
		// SE���Đ�
		m_SoundManager->Play(SOUND_ID::s_BOSS_DEAD);
		m_GameMain->SetGameClear(true);
	}
	
	// ���S�^�C�}�[�̍X�V
	m_DeadTimer.Update();

	if (m_DeadTimer.Finished())
		DeleteObject();
}

void CBossEnemy::FirstPhase(void)
{
	// �v���C���[�Ǝ��g�̋���
	aqua::CVector3 v = m_Player->GetPosition() - m_Position;

	// �x�N�g���̃m�[�}���C�Y
	v.Normalize();

	// 2�_�����]�p�x�����߂�
	m_Cube.m_HRotate = aqua::RadToDeg(atan2(v.x, v.z));

	// �C�G�l�~�[�̍��W�Z�b�g
	SetCannonPosition(m_Cube.m_HRotate);
}

void CBossEnemy::SecondPhase(void)
{
	// �C�G�l�~�[�̍��W�Z�b�g
	SetCannonPosition(m_Rotate);

	m_Rotate += m_rotate_speed;

	m_Model.rotation.y = aqua::DegToRad(m_Rotate*2.0f);

	// �I�[�������W�U�������Ă��Ȃ��Ȃ�ȉ��̏�����
	if (!m_AllRangeAttacking)
	{
		// 
		m_AllRangeCT.Update();


		for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
		{
			// �C�������Ă���Ȃ���W�ƒe�����������
			if (m_Cannon[i] && !m_Cannon[i]->GetDead())
				m_Cannon[i]->SetBulletType(m_ShotBullet);
		}
		// CT���I�����Ă�����I�[�������W�U�����s��
		if (m_AllRangeCT.Finished())
			AllRangeAttack();
	}
	else
	{
		for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
			// �A��^�C�~���O�͂ǂ���ꗥ�œ����Ȃ̂łǂꂩ��ł��I���Ă���΃I�[�������W�U���̏I��
			if (m_Cannon[i] && !m_Cannon[i]->GetDead() && i <= 3)
				if (m_Cannon[i]->GetFinish())
					m_AllRangeAttacking = false;
	}

}

void CBossEnemy::PhaseChange(void)
{
	// ��Ԃ����S�Ȃ炱��ȏ�J�ڂ�����K�v�͂Ȃ�
	if (m_Phase == BOSS_PHASE::DEAD)
		return;
	// ���g�̌`�Ԃ����̌`�Ԃ֕ύX
	m_Phase = (BOSS_PHASE)((int)m_Phase + 1);

	// ����ł��Ȃ��Ȃ�ȉ��̏�����
	if (m_Phase != BOSS_PHASE::DEAD)
	{
		// �ˌ�CT��{��
		m_ShotCT.SetLimit(m_ShotCT.GetLimit() * 2.0f);

		// ���C�t�o�[�̌v�Z����
		m_LifeBar->CalcLifeBar();

		// �C�̍Đݒu
		CannonSetUp();
	}
}

void CBossEnemy::CannonSetUp(void)
{
	// �C�̍Đ����E�ǉ��ƒe��̕ύX
	for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
	{
		// �������݂Ȃ�E��
		if (m_Cannon[i])
			m_Cannon[i]->Dead();
		// �G�Ǘ��N���X�Ő��������A�|�C���^���󂯎��
		m_Cannon[i] = (CBossCannon*)m_EnemyManager->CreateBossParts(m_base_cannon_pos[i], ENEMY_ID::BOSS_CANNON);
		// ���g�̎ˌ����s�����邽�߂�
		m_Cannon[i]->SetBulletType(m_ShotBullet);
		m_Cannon[i]->SetBossEnemy(this);
		m_Cannon[i]->SetCannonNumber(i);
		m_CannonPos[i] = m_Position + m_base_cannon_pos[i];
	}
}

void CBossEnemy::AllRangeAttack(void)
{
	m_AllRangeAttacking = true;
	// ���̎��_�Ń^�C�}�[�����Z�b�g(���̊֐����ēx�ĂԂ̂�h���ړI�AARA���̓^�C�}�[�̍X�V��������Ȃ��̂�CT�����͂Ȃ�)
	m_AllRangeCT.Reset();

	float shot_angle[4] = { 0.0f };

	for (;;)
	{
		for (int i = 0; i < m_cannon_count[0]; ++i)
			// �����Ŋp�x�����
			shot_angle[i] = (float)aqua::Rand(m_cannon_count[m_Phase]);

		// �p�x���ǂ������ĂȂ����m�F����
		if (shot_angle[0] != shot_angle[1] && shot_angle[0] != shot_angle[2] && shot_angle[0] != shot_angle[3] &&
			shot_angle[1] != shot_angle[2] && shot_angle[1] != shot_angle[3] && shot_angle[2] != shot_angle[3])
			break;
	}


	// "����"�̖C�ɃI�[�������W�U����������
	for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
		if (m_Cannon[i] && !m_Cannon[i]->GetDead() && i<= 3)
		{
			m_Cannon[i]->SetBulletType(BULLET_TYPE::BEAM);
			m_Cannon[i]->SetAllRange(shot_angle[i]);
		}

}
