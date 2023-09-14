
#pragma once

#include "..\ui_component.h"

/*!
 *  @class      CTutorialMessage
 *
 *  @brief      チュートリアルメッセージ描画クラス
 *
 *  @author     Kazuto Shimazaki
 *
 *  @date
 *
 *  @version    1.0
 */
class CTutorialMessage
    : public IUIComponent
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親のオブジェクト
     */
    CTutorialMessage(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CTutorialMessage(void) = default;

    /*!
     *  @brief      初期化
     */
    void        Initialize(std::string text);

    /*!
     *  @brief      更新
     */
    void        Update(void) override;

    /*!
     *  @brief      描画
     */
    void        Draw(void) override;

    /*!
     *  @brief      解放
     */
    void        Finalize(void) override;

private:
    /*!
     *  @brief      出る
     */
    void        PopIn(void);

    /*!
     *  @brief      待機
     */
    void        Wait(void);

    /*!
     *  @brief      消える
     */
    void        PopOut(void);


    enum class STATE
    {
        POP_IN,     // 出る
        WAIT,       // 待機
        POP_OUT,    // 消える
        END         // 終了
    };

    static const float      m_pop_time;                 // 出るのにかける時間
    static const float      m_wait_time;                // 待機時間
    static const float      m_background_panel_height;  // パネルの高さ

    aqua::CTimer            m_Timer;                    // タイマー
    aqua::CBoxPrimitive     m_WindowPanel;              // パネル
    aqua::CLabel            m_FunctionName;             // 機能名
    aqua::CLabel            m_Message;                  // テキストクラス
    STATE                   m_State;                    // 状態
};
