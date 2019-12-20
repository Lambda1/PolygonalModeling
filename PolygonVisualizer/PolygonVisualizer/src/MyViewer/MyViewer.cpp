#include "./MyViewer.hpp"

MyViewer::MyViewer():
	m_window_width(0), m_window_height(0),
	m_fovy(0.0f), m_aspect(0.0f)
{

}

MyViewer::~MyViewer()
{
	m_shader_model.UnUseProgram();

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
	m_shader_model.Set(MY_VIEWER_DEFINE::SHADER::BASE_VERTEX, MY_VIEWER_DEFINE::SHADER::BASE_FRAGMENT);
	m_shader_stage.Set(MY_VIEWER_DEFINE::STAGE_SHADER::BASE_VERTEX, MY_VIEWER_DEFINE::STAGE_SHADER::BASE_FRAGMENT);

	// fragment bind
	m_shader_model.BindFragDataLocation(MY_VIEWER_DEFINE::SHADER::FRAGMENT);

	// テーブル作成
	InitModelShaderTable();
	InitStageShaderTable();

	// ステージデータの転送
	m_shape_base.SetShapeWire(m_stage.GetVertex(), m_stage.GetVertexSize(), m_shader_stage_table[MY_VIEWER_DEFINE::STAGE_SHADER::TABLE::POSITION]);
}
// シェーダテーブルの初期化
// NOTE: MyViewerDefine.hppと連携
void MyViewer::InitModelShaderTable()
{
	// Attribute
	m_shader_model_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::POSITION, m_shader_model.GetAttLocationValue(MY_VIEWER_DEFINE::SHADER::POSITION));
	m_shader_model_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::NORMAL, m_shader_model.GetAttLocationValue(MY_VIEWER_DEFINE::SHADER::NORMAL));
	// Uniform
	m_shader_model_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::MODEL_VIEW, m_shader_model.GetUniLocationValue(MY_VIEWER_DEFINE::SHADER::MODEL_VIEW));
	m_shader_model_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::PROJECION, m_shader_model.GetUniLocationValue(MY_VIEWER_DEFINE::SHADER::PROJECTION));
	m_shader_model_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::NORMAL_MATRIX, m_shader_model.GetUniLocationValue(MY_VIEWER_DEFINE::SHADER::NORMAL_MATRIX));
	m_shader_model_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::LPOS, m_shader_model.GetUniLocationValue(MY_VIEWER_DEFINE::SHADER::LPOS));
	m_shader_model_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::LAMB, m_shader_model.GetUniLocationValue(MY_VIEWER_DEFINE::SHADER::LAMB));
	m_shader_model_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::LDIFF, m_shader_model.GetUniLocationValue(MY_VIEWER_DEFINE::SHADER::LDIFF));
	m_shader_model_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::LSPEC, m_shader_model.GetUniLocationValue(MY_VIEWER_DEFINE::SHADER::LSPEC));

#if DEBUG_SHADER_TABLE_LOG
	std::cout << "DEBUG: MODEL_SHADER_TABLE_LOG" << std::endl;
	for (auto itr = m_shader_model_table.begin(); itr != m_shader_model_table.end(); ++itr)
	{
		std::cout << (int)itr->first << " " << itr->second << std::endl;
	}
#endif
}
// ステージシェーダの初期化
void MyViewer::InitStageShaderTable()
{
	// Attribute
	m_shader_stage_table.emplace(MY_VIEWER_DEFINE::STAGE_SHADER::TABLE::POSITION, m_shader_stage.GetAttLocationValue(MY_VIEWER_DEFINE::STAGE_SHADER::POSITION));
	// Uniform
	m_shader_stage_table.emplace(MY_VIEWER_DEFINE::STAGE_SHADER::TABLE::PROJECION, m_shader_stage.GetUniLocationValue(MY_VIEWER_DEFINE::STAGE_SHADER::PROJECTION));
	m_shader_stage_table.emplace(MY_VIEWER_DEFINE::STAGE_SHADER::TABLE::MODEL_VIEW, m_shader_stage.GetUniLocationValue(MY_VIEWER_DEFINE::STAGE_SHADER::MODEL_VIEW));
#if DEBUG_SHADER_TABLE_LOG
	std::cout << "DEBUG: STAGE_SHADER_TABLE_LOG" << std::endl;
	for (auto itr = m_shader_stage_table.begin(); itr != m_shader_stage_table.end(); ++itr)
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
	m_shape_base.DiposeMemoryPop();
	// モデルデータをGPUへ転送
	m_shape_base.SetShape
	(
		m_model_data.GetModelData(),
		m_model_data.GetModelDataSize(),
		m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::POSITION],
		m_shader_model_table[MY_VIEWER_DEFINE::SHADER::TABLE::NORMAL]
	);

	// GUIManagerのモデルデータ更新
	m_gui_manager.SetModelData(&m_model_data);
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
	
	// 開始: ImGui処理
	// ImGUIの更新
	UpdateImGui();
	// フラグ更新
	m_gui_flags = m_gui_manager.GetGUIFlags();
	// GUI結果に基づく処理
	if (m_gui_flags != GUI_MANAGER_DEFINE::FLAGS::NONE) { SwitchProcessGUI(); }
	// 終了: ImGui処理

	// PV行列の更新
	SetPVMatrix();
	// 基準とする地平線を描画
	DrawBaseStage();
	// モデルを描画
	DrawModel();
}
// 描画処理
// NOTE: モデル計算されたものをレンダリングするのみ
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