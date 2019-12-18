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
	// 1�I�N�e�b�g�ł���Ɖ���
	using FLAG_TYPE = unsigned char;
	// �������̂���, ���������ӏ��̓t���O�Ǘ�.
	enum class MENU_FLAGS : FLAG_TYPE
	{
		NONE      = 0b00000000,
		OPEN_FILE = 0b00000001,
		SAVE_FILE = 0b00000010,
	};
private:
	// ���j���[�t���O
	MENU_FLAGS m_menu_flag;
	// ���j���[�e�[�u��
	std::vector<void(MenuBar::*)()> m_menu_table;
	// �I���t�@�C��
	std::string m_open_file, m_save_file;

	// ����������
	void InitTable();

	// ���j���[����
	void OpenModelFile();
	void SaveModelFile();

	// �t�@�C�����j���[
	void FileMenu();
public:
	MenuBar();
	~MenuBar();

	// �X�V����
	void Update();

	// Getter
	// Update���ŏ��������ӏ��̃t���O��Ԃ�
	inline MENU_FLAGS GetMenuFlag() const { return m_menu_flag; }
};

constexpr MenuBar::MENU_FLAGS operator|(const MenuBar::MENU_FLAGS& lhs, const MenuBar::MENU_FLAGS& rhs)
{
	return static_cast<MenuBar::MENU_FLAGS>(static_cast<MenuBar::FLAG_TYPE>(lhs) | static_cast<MenuBar::FLAG_TYPE>(rhs));
}
constexpr void operator|=(MenuBar::MENU_FLAGS &lhs, const MenuBar::MENU_FLAGS &rhs) { lhs = lhs | rhs; }

#endif