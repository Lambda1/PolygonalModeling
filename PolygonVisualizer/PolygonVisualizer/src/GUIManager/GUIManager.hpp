#ifndef __GUI_MANAGER_HPP__
#define __GUI_MANAGER_HPP__

#include "../MenuBar/MenuBar.hpp"
#include "../GUIWindow/ToolWindow/ToolWindow.hpp"

#include <iostream>

class GUIManager
{
	// GUIˆ—•Ï”
	MenuBar m_menu_bar;
	GUIWindow *m_tool_window;

	// ‰Šú‰»ˆ—
	void InitGUI();
public:
	GUIManager();
	~GUIManager();

	// XV
	void Update();
};

#endif