#ifndef __MY_VIEWER_HPP__
#define __MY_VIEWER_HPP__

#include "./MyViewerDefine.hpp"
#include "../GUIManager/GUIManagerDefine.hpp"
#include "../GUIManager/GUIManager.hpp"
#include "../OpenGL/MyGLFW/MyGLFW.hpp"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

// �e�X�g����
#include "../OpenGL/MyShader/MyShader.hpp"

#include <string>
#include <thread>

class MyViewer
{
	// GLFW�ɂ��E�B���h�E�}�l�[�W��
	MyGLFW m_opengl_manager;
	int m_window_width, m_window_height;
	std::string m_window_name;
	// �V�F�[�_����
	MyShader m_shader;
	// ImGui�p�ϐ�
	GUIManager m_gui_manager;
	ImGuiIO m_imgui_io;
	// �t���O����
	GUI_MANAGER_DEFINE::FLAGS m_gui_flags;

	// ����������
	void InitOpenGL();
	void InitShader();
	void InitImGui();
	void InitThread();

	// ImGUI����
	void UpdateImGui();
	// GUIManager�t���O�Ɋ�Â�����
	void SwitchProcessGUI();
public:
	MyViewer();
	~MyViewer();

	// ������
	void Init(const int &width, const int &height, const std::string &name);

	// �X�V����
	void Update();
	// �`�揈��
	void Draw();
	// OpenGL�p������
	void ProcessOpenGL();
	// �p������
	inline bool MainLoop() const { return m_opengl_manager.MainLoop(); }
};

#endif