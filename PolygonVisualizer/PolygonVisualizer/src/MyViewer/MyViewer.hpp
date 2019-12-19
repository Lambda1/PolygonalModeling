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
	// GLFWによるウィンドウマネージャ
	MyGLFW m_opengl_manager;
	int m_window_width, m_window_height;
	std::string m_window_name;
	// シェーダ処理
	MyShader m_shader;
	std::map<MY_VIEWER_DEFINE::SHADER::TABLE, const GLint> m_shader_table;
	// ImGui用変数
	GUIManager m_gui_manager;
	ImGuiIO m_imgui_io;
	// フラグ処理
	GUI_MANAGER_DEFINE::FLAGS m_gui_flags;
	// レンダリング用変数
	ShapeManager m_shape_base;
	UniformGL<MaterialGL>* m_material;

	// 初期化処理
	void InitOpenGL();
	void InitShader();
	void InitShaderTable();
	void InitImGui();
	void InitThread();

	// ImGUI処理
	void UpdateImGui();
	// GUIManagerフラグに基づく処理
	void SwitchProcessGUI();

	// レンダリング処理
	void DrawBaseStage();
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