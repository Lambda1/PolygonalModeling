#include "./MyViewer.hpp"

MyViewer::MyViewer():
	m_window_width(0), m_window_height(0)
{

}

MyViewer::~MyViewer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

// private
/*
	ImGUI初期化
	NOTE: コンテクスト作成後に行うこと.
*/
void MyViewer::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_opengl_manager.GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 130");
}
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

	// 初期化処理
	InitImGui();
}
// 更新処理
void MyViewer::Update()
{

}
// 描画処理
void MyViewer::Draw()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	bool is_window = true;
	ImGui::ShowDemoWindow(&is_window);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	m_opengl_manager.SwapBuffer();
}
// OpenGLの処理
void MyViewer::ProcessOpenGL()
{
	// OpenGL: イベント処理
	m_opengl_manager.PollEvents();
	// OpenGL: エラーチェック
	m_opengl_manager.ErrorCheck();
}