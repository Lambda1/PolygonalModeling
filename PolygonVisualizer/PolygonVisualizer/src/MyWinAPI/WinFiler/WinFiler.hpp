#ifndef __WIN_FILER_HPP__
#define __WIN_FILER_HPP__

/*
	�t�@�C���_�C�A���O�N���X
	NOTE: �葱���̂ݍs������, �ÓI�N���X�Ƃ���.
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

	// �t�@�C�����ʃ_�C�A���O
	static OPENFILENAME CommonDialog();
public:
	// �R�s�[�֎~
	WinFiler(const WinFiler&) = delete;
	WinFiler& operator=(const WinFiler&) = delete;

	~WinFiler();

	// �I�[�v���_�C�A���O
	static std::string SelectFile();
	// �Z�[�u�_�C�A���O
	static std::string SaveFile();
};

#endif