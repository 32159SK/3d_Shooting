#pragma once

#include "aqua.h"
#include <vector>


/*!
 *  @brief      読み込むファイルの種類
 */
enum class FILE_TYPE
{
    ENEMY_INFO,
    BULLET_INFO,
    POP_LIST,
    STAGE
};

/*!
 *  @brief      エネミーの
 */
enum class ENEMY_TYPE
{
    NOMAL,
    TURRET,
};

/*!
 *  @brief      エネミーのポップテーブル
 */
struct ENEMY_POP_LIST
{
    int   wave  = 1;
    aqua::CVector3 pop_pos = aqua::CVector3::ZERO;
};

/*!
 *  @brief      エネミーの情報
 */
struct ENEMY_INFO
{
    int   life = 1;
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
    FAST,
    MINE,
    MAX
};

struct BULLET_INFO
{
    BULLET_TYPE bullet_type = BULLET_TYPE::NOMAL;
    int     damage = 1;
    float   radius = 5;
    float   speed = 2.0f;
    aqua::CColor color = aqua::CColor::RED;
};

/*!
 *  @class      CGame
 *
 *  @brief      CSVクラス
 *
 *  @author     Kazuto Shimazaki
 *
 *  @date       2023/05/08
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
    int                    GetFileRow(FILE_TYPE file_type) { return m_FileRow[(int)file_type]; }

    /*!
     *  @brief      解放
     */
    void                   Finalize(void)override;

    /*!
     *  @brief      エネミー情報取得
     */
    ENEMY_INFO             GetEneInfo(int i) { return m_EnemyInfo[i]; }

    /*!
     *  @brief      弾情報取得
     */
    BULLET_INFO            GetBullInfo(int i) { return m_BulletInfo[i]; }

    /*!
     *  @brief      ポップ情報取得
     */
    ENEMY_POP_LIST         GetPopList(int i) { return m_PopList[i]; }

    /*!
     *  @brief      ステージ配置取得
     */
    int                     GetStage(int i, int k) { return m_Stage[i][k]; }

private:

    //! CSVファイルのデータをトークデータリストに変換する
    void                   Parse(const std::string& file_name);

    int                            m_FileRow[4];

    FILE_TYPE                      m_FileType;

    std::vector<ENEMY_INFO>        m_EnemyInfo;

    std::vector<BULLET_INFO>       m_BulletInfo;

    std::vector<ENEMY_POP_LIST>    m_PopList;

    int                            m_Stage[10][10];    // ステージ配置
};
