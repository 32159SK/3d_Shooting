
#include "../game_object.h"
#include "csv_reader.h"


CCSVReader::
CCSVReader(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "CSVReader")
	, m_FileRow(0)
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
}

/*
 *  @brief      データ読み込み
 */
void CCSVReader::Parse(const std::string& file_name)
{
	aqua::CCSVLoader csv;
	csv.Load(file_name);

	csv.Unload();
}

