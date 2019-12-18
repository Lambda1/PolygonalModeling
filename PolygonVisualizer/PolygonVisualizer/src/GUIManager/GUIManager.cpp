#include "./GUIManager.hpp"

GUIManager::GUIManager():
	m_tool_window(nullptr)
{
	InitGUI();
}

GUIManager::~GUIManager()
{
	if (m_tool_window)
	{
		delete m_tool_window;
		m_tool_window = nullptr;
	}
}
// private
// GUI初期化
void GUIManager::InitGUI()
{
	m_tool_window = new ToolWindow;
	if (!m_tool_window)
	{
		std::cerr << "ERROR: TOOL WINDOW IS NULL." << std::endl;
		std::abort();
	}
}
// public
// 更新処理
void GUIManager::Update()
{
	// メニューバー処理
	m_menu_bar.Update();

	// ウィンドウ処理
	if (m_tool_window)
	{
		m_tool_window->Update();
	}
}