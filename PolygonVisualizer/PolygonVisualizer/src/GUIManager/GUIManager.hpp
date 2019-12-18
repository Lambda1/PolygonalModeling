#ifndef __GUI_MANAGER_HPP__
#define __GUI_MANAGER_HPP__

#include "../MenuBar/MenuBar.hpp"
#include "../GUIWindow/ToolWindow/ToolWindow.hpp"

#include <iostream>

class GUIManager
{
	// GUI�����ϐ�
	MenuBar m_menu_bar;
	GUIWindow *m_tool_window;

	// ����������
	void InitGUI();
public:
	GUIManager();
	~GUIManager();

	// �X�V
	void Update();
};

#endif