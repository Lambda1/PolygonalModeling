#ifndef __WIN_FILER_HPP__
#define __WIN_FILER_HPP__

/*
	ファイルダイアログクラス
	NOTE: 手続きのみ行うため, 静的クラスとする.
*/

#include <Windows.h>
#include <string>

class WinFiler
{
public:
	struct INVALID_TABLE
	{
	public:
		INVALID_TABLE() = delete;
		INVALID_TABLE(const INVALID_TABLE&) = delete;
		INVALID_TABLE& operator=(const INVALID_TABLE&) = delete;
		inline static const std::string INVALID_FILE = "";
	};
private:
	WinFiler();

	// ファイル共通ダイアログ
	static OPENFILENAME CommonDialog();
public:
	// コピー禁止
	WinFiler(const WinFiler&) = delete;
	WinFiler& operator=(const WinFiler&) = delete;

	~WinFiler();

	// オープンダイアログ
	static std::string SelectFile();
	// セーブダイアログ
	static std::string SaveFile();
};

#endif