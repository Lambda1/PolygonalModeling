#include "./ToolWindow.hpp"

ToolWindow::ToolWindow():
	m_model_data_ptr(nullptr)
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
// カメラ情報表示
void ToolWindow::DisplayCameaInfo() const
{
	ImGui::TextColored(IMGUI_COLOR_DEFINE::COLOR4::GREEN, "Main Camera");
	if (m_main_camera_ptr)
	{
		ImGui::Text(" Field of View : %.2f", m_main_camera_ptr->fov);
		ImGui::Text(" POSITION : (%.2f, %.2f, %.2f)", m_main_camera_ptr->x, m_main_camera_ptr->y, m_main_camera_ptr->z);
		ImGui::Text(" GAZE POS : (%.2f, %.2f, %.2f)", m_main_camera_ptr->gx, m_main_camera_ptr->gy, m_main_camera_ptr->gz);
	}
}

// public
void ToolWindow::Update()
{
	ImGui::Begin(TOOL_WINDOW_DEFINE::WINDOW_NAME);

	// モデルの詳細表示
	DisplayModelData();

	// カメラ設定表示
	ImGui::Separator();
	DisplayCameaInfo();

	// フレームレート表示
	ImGui::Separator();
	DisplayFrameRate();

	ImGui::End();
}