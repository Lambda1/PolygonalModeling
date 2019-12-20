#include "./MyViewer.hpp"

MyViewer::MyViewer():
	m_window_width(0), m_window_height(0),
	m_fovy(0.0f), m_aspect(0.0f)
{

}

MyViewer::~MyViewer()
{
	m_shader.UnUseProgram();

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
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	// OpenGLコンテクストの作成
	m_opengl_manager.InitWindow(m_window_width, m_window_height, m_window_name.c_str());
	// 背景色設定
	glClearColor(0.3f, 0.3f, 0.3f, 1);
	// シェーダ初期化
	InitShader();
}
// シェーダ初期化
void MyViewer::InitShader()
{
	// Vertex/Fragmentシェーダの初期化
	m_shader.Set(MY_VIEWER_DEFINE::SHADER::BASE_VERTEX, MY_VIEWER_DEFINE::SHADER::BASE_FRAGMENT);

	// fragment bind
	m_shader.BindFragDataLocation(MY_VIEWER_DEFINE::SHADER::FRAGMENT);

	// テーブル作成
	InitShaderTable();
}
// シェーダテーブルの初期化
// NOTE: MyViewerDefine.hppと連携
void MyViewer::InitShaderTable()
{
	// Attribute
	m_shader_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::POSITION, m_shader.GetAttLocationValue(MY_VIEWER_DEFINE::SHADER::POSITION));
	m_shader_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::NORMAL, m_shader.GetAttLocationValue(MY_VIEWER_DEFINE::SHADER::NORMAL));
	// Uniform
	m_shader_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::MODEL_VIEW, m_shader.GetUniLocationValue(MY_VIEWER_DEFINE::SHADER::MODEL_VIEW));
	m_shader_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::PROJECION, m_shader.GetUniLocationValue(MY_VIEWER_DEFINE::SHADER::PROJECTION));
	m_shader_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::NORMAL_MATRIX, m_shader.GetUniLocationValue(MY_VIEWER_DEFINE::SHADER::NORMAL_MATRIX));
	m_shader_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::LPOS, m_shader.GetUniLocationValue(MY_VIEWER_DEFINE::SHADER::LPOS));
	m_shader_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::LAMB, m_shader.GetUniLocationValue(MY_VIEWER_DEFINE::SHADER::LAMB));
	m_shader_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::LDIFF, m_shader.GetUniLocationValue(MY_VIEWER_DEFINE::SHADER::LDIFF));
	m_shader_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::LSPEC, m_shader.GetUniLocationValue(MY_VIEWER_DEFINE::SHADER::LSPEC));

#if DEBUG_SHADER_TABLE_LOG
	std::cout << "DEBUG: SHADER_TABLE_LOG" << std::endl;
	for (auto itr = m_shader_table.begin(); itr != m_shader_table.end(); ++itr)
	{
		std::cout << (int)itr->first << " " << itr->second << std::endl;
	}
#endif
}
// スレッド生成
void MyViewer::InitThread()
{
}
// ビュアー用変数初期化
void MyViewer::InitViewer()
{
	// カメラ位置
	m_main_camera.SetPos(10.0f, 10.0f, 10.0f);
	m_main_camera.up_y = 1.0f;

	// ライティング
	m_main_light.SetPos(0.0f, 3.0f, 1.0f, 1.0f);
	m_main_light.SetAmb(1.0f, 1.0f, 1.0f);
	m_main_light.SetDiff(1.0f, 1.0f, 1.0f);
	m_main_light.SetSpec(1.0f, 1.0f, 1.0f);
	
	// 画面処理
	m_fovy = m_opengl_manager.GetFovy(30.0f);
	m_aspect = m_opengl_manager.GetAspect();
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
		RegistrationModel(); // モデルデータ登録
		break;
	case GUI_MANAGER_DEFINE::FLAGS::SAVE_FILE:
		break;
	default:
		break;
	}
}
// モデルデータの登録
void MyViewer::RegistrationModel()
{
	// モデル読み込み
	m_model_data.LoadModelData(m_gui_manager.GetFileName());

	// 読み込み中のモデルデータの解放
	m_shape_base.DiposeMemory();
	// モデルデータをGPUへ転送
	m_shape_base.SetShapeWire
	(
		m_model_data.GetModelData(),
		m_model_data.GetModelDataSize(),
		m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::POSITION],
		m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::NORMAL]
	);

	// GUIManagerのモデルデータ更新
	m_gui_manager.SetModelData(&m_model_data);
}
// ビュアーの地平線を描画
void MyViewer::DrawBaseStage()
{
	m_aspect = m_opengl_manager.GetAspect();
	m_projection = MathGL::Perspective(m_fovy, m_aspect, 0.01f, 300.0f);
	m_view = m_main_camera.LookAt(0.0f, 0.0f, 0.0f);

	static GLfloat r = 0.0f;
	m_view = m_view * MathGL::Quaternion(r, 0, 1, 0);
	r += 0.01f;

	m_shader.UniformMatrix4fv(m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::PROJECION], 1, GL_FALSE, m_projection.GetMatrix());

	m_shader.Uniform4fv(m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::LPOS], 1, (m_view * m_main_light.GetPos()).data());
	m_shader.Uniform3fv(m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::LAMB], 1, m_main_light.GetAmb());
	m_shader.Uniform3fv(m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::LDIFF], 1, m_main_light.GetDiff());
	m_shader.Uniform3fv(m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::LSPEC], 1, m_main_light.GetSpec());

	GLfloat normal[9];
	m_view.GetNormalMatrix(normal);
	m_shader.UniformMatrix3fv(m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::NORMAL_MATRIX], 1, GL_FALSE, normal);
	m_shader.UniformMatrix4fv(m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::MODEL_VIEW], 1, GL_FALSE, m_view.GetMatrix());
	
	if (m_model_data.IsRegistration()) { m_shape_base.Draw(0); }
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
	InitViewer();
}
// 更新処理
// NOTE: ImGUIが即時処理のため, Update側で画面クリアを行う.
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

	// ここから3D描画
	m_shader.UseProgram();	 // シェーダ起動
	DrawBaseStage();         // 基準点を描画
	m_shader.UnUseProgram(); // シェーダ終了
	// ここまで3D描画
}
// 描画処理
void MyViewer::Draw()
{
	// ImGui: レンダリング
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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