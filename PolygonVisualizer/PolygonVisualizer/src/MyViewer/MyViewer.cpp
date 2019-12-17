#include "./MyViewer.hpp"

MyViewer::MyViewer():
	m_window_width(0), m_window_height(0)
{

}

MyViewer::~MyViewer()
{

}

// private
// �������֌W
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
}
// �X�V����
void MyViewer::Update()
{

}
// �`�揈��
void MyViewer::Draw()
{

}
// OpenGL�̏���
void MyViewer::ProcessOpenGL()
{
	// OpenGL: �C�x���g����
	m_opengl_manager.PollEvents();
	// OpenGL: �G���[�`�F�b�N
	m_opengl_manager.ErrorCheck();
}