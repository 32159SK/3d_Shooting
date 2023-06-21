
#include "../game_object.h"
#include "csv_reader.h"


CCSVReader::
CCSVReader(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "CSVReader")
	, m_FileRow{ 0 }
	, m_FileType(FILE_TYPE::ENEMY_INFO)
	, m_Stage{ 0 }
{
}

/*
 *  @brief      初期化
 */
void
CCSVReader::
Initialize(FILE_TYPE file_type, std::string file_name)
{
	m_FileType = file_type;
	// CSVをパース
	CCSVReader::Parse("data\\csv\\" + file_name + ".csv");
}


/*
 *  @brief      解放
 */
void CCSVReader::Finalize(void)
{
	m_EnemyInfo.clear();
	m_BulletInfo.clear();
	m_PopList.clear();
}

/*
 *  @brief      データ読み込み
 */
void CCSVReader::Parse(const std::string& file_name)
{
	aqua::CCSVLoader csv;
	csv.Load(file_name);

	// ファイルの種類に合わせて行数を取得
	m_FileRow[(int)m_FileType] = csv.GetRows();

	ENEMY_INFO e_info;
	BULLET_INFO b_info;
	ENEMY_POP_LIST pop_list;
	switch (m_FileType)
	{
	case FILE_TYPE::ENEMY_INFO:
		for (int i = 0; i < m_FileRow[(int)m_FileType]; ++i)
		{
			e_info =
			{
				(ENEMY_ID)i,					// id
				std::stoi(csv.GetString(i,0)),	// life
				std::stof(csv.GetString(i,1)),	// width
				std::stof(csv.GetString(i,2)),	// height
				std::stof(csv.GetString(i,3)),	// depth
				std::stof(csv.GetString(i,4)),	// speed
				std::stof(csv.GetString(i,5)),	// shot_ct
				aqua::CColor::BLACK
			};
			m_EnemyInfo.push_back(e_info);
		}
		break;
	case FILE_TYPE::BULLET_INFO:
		for (int i = 0; i < m_FileRow[(int)m_FileType]; ++i)
		{
			b_info =
			{
				(BULLET_TYPE)i,
				std::stoi(csv.GetString(i,0)),	// damage
				std::stof(csv.GetString(i,1)),	// speed
				aqua::CColor::RED
			};
			m_BulletInfo.push_back(b_info);
		}
		break;
	case FILE_TYPE::POP_LIST:
		for (int i = 0; i < m_FileRow[(int)m_FileType]; ++i)
		{
			pop_list =
			{
				std::stoi(csv.GetString(i,0)),	// wave
				(ENEMY_ID)std::stoi(csv.GetString(i,1))		// e_id
			};
			m_PopList.push_back(pop_list);
		}
		break;
	case FILE_TYPE::STAGE:
		// 行
		for (int i = 0; i < 21; ++i)
			// 列
			for (int k = 0; k < 21; ++k)
				m_Stage[i][k] = std::stoi(csv.GetString(i, k));
		break;
	default:
		break;
	}

	csv.Unload();
}

