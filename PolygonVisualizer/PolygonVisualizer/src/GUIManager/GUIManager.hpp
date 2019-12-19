#ifndef __GUI_MANAGER_HPP__
#define __GUI_MANAGER_HPP__

#include "./GUIManagerDefine.hpp"

#include "../MenuBar/MenuBar.hpp"
#include "../GUIWindow/ToolWindow/ToolWindow.hpp"

#include <iostream>
#include <string>

class GUIManager
{
	// GUI処理変数
	MenuBar m_menu_bar;
	GUIWindow *m_tool_window;
	// ファイル処理
	std::string m_file_name; // OpenとSaveで共用
	// 処理フラグ
	GUI_MANAGER_DEFINE::FLAGS m_gui_flags;

	// 初期化処理
	void InitGUI();

	// メニューバー処理
	void ProcessMenuBar();
public:
	GUIManager();
	~GUIManager();

	// 更新
	void Update();

	// Getter
	// GUI Managerフラグ
	inline GUI_MANAGER_DEFINE::FLAGS GetGUIFlags() const { return m_gui_flags; }
	// ファイルネーム
	inline std::string GetFileName() const { return m_file_name; }
};

#endif