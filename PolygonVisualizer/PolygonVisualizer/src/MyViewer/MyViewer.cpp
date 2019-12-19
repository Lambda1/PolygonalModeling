#include "./MyViewer.hpp"

MyViewer::MyViewer():
	m_window_width(0), m_window_height(0)
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
	m_shader_table.emplace(MY_VIEWER_DEFINE::SHADER::TABLE::MATERIAL, m_shader.GetUniformBlockIndex(MY_VIEWER_DEFINE::SHADER::MATERIAL));
	// Block Bind
	m_shader.UniformBlockBind(m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::MATERIAL], 0);
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
// ビュアーの地平線を描画
void MyViewer::DrawBaseStage()
{
	const GLfloat fovy = m_opengl_manager.GetFovy(30.0f);
	const GLfloat aspect = m_opengl_manager.GetAspect();

	MatrixGL m_projection = MathGL::Perspective(fovy, aspect, 0.01f, 300.0f);
	MatrixGL m_view = MathGL::LookAt(10.0f, 10.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	m_shader.UniformMatrix4fv(m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::PROJECION], 1, GL_FALSE, m_projection.GetMatrix());

	LightGL m_light;
	m_light.SetPos(0.0f, 10.0f, 1.0f, 1.0f);
	m_light.SetAmb(1.0f, 1.0f, 1.0f);
	m_light.SetDiff(1.0f, 1.0f, 1.0f);
	m_light.SetSpec(1.0f, 1.0f, 1.0f);
	m_shader.Uniform4fv(m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::LPOS], 1, (m_view * m_light.GetPos()).data());
	m_shader.Uniform3fv(m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::LAMB], 1, m_light.GetAmb());
	m_shader.Uniform3fv(m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::LDIFF], 1, m_light.GetDiff());
	m_shader.Uniform3fv(m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::LSPEC], 1, m_light.GetSpec());

	GLfloat normal[9];
	m_view.GetNormalMatrix(normal);
	m_shader.UniformMatrix3fv(m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::NORMAL_MATRIX], 1, GL_FALSE, normal);
	m_shader.UniformMatrix4fv(m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::MODEL_VIEW], 1, GL_FALSE, m_view.GetMatrix());
	m_material->Select(0,0);
	m_shape_base.Draw(0);
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

	// debug
	std::vector<MaterialGL> m___;
	m___.emplace_back(MaterialGL{ 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 0.3f, 0.3f, 0.3f, 30.0f });
	m_material = new UniformGL<MaterialGL>(m___.data(), m___.size());
	CubeGL m_cube;
	m_shape_base.SetShape(m_cube.GetVertex(), m_cube.GetVertexSize(), m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::POSITION], m_shader_table[MY_VIEWER_DEFINE::SHADER::TABLE::NORMAL]);
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
}
// 描画処理
void MyViewer::Draw()
{
	// シェーダ起動
	m_shader.UseProgram();

	// 基準点を描画
	DrawBaseStage();

	// ImGui: レンダリング
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// ダブルバッファリング
	m_opengl_manager.SwapBuffer();
	// シェーダ終了
	m_shader.UnUseProgram();
}
// OpenGLの処理
void MyViewer::ProcessOpenGL()
{
	// OpenGL: イベント処理
	m_opengl_manager.PollEvents();
	// OpenGL: エラーチェック
	m_opengl_manager.ErrorCheck();
}