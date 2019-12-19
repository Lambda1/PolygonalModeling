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
	ImGUI������
	NOTE: �R���e�N�X�g�쐬��ɍs������.
*/
void MyViewer::InitImGui()
{
	// ImGui: �R���e�N�X�g�쐬
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// ImGui: ���o�͏�����
	m_imgui_io = ImGui::GetIO();

	// ImGui: ���h���̐ݒ�
	ImGui::StyleColorsDark();
	ImGui::GetStyle().Alpha = 0.9f;

	// ImGui: OpenGL�A�g
	ImGui_ImplGlfw_InitForOpenGL(m_opengl_manager.GetWindow(), true);
	ImGui_ImplOpenGL3_Init(MY_VIEWER_DEFINE::IMGUI::GLSL_VERSION_C_STR);
}
// OpenGL������
void MyViewer::InitOpenGL()
{
	// OpenGL�R���e�N�X�g�̍쐬
	m_opengl_manager.InitWindow(m_window_width, m_window_height, m_window_name.c_str());
	// �w�i�F�ݒ�
	glClearColor(0.3f, 0.3f, 0.3f, 1);
	// �V�F�[�_������
	InitShader();
}
void MyViewer::InitShader()
{
	// Vertex/Fragment�V�F�[�_�̏�����
	m_shader.Set(MY_VIEWER_DEFINE::SHADER::BASE_VERTEX, MY_VIEWER_DEFINE::SHADER::BASE_FRAGMENT);
}
// �X���b�h����
void MyViewer::InitThread()
{
}
// ImGui�̃����_�����O
void MyViewer::UpdateImGui()
{
	// �t���[������
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// GUI�X�V
	m_gui_manager.Update();

	// �����_�����O
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
// �t���O�Ɋ�Â�����
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
// ����������
void MyViewer::Init(const int& width, const int& height, const std::string& name)
{
	// �E�B���h�E�f�[�^�̏�����
	m_window_width = width, m_window_height = height;
	m_window_name = name;

	// ����������
	InitOpenGL();
	InitImGui();
}
// �X�V����
// NOTE: ImGUI�����������̂���, Update���ŉ�ʃN���A��ImGUI�̕`��E�X�V���s��.
void MyViewer::Update()
{
	// ��ʃN���A
	m_opengl_manager.Clear();
	// ImGUI�̍X�V
	UpdateImGui();

	// �t���O�X�V
	m_gui_flags = m_gui_manager.GetGUIFlags();

	// GUI���ʂɊ�Â�����
	if (m_gui_flags != GUI_MANAGER_DEFINE::FLAGS::NONE) { SwitchProcessGUI(); }
}
// �`�揈��
void MyViewer::Draw()
{


	// �_�u���o�b�t�@�����O
	m_opengl_manager.SwapBuffer();
}
// OpenGL�̏���
void MyViewer::ProcessOpenGL()
{
	// OpenGL: �C�x���g����
	m_opengl_manager.PollEvents();
	// OpenGL: �G���[�`�F�b�N
	m_opengl_manager.ErrorCheck();
}