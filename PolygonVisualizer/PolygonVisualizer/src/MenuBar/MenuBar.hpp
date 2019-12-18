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
	// ���j���[�e�[�u��
	std::vector<void(MenuBar::*)()> m_menu_table;

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
};

#endif