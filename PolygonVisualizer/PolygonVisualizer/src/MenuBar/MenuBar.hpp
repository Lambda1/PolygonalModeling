#ifndef __MENU_BAR_HPP__
#define __MENU_BAR_HPP__

#include "./MenuBarDefine.hpp"

#include "../imgui/imgui.h"

#include <iostream>
#include <vector>
#include <functional>
#include <map>

using namespace MENU_BAR_DEFINE;

class MenuBar
{
	// メニューテーブル
	std::vector<void(MenuBar::*)()> m_menu_table;

	// 初期化処理
	void InitTable();

	// メニュー処理
	void OpenModelFile();
	void SaveModelFile();

	// ファイルメニュー
	void FileMenu();
public:
	MenuBar();
	~MenuBar();

	// 更新処理
	void Update();
};

#endif