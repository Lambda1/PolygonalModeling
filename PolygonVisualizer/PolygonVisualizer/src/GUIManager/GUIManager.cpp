#include "./GUIManager.hpp"

GUIManager::GUIManager():
	m_tool_window(nullptr),
	m_gui_flags(GUI_MANAGER_DEFINE::FLAGS::NONE)
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
// GUI������
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
// �X�V����
void GUIManager::Update()
{
	// �t���O�N���A
	m_gui_flags = GUI_MANAGER_DEFINE::FLAGS::NONE;

	// ���j���[�o�[�X�V����
	m_menu_bar.Update();
	// �E�B���h�E�X�V����
	if (m_tool_window) { m_tool_window->Update(); }

	// �eGUI�̏���
	ProcessMenuBar();

	if (m_gui_flags != GUI_MANAGER_DEFINE::FLAGS::NONE)
		std::cout << (int)m_gui_flags << std::endl;
}
// ���j���[�o�[����
void GUIManager::ProcessMenuBar()
{
	MenuBar::MENU_FLAGS flags = m_menu_bar.GetMenuFlag();
	if ((flags & MenuBar::MENU_FLAGS::OPEN_FILE) == MenuBar::MENU_FLAGS::OPEN_FILE)
	{
		m_file_name = m_menu_bar.GetOpenFile();
		m_gui_flags |= GUI_MANAGER_DEFINE::FLAGS::OPEN_FILE;
	}
	else if ((flags & MenuBar::MENU_FLAGS::SAVE_FILE) == MenuBar::MENU_FLAGS::SAVE_FILE)
	{
		m_file_name = m_menu_bar.GetSaveFile();
		m_gui_flags |= GUI_MANAGER_DEFINE::FLAGS::SAVE_FILE;
	}
}