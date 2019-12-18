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
	// ���j���[�o�[����
	m_menu_bar.Update();

	// �E�B���h�E����
	if (m_tool_window)
	{
		m_tool_window->Update();
	}
}