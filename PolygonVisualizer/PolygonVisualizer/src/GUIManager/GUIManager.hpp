#ifndef __GUI_MANAGER_HPP__
#define __GUI_MANAGER_HPP__

#include "./GUIManagerDefine.hpp"

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
	// �����t���O
	GUI_MANAGER_DEFINE::FLAGS m_gui_flags;

	// ����������
	void InitGUI();

	// ���j���[�o�[����
	void ProcessMenuBar();
public:
	GUIManager();
	~GUIManager();

	// �X�V
	void Update();

	// Getter
	// GUI Manager�t���O
	inline GUI_MANAGER_DEFINE::FLAGS GetGUIFlags() const { return m_gui_flags; }
	// �t�@�C���l�[��
	inline std::string GetFileName() const { return m_file_name; }
};

#endif