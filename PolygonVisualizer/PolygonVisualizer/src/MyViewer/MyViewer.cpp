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
	ImGui::StyleColorsClassic();

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