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
		// 更新処理
		viewer_manager.Update();
		// 描画処理
		viewer_manager.Draw();

		// OpenGLのハンドラ処理
		viewer_manager.ProcessOpenGL();
	}

	return 0;
}