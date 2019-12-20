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
#include "../OpenGL/PrimitiveObjectGL/StageGL.hpp"
#include "../MainCamera/MainCameraGL.hpp"
#include "../OpenGL/LightGL/LightGL.hpp"
#include "../OpenGL/MyShader/MyShader.hpp"
#include "../OpenGL/MathGL/MathGL.hpp"
#include "../OpenGL/MaterialGL/MaterialGL.hpp"
#include "../OpenGL/UniformGL/UniformGL.hpp"
#include "../MyModel/MyModel.hpp"
#include "../ShapeManager/ShapeManager.hpp"

#include <GL/glew.h>

#include <string>
#include <thread>
#include <map>

#define DEBUG_SHADER_TABLE_LOG true

class MyViewer
{
	// �Œ�V�F�[�_�p�����[�^
	// NOTE: 1���f���ǂݍ��݂Ɖ���
	inline static constexpr int DRAW_ID_STAGE = 0;
	inline static constexpr int DRAW_ID_MODEL = 1;

	// GLFW�ɂ��E�B���h�E�}�l�[�W��
	MyGLFW m_opengl_manager;
	int m_window_width, m_window_height;
	std::string m_window_name;
	// ���f���V�F�[�_����
	MyShader m_shader_model;
	std::map<MY_VIEWER_DEFINE::SHADER::TABLE, const GLint> m_shader_model_table;
	// ���f���V�F�[�_����
	MyShader m_shader_stage;
	std::map<MY_VIEWER_DEFINE::STAGE_SHADER::TABLE, const GLint> m_shader_stage_table;
	// ImGui�p�ϐ�
	GUIManager m_gui_manager;
	ImGuiIO m_imgui_io;
	// �t���O����
	GUI_MANAGER_DEFINE::FLAGS m_gui_flags;
	// �����_�����O�p�ϐ�
	ShapeManager m_shape_base;
	// �r���A�[����
	MainCameraGL m_main_camera;
	LightGL m_main_light;
	StageGL m_stage;
	// ���e�����p
	GLfloat m_fovy, m_aspect;      // ��p, �A�X�y�N�g��
	MatrixGL m_projection, m_view; // PV�s��
	// ���f���f�[�^
	MyModel m_model_data;

	// ����������
	void InitOpenGL();
	void InitShader();
	void InitModelShaderTable();
	void InitStageShaderTable();
	void InitImGui();
	void InitViewer();
	void InitThread();

	// ImGUI����
	void UpdateImGui();
	// GUIManager�t���O�Ɋ�Â�����
	void SwitchProcessGUI();
	void RegistrationModel(); // ���f���o�^

	/*
		�V�F�[�_�X�V����
		NOTE: ���t���[�����s���邽��, inline�W�J
	*/
	// �V�F�[�_���̌������X�V
	inline void UpdateShaderLight()
	{
		m_shader_model.Uniform4fv(m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::LPOS], 1, (m_view * m_main_light.GetPos()).data());
		m_shader_model.Uniform3fv(m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::LAMB], 1, m_main_light.GetAmb());
		m_shader_model.Uniform3fv(m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::LDIFF], 1, m_main_light.GetDiff());
		m_shader_model.Uniform3fv(m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::LSPEC], 1, m_main_light.GetSpec());
	}

	/*
		�����_�����O����
		NOTE: ���t���[�����s���邽��, inline�W�J
	*/
	// pv�s��̌v�Z
	inline void SetPVMatrix()
	{
		m_aspect = m_opengl_manager.GetAspect();
		m_projection = MathGL::Perspective(m_fovy, m_aspect, 0.01f, 300.0f);
		m_view = m_main_camera.LookAt(0.0f, 0.0f, 0.0f);
	}
	// �r���A�[���Ƀ��f����`��
	// NOTE: base�V�F�[�_
	inline void DrawModel()
	{
		m_shader_model.UseProgram();

		// �v���W�F�N�V�����ݒ�
		m_shader_model.UniformMatrix4fv(m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::PROJECION], 1, GL_FALSE, m_projection.GetMatrix());
		// �����ݒ�
		UpdateShaderLight();
		// �@���ݒ�
		GLfloat normal[9];
		m_view.GetNormalMatrix(normal);
		m_shader_model.UniformMatrix3fv(m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::NORMAL_MATRIX], 1, GL_FALSE, normal);
		// �r���[�ݒ�
		m_shader_model.UniformMatrix4fv(m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::MODEL_VIEW], 1, GL_FALSE, m_view.GetMatrix());

		// �`��
		m_shape_base.Draw(DRAW_ID_MODEL);

		m_shader_model.UnUseProgram();
	}
	// �r���A�[�̒n������`��
	// NOTE: stage�V�F�[�_
	inline void DrawBaseStage()
	{
		m_shader_stage.UseProgram();
		
		m_shader_stage.UniformMatrix4fv(m_shader_stage_table[MY_VIEWER_DEFINE::STAGE_SHADER::TABLE::PROJECION], 1, GL_FALSE, m_projection.GetMatrix());
		m_shader_stage.UniformMatrix4fv(m_shader_stage_table[MY_VIEWER_DEFINE::STAGE_SHADER::TABLE::MODEL_VIEW], 1, GL_FALSE, m_view.GetMatrix());
		m_shape_base.Draw(DRAW_ID_STAGE);

		m_shader_stage.UnUseProgram();
	}
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