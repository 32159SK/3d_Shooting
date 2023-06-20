
#include "../game_object.h"
#include "enemy_manager.h"
#include "enemy/mob_normal/mob_enemy.h"
#include "enemy/along_wall/along_wall.h"
#include "enemy/fixed_enemy/fixed_enemy.h"

const int CEnemyManager::m_max_wave = 2;

CEnemyManager::CEnemyManager(aqua::IGameObject* parent)
	: IGameObject(parent, "EnemyManager")
	, m_Player(nullptr)
	, m_BulletManagar(nullptr)
	, m_EnemyCount(0)
	, m_WaveCount(1)
	, m_Finish(false)
{
}

void CEnemyManager::Initialize(CCSVReader* csv_r, CBulletManager* bm, CPlayer* player, CStageManager* st_m, CRader* rader)
{
	m_CSVReader = csv_r;
	m_Player = player;
	m_BulletManagar = bm;
	m_StageManager = st_m;
	m_Rader = rader;

	m_CSVReader->Initialize(FILE_TYPE::POP_LIST, "pop_list");
	int row = m_CSVReader->GetFileRow(FILE_TYPE::POP_LIST);
	for (int i = 0; i < row; ++i)
		m_PopList.push_back(m_CSVReader->GetPopList(i));

	m_CSVReader->Initialize(FILE_TYPE::ENEMY_INFO, "enemy_info");
	row = m_CSVReader->GetFileRow(FILE_TYPE::ENEMY_INFO);
	for (int i = 0; i < row; ++i)
		m_EnemyInfo.push_back(m_CSVReader->GetEneInfo(i));

}

void CEnemyManager::Update(void)
{
	IGameObject::Update();


	if (m_ChildObjectList.empty())
		WaveChange();
}

void CEnemyManager::Draw(void)
{
	IGameObject::Draw();
}

void CEnemyManager::Create(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info)
{
	// ��̃G�l�~�[�N���X��p��
	CEnemy* enemy = nullptr;
	switch (enemy_info.id)
	{
	case ENEMY_ID::MOB:  enemy = aqua::CreateGameObject<CMobEnemy>(this); break;
	case ENEMY_ID::ALONG_WALL: enemy = aqua::CreateGameObject<CFixedEnemy>(this); break;
	case ENEMY_ID::FIXED: enemy = aqua::CreateGameObject<CFixedEnemy>(this); break;
	default:
		break;
	}

		

	// �������ƃv���C���[�̃|�C���^��n��
	enemy->Initialize(pop_pos, enemy_info.width, enemy_info.height, enemy_info.depth, enemy_info.color, m_StageManager, m_BulletManagar);
	enemy->SetPlayer(m_Player);
	m_EnemyCount++;

	// �e�Ƃ̏Փˊm�F�p�ɒe�Ǘ��N���X�ɐ��������G�l�~�[�̃|�C���^��n��
	m_BulletManagar->SetEnemy(enemy);
	m_Rader->SetEnemy(enemy);
}

void CEnemyManager::Finalize(void)
{
	IGameObject::Finalize();
}

CEnemy* CEnemyManager::GetNearest(aqua::CVector3 player_pos)
{
	if (m_ChildObjectList.empty())
		return nullptr;


	// �ł��߂��G
	CEnemy* nearestEnemy = nullptr;

	for (auto it : m_ChildObjectList)
	{
		CEnemy* enemy = (CEnemy*)it;

		// �ł��߂��G���܂��������Ă��Ȃ��ꍇ�A���ő������
		if (!nearestEnemy) nearestEnemy = enemy;

		// �G�ƃv���C���[�̋���
		float nearestDistance = abs(aqua::CVector3::Length(nearestEnemy->GetPosition() - player_pos));
		float itDistance = abs(aqua::CVector3::Length(enemy->GetPosition() - player_pos));

		// ���v���C���[�ɋ߂��G��nearestEnemy�ɂ���
		if (itDistance < nearestDistance) nearestEnemy = enemy;

		// �v���C���[�ƓG�̊Ԃɕǂ������null
		if (m_StageManager->StageObjectCollision(enemy->GetPosition(), player_pos, false))
			nearestEnemy = nullptr;

	}
	return nearestEnemy;
}
void CEnemyManager::WaveChange(void)
{
	if (m_WaveCount > m_max_wave)
	{
		m_Finish = true;
		return;
	}
	m_EnemyCount = 0;
	m_BulletManagar->EnemyReset();

	for (int i = 0; i < m_PopList.size(); ++i)
		if (m_PopList[i].wave == m_WaveCount)
			Create(m_PopList[i].pop_pos, m_EnemyInfo[(int)m_PopList[i].pop_e_id]);

	// wave�ɍ��킹�ăt�B�[���h��؂�ւ���
   	m_StageManager->WaveChange(m_WaveCount);
	m_WaveCount++;
}