#ifndef __MY_VIEWER_HPP__
#define __MY_VIEWER_HPP__

#include "./MyViewerDefine.hpp"
#include "../GUIManager/GUIManager.hpp"
#include "../OpenGL/MyGLFW/MyGLFW.hpp"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include <string>
#include <thread>

class MyViewer
{
	// GLFWによるウィンドウマネージャ
	MyGLFW m_opengl_manager;
	int m_window_width, m_window_height;
	std::string m_window_name;
	// ImGui用変数
	GUIManager m_gui_manager;
	ImGuiIO m_imgui_io;

	// 初期化処理
	void InitOpenGL();
	void InitImGui();
	void InitThread();

	// ImGUI処理
	void UpdateImGui();
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