#include "./MyViewer.hpp"

MyViewer::MyViewer():
	m_window_width(0), m_window_height(0)
{

}

MyViewer::~MyViewer()
{

}

// private
// 初期化関係
// スレッド生成
void MyViewer::InitThread()
{
}

// public
// 初期化処理
void MyViewer::Init(const int& width, const int& height, const std::string& name)
{
	// ウィンドウデータの初期化
	m_window_width = width, m_window_height = height;
	m_window_name = name;
	// OpenGLコンテクストの作成
	m_opengl_manager.InitWindow(m_window_width, m_window_height, m_window_name.c_str());
}
// 更新処理
void MyViewer::Update()
{

}
// 描画処理
void MyViewer::Draw()
{

}
// OpenGLの処理
void MyViewer::ProcessOpenGL()
{
	// OpenGL: イベント処理
	m_opengl_manager.PollEvents();
	// OpenGL: エラーチェック
	m_opengl_manager.ErrorCheck();
}