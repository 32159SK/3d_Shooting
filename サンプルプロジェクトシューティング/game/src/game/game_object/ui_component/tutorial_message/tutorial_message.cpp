#include "tutorial_message.h"

const float CTutorialMessage::m_pop_time = 1.0f;
const float CTutorialMessage::m_wait_time = 5.0f;
const float CTutorialMessage::m_background_panel_height = 50.0f;

CTutorialMessage::CTutorialMessage(aqua::IGameObject* parent)
	:IUIComponent(parent,"TutorialMassage")
{
}

void CTutorialMessage::Initialize(std::string text)
{
    // タイマーのセットアップ
    m_Timer.Setup(m_pop_time);

    // ラベルの生成
    m_Message.Create(20, 2);

    // 表示するテキストを代入
    m_Message.text = text;

    // 座標計算
    m_Message.position.x = ((float)aqua::GetWindowWidth() + (float)m_Message.GetTextWidth()) / 2.0f;
    m_Message.position.y = (float)aqua::GetWindowHeight() - m_background_panel_height;

    // 背景ウインドウパネルのセットアップ
    m_WindowPanel.Setup({ 0.0f,(float)aqua::GetWindowHeight() }, (float)aqua::GetWindowWidth(), m_background_panel_height, 0x80000000);

    // 状態をポップイン(入り)に
    m_State = STATE::POP_IN;

}

void CTutorialMessage::Update(void)
{
    // タイマーの更新
    m_Timer.Update();

    // 状態によって処理を分ける
    switch (m_State)
    {
    case STATE::POP_IN:        PopIn();        break;
    case STATE::WAIT:          Wait();         break;
    case STATE::POP_OUT:       PopOut();       break;
    case STATE::END:           DeleteObject(); break;
    default:
        break;
    }
}

void CTutorialMessage::Draw(void)
{
	// ウインドウとメッセージの描画
	m_WindowPanel.Draw();
	m_Message.Draw();
}

void CTutorialMessage::Finalize(void)
{
	m_Message.Delete();
}

void CTutorialMessage::PopIn(void)
{
    // パネルの始点と終点を決める
    float start = (float)aqua::GetWindowHeight();
    float end = (float)aqua::GetWindowHeight() - m_background_panel_height;

    // positionの仮変数
    float pos_y = aqua::easing::OutCubic(m_Timer.GetTime(), m_Timer.GetLimit(), start, end);

    // 計算した座標の代入
    m_WindowPanel.position.y = pos_y;
    m_Message.position.y = pos_y;

    // タイマー終了
    if (m_Timer.Finished())
    {
        // タイマーの再設定
        m_Timer.Setup(m_wait_time);
        // 状態の遷移
        m_State = STATE::WAIT;
    }
}

void CTutorialMessage::Wait(void)
{
    // タイマー終了
    if (m_Timer.Finished())
    {
        // タイマーの再設定
        m_Timer.Setup(m_pop_time);
        // 状態の遷移
        m_State = STATE::POP_OUT;
    }
}

void CTutorialMessage::PopOut(void)
{
    // パネルの始点と終点を決める
    float start = (float)aqua::GetWindowHeight() - m_background_panel_height;
    float end = (float)aqua::GetWindowHeight();

    // positionの仮変数
    float pos_y = aqua::easing::InCubic(m_Timer.GetTime(), m_Timer.GetLimit(), start, end);

    // 計算した座標の代入
    m_WindowPanel.position.y = pos_y;
    m_Message.position.y = pos_y;

    // タイマー終了で終わり
    if (m_Timer.Finished()) m_State = STATE::END;
}
