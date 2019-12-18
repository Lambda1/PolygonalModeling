#ifndef __GUI_MANAGER_HPP__
#define __GUI_MANAGER_HPP__

#include "../MenuBar/MenuBar.hpp"
#include "../GUIWindow/ToolWindow/ToolWindow.hpp"

#include <iostream>
#include <string>

class GUIManager
{
	// GUI�����ϐ�
	MenuBar m_menu_bar;
	GUIWindow *m_tool_window;
	// �t�@�C������
	std::string m_file_name; // Open��Save�ŋ��p

	// ����������
	void InitGUI();

	// ���j���[�o�[����
	void ProcessMenuBar();
public:
	GUIManager();
	~GUIManager();

	// �X�V
	void Update();
};

#endif