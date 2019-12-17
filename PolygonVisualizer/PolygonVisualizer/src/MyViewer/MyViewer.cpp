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
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_opengl_manager.GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 130");
}
// �X���b�h����
void MyViewer::InitThread()
{
}

// public
// ����������
void MyViewer::Init(const int& width, const int& height, const std::string& name)
{
	// �E�B���h�E�f�[�^�̏�����
	m_window_width = width, m_window_height = height;
	m_window_name = name;
	// OpenGL�R���e�N�X�g�̍쐬
	m_opengl_manager.InitWindow(m_window_width, m_window_height, m_window_name.c_str());

	// ����������
	InitImGui();
}
// �X�V����
void MyViewer::Update()
{

}
// �`�揈��
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
// OpenGL�̏���
void MyViewer::ProcessOpenGL()
{
	// OpenGL: �C�x���g����
	m_opengl_manager.PollEvents();
	// OpenGL: �G���[�`�F�b�N
	m_opengl_manager.ErrorCheck();
}