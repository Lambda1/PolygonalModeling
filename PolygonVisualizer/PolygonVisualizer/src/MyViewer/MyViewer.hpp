#ifndef __MY_VIEWER_HPP__
#define __MY_VIEWER_HPP__

#include "../OpenGL/MyGLFW/MyGLFW.hpp"

#include <string>
#include <thread>

class MyViewer
{
	// GLFWによるウィンドウマネージャ
	MyGLFW m_opengl_manager;
	int m_window_width, m_window_height;
	std::string m_window_name;

	// 初期化処理
	void InitThread(); // スレッド生成
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