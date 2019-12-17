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
		viewer_manager.Update();
		viewer_manager.Draw();

		viewer_manager.ProcessOpenGL();
	}

	return 0;
}