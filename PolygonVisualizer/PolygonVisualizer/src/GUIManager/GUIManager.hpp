#ifndef __GUI_MANAGER_HPP__
#define __GUI_MANAGER_HPP__

#include "./GUIManagerDefine.hpp"
#include "../MenuBar/MenuBar.hpp"
#include "../GUIWindow/ToolWindow/ToolWindow.hpp"
#include "../MyModel/MyModel.hpp"
#include "../MainCamera/MainCameraGL.hpp"

#include <iostream>
#include <string>

class GUIManager
{
	// GUI�����ϐ�
	MenuBar m_menu_bar;
	ToolWindow* m_tool_window;
	// �t�@�C������
	std::string m_file_name; // Open��Save�ŋ��p
	// �����t���O
	GUI_MANAGER_DEFINE::FLAGS m_gui_flags;
	// MyViewer�Ƃ̘A�g
	const MyModel *m_model_data_ptr; // ���f���f�[�^�ւ̃|�C���^

	// ����������
	void InitGUI();

	// ���j���[�o�[����
	void ProcessMenuBar();
public:
	GUIManager();
	~GUIManager();

	// �X�V
	void Update();

	// �����
	// ToolWindow�փJ�����|�C���^��n��
	void MediationCameraPtrToToolWindow(MainCameraGL *camera);

	// Setter
	// ���f���f�[�^�̃Z�b�g
	// NOTE: ToolWindow�������X�V
	inline void SetModelData(const MyModel* model_data)
	{
		m_model_data_ptr = model_data;
		m_tool_window->SetModelData(model_data);
	}

	// Getter
	// GUI Manager�t���O
	inline GUI_MANAGER_DEFINE::FLAGS GetGUIFlags() const { return m_gui_flags; }
	// �t�@�C���l�[��
	inline std::string GetFileName() const { return m_file_name; }
	// ���f���f�[�^
	inline const MyModel* GetModelData() const { return m_model_data_ptr; };
};

#endif