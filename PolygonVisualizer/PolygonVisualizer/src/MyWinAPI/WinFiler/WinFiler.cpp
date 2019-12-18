#include "./WinFiler.hpp"

WinFiler::WinFiler()
{
}

WinFiler::~WinFiler()
{
}

// public
/*
	ファイルセレクト
	NOTE: 選択されたファイルのフルパスを返し, ない場合は空白を返す.
*/
std::string WinFiler::SelectFile()
{
	OPENFILENAME ofn = { 0 };
	TCHAR strFile[MAX_PATH] = "";

	ofn.lStructSize = sizeof(OPENFILENAME);
	// 親ウィンドウハンドル(MFCではないのでnull)
	ofn.hwndOwner = nullptr;
	// ファイルフィルター
	ofn.lpstrFilter = TEXT("All files {*.*}\0*.*\0\0");
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

	if (GetOpenFileName(&ofn))
	{
		std::string full_path(strFile);
		return full_path;

	}

	return INVALID_TABLE::INVALID_FILE;
}