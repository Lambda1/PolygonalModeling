#ifndef __MENU_BAR_HPP__
#define __MENU_BAR_HPP__

#include "./MenuBarDefine.hpp"
#include "../MyWinAPI/WinFiler/WinFiler.hpp"

#include "../imgui/imgui.h"

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>

using namespace MENU_BAR_DEFINE;

class MenuBar
{
public:
	// 1オクテットであると仮定
	using FLAG_TYPE = unsigned char;
	// 高速化のため, 処理した箇所はフラグ管理.
	enum class MENU_FLAGS : FLAG_TYPE
	{
		NONE      = 0b00000000,
		OPEN_FILE = 0b00000001,
		SAVE_FILE = 0b00000010,
	};
private:
	// メニューフラグ
	MENU_FLAGS m_menu_flag;
	// メニューテーブル
	std::vector<void(MenuBar::*)()> m_menu_table;
	// 選択ファイル
	std::string m_open_file, m_save_file;

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

	// Getter
	// Update内で処理した箇所のフラグを返す
	inline MENU_FLAGS GetMenuFlag() const { return m_menu_flag; }
};

constexpr MenuBar::MENU_FLAGS operator|(const MenuBar::MENU_FLAGS& lhs, const MenuBar::MENU_FLAGS& rhs)
{
	return static_cast<MenuBar::MENU_FLAGS>(static_cast<MenuBar::FLAG_TYPE>(lhs) | static_cast<MenuBar::FLAG_TYPE>(rhs));
}
constexpr void operator|=(MenuBar::MENU_FLAGS &lhs, const MenuBar::MENU_FLAGS &rhs) { lhs = lhs | rhs; }

#endif