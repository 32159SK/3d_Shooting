#pragma once

#include "aqua.h"
#include <vector>


/*!
 *  @brief      �ǂݍ��ރt�@�C���̎��
 */
enum class FILE_TYPE
{
    ENEMY_INFO,
    BULLET_INFO,
    POP_LIST,
    STAGE
};

/*!
 *  @brief      �G�l�~�[��
 */
enum class ENEMY_TYPE
{
    NOMAL,
    TURRET,
};

/*!
 *  @brief      �G�l�~�[�̃|�b�v�e�[�u��
 */
struct ENEMY_POP_LIST
{
    int   wave  = 1;
    aqua::CVector3 pop_pos = aqua::CVector3::ZERO;
};

/*!
 *  @brief      �G�l�~�[�̏��
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
 *  @brief      CSV�N���X
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
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent  �e�I�u�W�F�N�g
     */
    CCSVReader(aqua::IGameObject* parent);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CCSVReader(void) = default;

    /*!
     *  @brief      ������
     */
    void                   Initialize(FILE_TYPE file_type, std::string file_name);

    /*!
     *  @brief      �t�@�C���s���擾
     */
    int                    GetFileRow(FILE_TYPE file_type) { return m_FileRow[(int)file_type]; }

    /*!
     *  @brief      ���
     */
    void                   Finalize(void)override;

    /*!
     *  @brief      �G�l�~�[���擾
     */
    ENEMY_INFO             GetEneInfo(int i) { return m_EnemyInfo[i]; }

    /*!
     *  @brief      �e���擾
     */
    BULLET_INFO            GetBullInfo(int i) { return m_BulletInfo[i]; }

    /*!
     *  @brief      �|�b�v���擾
     */
    ENEMY_POP_LIST         GetPopList(int i) { return m_PopList[i]; }

    /*!
     *  @brief      �X�e�[�W�z�u�擾
     */
    int                     GetStage(int i, int k) { return m_Stage[i][k]; }

private:

    //! CSV�t�@�C���̃f�[�^���g�[�N�f�[�^���X�g�ɕϊ�����
    void                   Parse(const std::string& file_name);

    int                            m_FileRow[4];

    FILE_TYPE                      m_FileType;

    std::vector<ENEMY_INFO>        m_EnemyInfo;

    std::vector<BULLET_INFO>       m_BulletInfo;

    std::vector<ENEMY_POP_LIST>    m_PopList;

    int                            m_Stage[10][10];    // �X�e�[�W�z�u
};
