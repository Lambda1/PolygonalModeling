#ifndef __MY_VIEWER_HPP__
#define __MY_VIEWER_HPP__

#include "./MyViewerDefine.hpp"
#include "../GUIManager/GUIManagerDefine.hpp"
#include "../GUIManager/GUIManager.hpp"
#include "../OpenGL/MyGLFW/MyGLFW.hpp"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

// テスト処理
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
	// 固定シェーダパラメータ
	// NOTE: 1モデル読み込みと仮定
	inline static constexpr int DRAW_ID_STAGE = 0;
	inline static constexpr int DRAW_ID_MODEL = 1;

	// GLFWによるウィンドウマネージャ
	MyGLFW m_opengl_manager;
	int m_window_width, m_window_height;
	std::string m_window_name;
	// モデルシェーダ処理
	MyShader m_shader_model;
	std::map<MY_VIEWER_DEFINE::SHADER::TABLE, const GLint> m_shader_model_table;
	// モデルシェーダ処理
	MyShader m_shader_stage;
	std::map<MY_VIEWER_DEFINE::STAGE_SHADER::TABLE, const GLint> m_shader_stage_table;
	// ImGui用変数
	GUIManager m_gui_manager;
	ImGuiIO m_imgui_io;
	// フラグ処理
	GUI_MANAGER_DEFINE::FLAGS m_gui_flags;
	// レンダリング用変数
	ShapeManager m_shape_base;
	// ビュアー処理
	MainCameraGL m_main_camera;
	LightGL m_main_light;
	StageGL m_stage;
	// 投影処理用
	GLfloat m_fovy, m_aspect;      // 画角, アスペクト比
	MatrixGL m_projection, m_view; // PV行列
	// モデルデータ
	MyModel m_model_data;

	// 初期化処理
	void InitOpenGL();
	void InitShader();
	void InitModelShaderTable();
	void InitStageShaderTable();
	void InitImGui();
	void InitViewer();
	void InitThread();

	// ImGUI処理
	void UpdateImGui();
	// GUIManagerフラグに基づく処理
	void SwitchProcessGUI();
	void RegistrationModel(); // モデル登録

	/*
		シェーダ更新処理
		NOTE: 毎フレーム実行するため, inline展開
	*/
	// シェーダ中の光源を更新
	inline void UpdateShaderLight()
	{
		m_shader_model.Uniform4fv(m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::LPOS], 1, (m_view * m_main_light.GetPos()).data());
		m_shader_model.Uniform3fv(m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::LAMB], 1, m_main_light.GetAmb());
		m_shader_model.Uniform3fv(m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::LDIFF], 1, m_main_light.GetDiff());
		m_shader_model.Uniform3fv(m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::LSPEC], 1, m_main_light.GetSpec());
	}

	/*
		レンダリング処理
		NOTE: 毎フレーム実行するため, inline展開
	*/
	// pv行列の計算
	inline void SetPVMatrix()
	{
		m_aspect = m_opengl_manager.GetAspect();
		m_projection = MathGL::Perspective(m_fovy, m_aspect, 0.01f, 300.0f);
		m_view = m_main_camera.LookAt(0.0f, 0.0f, 0.0f);
	}
	// ビュアー中にモデルを描画
	// NOTE: baseシェーダ
	inline void DrawModel()
	{
		m_shader_model.UseProgram();

		// プロジェクション設定
		m_shader_model.UniformMatrix4fv(m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::PROJECION], 1, GL_FALSE, m_projection.GetMatrix());
		// 光源設定
		UpdateShaderLight();
		// 法線設定
		GLfloat normal[9];
		m_view.GetNormalMatrix(normal);
		m_shader_model.UniformMatrix3fv(m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::NORMAL_MATRIX], 1, GL_FALSE, normal);
		// ビュー設定
		m_shader_model.UniformMatrix4fv(m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::MODEL_VIEW], 1, GL_FALSE, m_view.GetMatrix());

		// 描画
		m_shape_base.Draw(DRAW_ID_MODEL);

		m_shader_model.UnUseProgram();
	}
	// ビュアーの地平線を描画
	// NOTE: stageシェーダ
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

	// 初期化
	void Init(const int &width, const int &height, const std::string &name);

	// 更新処理
	void Update();
	// 描画処理
	void Draw();
	// OpenGL継続処理
	void ProcessOpenGL();
	// 継続判定
	inline bool MainLoop() const { return m_opengl_manager.MainLoop(); }
};

#endif