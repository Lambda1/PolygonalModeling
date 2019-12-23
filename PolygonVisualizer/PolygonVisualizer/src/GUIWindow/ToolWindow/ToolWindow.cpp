#include "./ToolWindow.hpp"

ToolWindow::ToolWindow():
	m_model_data_ptr(nullptr),
	m_main_camera_ptr(nullptr),
	m_translation{}, m_scale(1.0f), m_rotate(0.0f),
	m_rotate_bits{}
{
}

ToolWindow::~ToolWindow()
{
}
// private
// フレームレート
void ToolWindow::DisplayFrameRate() const
{
	float frame_rate = ImGui::GetIO().Framerate;
	ImGui::TextColored(IMGUI_COLOR_DEFINE::COLOR4::BLUE, "Frame Rate");
	ImGui::Text(" %.2f[fps] (%.3f[ms/frame])", frame_rate, ONE_MINUTE / frame_rate);
}
// モデルデータ
void ToolWindow::DisplayModelData() const
{
	ImGui::TextColored(IMGUI_COLOR_DEFINE::COLOR4::RED, "Information Load Model");
	if (m_model_data_ptr)
	{
		ImGui::Text(" FILE NAME: %s", m_model_data_ptr->GetFileName_C_STR());
		ImGui::Text(" VERTEX: %-d", m_model_data_ptr->GetModelVertexNum());
		ImGui::Text(" FACE  : %-d", m_model_data_ptr->GetModelFaceNum());
	}
}

// カメラ更新処理
// NOTE: ImGuiは, 文字列はラベルとして扱うので, ##を加える.
void ToolWindow::UpdateCamera()
{
	ImGui::TextColored(IMGUI_COLOR_DEFINE::COLOR4::GREEN, "Main Camera");
	if (m_main_camera_ptr)
	{
		// FoV
		ImGui::Text(" Field of View : %.2f", my::math::toDegree(m_main_camera_ptr->fov)); ImGui::SameLine();
		ImGui::SliderFloat(" ", m_main_camera_ptr->GetFovPtr(), MainCameraGL::MIN_FOV_F, MainCameraGL::MAX_FOV_F, "%.2f");
		// カメラ位置
		ImGui::Text(" CAMERA POS:"); ImGui::SameLine();
		ImGui::SliderFloat3("1", m_main_camera_ptr->GetPosPtr(), m_main_camera_ptr->GetMinPos(), m_main_camera_ptr->GetMaxPos(), "%.2f", SLIDER_SPEED); ImGui::SameLine();
		if (ImGui::Button("ORIGIN##1")) { m_main_camera_ptr->ResetPos(); }
		// カメラ注視点
		ImGui::Text("  GAZE  POS:"); ImGui::SameLine();
		ImGui::SliderFloat3("2", m_main_camera_ptr->GetGazePtr(), m_main_camera_ptr->GetMinPos(), m_main_camera_ptr->GetMaxPos(), "%.2f", SLIDER_SPEED); ImGui::SameLine();
		if (ImGui::Button("ORIGIN##2")) { m_main_camera_ptr->ResetGaze(); }
	}
}
// モデル更新処理
// NOTE: モデル行列
void ToolWindow::UpdateModel()
{
	ImGui::TextColored(IMGUI_COLOR_DEFINE::COLOR4::YELLOW, "Model Matrix");
	// 平行移動
	ImGui::Text(" TRANSLATION:"); ImGui::SameLine();
	ImGui::DragFloat3("M1", m_translation, DRAG_RESOLUTION, -DRAG_MAX, DRAG_MAX, "%.2f"); ImGui::SameLine();
	if (ImGui::Button("ORIGIN##3")) { m_translation[0] = m_translation[1] = m_translation[2] = 0.0f; }
	// スケール
	ImGui::Text(" FIXED SCALE:"); ImGui::SameLine();
	ImGui::SliderFloat("M2", &m_scale, 0.0f, DRAG_MAX, "%.2f", 3.0f); ImGui::SameLine();
	if (ImGui::Button("ORIGIN##4")) { m_scale = 1.0f; }
	// 回転
	ImGui::Text("    ROTATION:"); ImGui::SameLine();
	ImGui::SliderFloat("M3", &m_rotate, -360.0f, 360.0f, "%.2f"); ImGui::SameLine();
	if(ImGui::Button("ORIGIN##5")) { m_rotate = 0.0f; }
	ImGui::Text(" AXIS:"); ImGui::SameLine();
	ImGui::Checkbox("X", &m_rotate_bits[0]); ImGui::SameLine();
	ImGui::Checkbox("Y", &m_rotate_bits[1]); ImGui::SameLine();
	ImGui::Checkbox("Z", &m_rotate_bits[2]);

	// モデル行列適用
	if (m_model_data_ptr)
	{
		m_model_data_ptr->SetTranslateMatrix(m_translation[0], m_translation[1], m_translation[2]);
		m_model_data_ptr->SetFixedScaleMatrix(m_scale);
		m_model_data_ptr->SetRotateMatrix(static_cast<GLfloat>(my::math::toRadian(m_rotate)), BoolToInt(m_rotate_bits[0]), BoolToInt(m_rotate_bits[1]), BoolToInt(m_rotate_bits[2]));
	}
}

// public
void ToolWindow::Update()
{
	ImGui::Begin(TOOL_WINDOW_DEFINE::WINDOW_NAME);
	ImGui::PushItemWidth(UI_WIDTH_SIZE);
	// モデルの詳細表示
	DisplayModelData();

	// カメラ設定表示
	ImGui::Separator();
	UpdateCamera();

	// モデル行列設定
	ImGui::Separator();
	UpdateModel();

	// フレームレート表示
	ImGui::Separator();
	DisplayFrameRate();

	ImGui::End();
}