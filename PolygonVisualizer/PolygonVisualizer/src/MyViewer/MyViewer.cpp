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
	// ImGui: コンテクスト作成
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// ImGui: 入出力初期化
	m_imgui_io = ImGui::GetIO();

	// ImGui: 見栄えの設定
	ImGui::StyleColorsDark();
	ImGui::GetStyle().Alpha = 0.9f;

	// ImGui: OpenGL連携
	ImGui_ImplGlfw_InitForOpenGL(m_opengl_manager.GetWindow(), true);
	ImGui_ImplOpenGL3_Init(MY_VIEWER_DEFINE::IMGUI::GLSL_VERSION_C_STR);
}
// OpenGL初期化
void MyViewer::InitOpenGL()
{
	// OpenGLコンテクストの作成
	m_opengl_manager.InitWindow(m_window_width, m_window_height, m_window_name.c_str());
	// 背景色設定
	glClearColor(0.3f, 0.3f, 0.3f, 1);
	// シェーダ初期化
	InitShader();
}
void MyViewer::InitShader()
{
	// Vertex/Fragmentシェーダの初期化
	m_shader.Set(MY_VIEWER_DEFINE::SHADER::BASE_VERTEX, MY_VIEWER_DEFINE::SHADER::BASE_FRAGMENT);
}
// スレッド生成
void MyViewer::InitThread()
{
}
// ImGuiのレンダリング
void MyViewer::UpdateImGui()
{
	// フレーム生成
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// GUI更新
	m_gui_manager.Update();

	// レンダリング
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
// フラグに基づく処理
void MyViewer::SwitchProcessGUI()
{
	switch (m_gui_flags)
	{
	case GUI_MANAGER_DEFINE::FLAGS::OPEN_FILE:
		break;
	case GUI_MANAGER_DEFINE::FLAGS::SAVE_FILE:
		break;
	default:
		break;
	}
}

// public
// 初期化処理
void MyViewer::Init(const int& width, const int& height, const std::string& name)
{
	// ウィンドウデータの初期化
	m_window_width = width, m_window_height = height;
	m_window_name = name;

	// 初期化処理
	InitOpenGL();
	InitImGui();
}
// 更新処理
// NOTE: ImGUIが即時処理のため, Update側で画面クリアとImGUIの描画・更新を行う.
void MyViewer::Update()
{
	// 画面クリア
	m_opengl_manager.Clear();
	// ImGUIの更新
	UpdateImGui();

	// フラグ更新
	m_gui_flags = m_gui_manager.GetGUIFlags();

	// GUI結果に基づく処理
	if (m_gui_flags != GUI_MANAGER_DEFINE::FLAGS::NONE) { SwitchProcessGUI(); }
}
// 描画処理
void MyViewer::Draw()
{


	// ダブルバッファリング
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