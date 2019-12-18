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
	// メニューバー更新処理
	m_menu_bar.Update();
	// ウィンドウ更新処理
	if (m_tool_window) { m_tool_window->Update(); }

	// 各GUIの処理
	ProcessMenuBar();
}
// メニューバー処理
void GUIManager::ProcessMenuBar()
{
	MenuBar::MENU_FLAGS flags = m_menu_bar.GetMenuFlag();
	if (flags == MenuBar::MENU_FLAGS::OPEN_FILE)
	{
		//m_file_name = ;
	}
}