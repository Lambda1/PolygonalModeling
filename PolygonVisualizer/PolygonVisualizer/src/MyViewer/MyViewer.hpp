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
#include "../OpenGL/PrimitiveObjectGL/CubeGL.hpp"
#include "../OpenGL/LightGL/LightGL.hpp"
#include "../OpenGL/MyShader/MyShader.hpp"
#include "../OpenGL/MathGL/MathGL.hpp"
#include "../OpenGL/MaterialGL/MaterialGL.hpp"
#include "../OpenGL/UniformGL/UniformGL.hpp"
#include "../ShapeManager/ShapeManager.hpp"

#include <GL/glew.h>

#include <string>
#include <thread>
#include <map>

#define DEBUG_SHADER_TABLE_LOG true

class MyViewer
{
	// GLFW�ɂ��E�B���h�E�}�l�[�W��
	MyGLFW m_opengl_manager;
	int m_window_width, m_window_height;
	std::string m_window_name;
	// �V�F�[�_����
	MyShader m_shader;
	std::map<MY_VIEWER_DEFINE::SHADER::TABLE, const GLint> m_shader_table;
	// ImGui�p�ϐ�
	GUIManager m_gui_manager;
	ImGuiIO m_imgui_io;
	// �t���O����
	GUI_MANAGER_DEFINE::FLAGS m_gui_flags;
	// �����_�����O�p�ϐ�
	ShapeManager m_shape_base;
	UniformGL<MaterialGL>* m_material;

	// ����������
	void InitOpenGL();
	void InitShader();
	void InitShaderTable();
	void InitImGui();
	void InitThread();

	// ImGUI����
	void UpdateImGui();
	// GUIManager�t���O�Ɋ�Â�����
	void SwitchProcessGUI();

	// �����_�����O����
	void DrawBaseStage();
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