#include "./MainInfo.hpp"
#include "./MyViewer/MyViewer.hpp"

int main(int argc, char *argv[])
{
	// �r���A�[�Ǘ�
	MyViewer viewer_manager;

	// �r���A�[�̏�����
	viewer_manager.Init(MAIN_WINDOW::WIDTH, MAIN_WINDOW::HEIGHT, MAIN_WINDOW::WINDOW_NAME);

	// ���C�����[�v
	while (viewer_manager.MainLoop())
	{
		// �X�V����
		viewer_manager.Update();
		// �`�揈��
		viewer_manager.Draw();

		// OpenGL�̃n���h������
		viewer_manager.ProcessOpenGL();
	}

	return 0;
}