#include "./ToolWindow.hpp"

ToolWindow::ToolWindow():
	m_model_data_ptr(nullptr),
	m_main_camera_ptr(nullptr),
	m_translation{}, m_scale(1.0f), m_rotate{}
{
}

ToolWindow::~ToolWindow()
{
}
// private
// �t���[�����[�g
void ToolWindow::DisplayFrameRate() const
{
	float frame_rate = ImGui::GetIO().Framerate;
	ImGui::TextColored(IMGUI_COLOR_DEFINE::COLOR4::BLUE, "Frame Rate");
	ImGui::Text(" %.2f[fps] (%.3f[ms/frame])", frame_rate, ONE_MINUTE / frame_rate);
}
// ���f���f�[�^
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

// �J�����X�V����
// NOTE: ImGui��, ������̓��x���Ƃ��Ĉ����̂�, �����ɕς��Ă���.
void ToolWindow::UpdateCamera()
{
	ImGui::TextColored(IMGUI_COLOR_DEFINE::COLOR4::GREEN, "Main Camera");
	if (m_main_camera_ptr)
	{
		// FoV
		ImGui::Text(" Field of View : %.2f", my::math::toDegree(m_main_camera_ptr->fov)); ImGui::SameLine();
		ImGui::SliderFloat(" ", m_main_camera_ptr->GetFovPtr(), MainCameraGL::MIN_FOV_F, MainCameraGL::MAX_FOV_F, "%.2f");
		// �J�����ʒu
		ImGui::Text(" CAMERA POS:"); ImGui::SameLine();
		ImGui::SliderFloat3("1", m_main_camera_ptr->GetPosPtr(), m_main_camera_ptr->GetMinPos(), m_main_camera_ptr->GetMaxPos(), "%.2f", SLIDER_SPEED); ImGui::SameLine();
		if (ImGui::Button("ORIGIN")) { m_main_camera_ptr->ResetPos(); }
		// �J���������_
		ImGui::Text("  GAZE  POS:"); ImGui::SameLine();
		ImGui::SliderFloat3("2", m_main_camera_ptr->GetGazePtr(), m_main_camera_ptr->GetMinPos(), m_main_camera_ptr->GetMaxPos(), "%.2f", SLIDER_SPEED); ImGui::SameLine();
		if (ImGui::Button("ORIGlN")) { m_main_camera_ptr->ResetGaze(); }
	}
}
// ���f���X�V����
// NOTE: ���f���s��
void ToolWindow::UpdateModel()
{
	ImGui::TextColored(IMGUI_COLOR_DEFINE::COLOR4::YELLOW, "Model Matrix");
	// ���s�ړ�
	ImGui::Text(" TRANSLATION:"); ImGui::SameLine();
	ImGui::DragFloat3("M1", m_translation, DRAG_RESOLUTION, -DRAG_MAX, DRAG_MAX, "%.2f"); ImGui::SameLine();
	if (ImGui::Button("ORlGIN")) { m_translation[0] = m_translation[1] = m_translation[2] = 0.0f; }
	// �X�P�[��
	ImGui::Text(" FIXED SCALE:"); ImGui::SameLine();
	ImGui::SliderFloat("M2", &m_scale, 1.0f, DRAG_MAX, "%.2f", 3.0f); ImGui::SameLine();
	if (ImGui::Button("ORlGlN")) { m_scale = 1.0f; }

	// ���f���s��K�p
	if (m_model_data_ptr)
	{
		m_model_data_ptr->SetTranslateMatrix(m_translation[0], m_translation[1], m_translation[2]);
		m_model_data_ptr->SetFixedScaleMatrix(m_scale);
	}
}

// public
void ToolWindow::Update()
{
	ImGui::Begin(TOOL_WINDOW_DEFINE::WINDOW_NAME);
	ImGui::PushItemWidth(UI_WIDTH_SIZE);
	// ���f���̏ڍו\��
	DisplayModelData();

	// �J�����ݒ�\��
	ImGui::Separator();
	UpdateCamera();

	// ���f���s��ݒ�
	ImGui::Separator();
	UpdateModel();

	// �t���[�����[�g�\��
	ImGui::Separator();
	DisplayFrameRate();

	ImGui::End();
}