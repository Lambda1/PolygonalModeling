#ifndef __GUI_MANAGER_HPP__
#define __GUI_MANAGER_HPP__

#include "../MenuBar/MenuBar.hpp"
#include "../GUIWindow/ToolWindow/ToolWindow.hpp"

#include <iostream>

class GUIManager
{
	// GUI処理変数
	MenuBar m_menu_bar;
	GUIWindow *m_tool_window;

	// 初期化処理
	void InitGUI();
public:
	GUIManager();
	~GUIManager();

	// 更新
	void Update();
};

#endif