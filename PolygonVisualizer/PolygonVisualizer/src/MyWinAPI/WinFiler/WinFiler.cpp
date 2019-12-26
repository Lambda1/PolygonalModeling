#include "./WinFiler.hpp"

WinFiler::WinFiler()
{
}

WinFiler::~WinFiler()
{
}

// private
OPENFILENAME WinFiler::CommonDialog()
{
	OPENFILENAME ofn = {};
	TCHAR strFile[MAX_PATH] = "";

	ofn.lStructSize = sizeof(OPENFILENAME);
	// 親ウィンドウハンドル(MFCではないのでnull)
	ofn.hwndOwner = nullptr;
	// ファイルフィルター
	ofn.lpstrFilter =
		TEXT("Wavefront {*.obj}\0*.obj\0")
		TEXT("Point Cloud {*.pcd}\0*.pcd\0")
		TEXT("4-byte binary {*.bin4}\0*.bin4\0");
	// ユーザ定義フィルタ
	ofn.lpstrCustomFilter = nullptr;
	// ユーザ定義フィルタ長
	ofn.nMaxCustFilter = 0;
	// lpstrFilterで定義されたものから何番目をデフォにするか
	ofn.nFilterIndex = 0;
	// 開いた際に入力されるバッファ(必ず初期化すること)
	ofn.lpstrFile = strFile;
	// lpstrFile長
	ofn.nMaxFile = MAX_PATH;
	// 既存ファイルのみ選択可
	ofn.Flags = OFN_FILEMUSTEXIST;

	return ofn;
}

// public
/*
	セレクトファイル
	NOTE: 選択されたファイルのフルパスを返し, ない場合は空白を返す.
*/
std::string WinFiler::SelectFile()
{
	OPENFILENAME ofn = CommonDialog();

	if (GetOpenFileName(&ofn))
	{
		std::string full_path(ofn.lpstrFile);
		return full_path;

	}

	return INVALID_TABLE::INVALID_FILE;
}
/*
	セーブファイル
	NOTE: 選択されたファイルのフルパスを返し, ない場合は空白を返す.
*/
std::string WinFiler::SaveFile()
{
	OPENFILENAME ofn = CommonDialog();

	if (GetSaveFileName(&ofn))
	{
		std::string full_path(ofn.lpstrFile);
		return full_path;

	}

	return INVALID_TABLE::INVALID_FILE;
}