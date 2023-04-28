#pragma once

#include "aqua.h"
#include <vector>


/*!
 *  @brief      読み込むファイルの種類
 */
enum class FILE_TYPE
{
    ENEMY_INFO,
    POP_LIST,
};

/*!
 *  @brief      エネミーのポップテーブル
 */
struct ENEMY_POP_LIST
{
    float pop_time = 0.0f;
    float pos_x = 0.0f;
    float pos_z = 0.0f;
};

/*!
 *  @brief      エネミーの情報
 */
struct ENEMY_INFO
{
    int   life = 3;
    float width = 5.0f;
    float height = 5.0f;
    float depth = 5.0f;
    float speed = 1.0f;
    float shot_ct = 1.5f;
    aqua::CColor color = aqua::CColor::BLACK;
};

enum class BULLET_TYPE
{
    NOMAL,
    MAX
};

struct BULLET_INFO
{
    int     damage = 1;
    float   radius = 5;
    float   speed = 2.0f;
    aqua::CColor color = aqua::CColor::RED;
    BULLET_TYPE bullet_type = BULLET_TYPE::NOMAL;
};

/*!
 *  @class      CGame
 *
 *  @brief      CSVクラス
 *
 *  @author     Kazuto Shimazaki
 *
 *  @date       2023/04/27
 *
 *  @version    1.0
 */
class CCSVReader
    : public aqua::IGameObject
{
public:

    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親オブジェクト
     */
    CCSVReader(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CCSVReader(void) = default;

    /*!
     *  @brief      初期化
     */
    void                   Initialize(FILE_TYPE file_type, std::string file_name);

    /*!
     *  @brief      ファイル行数取得
     */
    int                    GetFileRow(void) { return m_FileRow; }

    /*!
     *  @brief      解放
     */
    void                   Finalize(void)override;
private:

    //! CSVファイルのデータをトークデータリストに変換する
    void Parse(const std::string& file_name);


    int                         m_FileRow;

    FILE_TYPE                   m_FileType;

};
