#include "./MainInfo.hpp"
#include "./MyViewer/MyViewer.hpp"

int main(int argc, char *argv[])
{
	// ビュアー管理
	MyViewer viewer_manager;

	// ビュアーの初期化
	viewer_manager.Init(MAIN_WINDOW::WIDTH, MAIN_WINDOW::HEIGHT, MAIN_WINDOW::WINDOW_NAME);

	// メインループ
	while (viewer_manager.MainLoop())
	{
		viewer_manager.Update();
		viewer_manager.Draw();

		viewer_manager.ProcessOpenGL();
	}

	return 0;
}