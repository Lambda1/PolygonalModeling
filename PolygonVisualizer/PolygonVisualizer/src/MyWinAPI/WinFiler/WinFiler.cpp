#include "./WinFiler.hpp"

WinFiler::WinFiler()
{
}

WinFiler::~WinFiler()
{
}

// public
/*
	�t�@�C���Z���N�g
	NOTE: �I�����ꂽ�t�@�C���̃t���p�X��Ԃ�, �Ȃ��ꍇ�͋󔒂�Ԃ�.
*/
std::string WinFiler::SelectFile()
{
	OPENFILENAME ofn = { 0 };
	TCHAR strFile[MAX_PATH] = "";

	ofn.lStructSize = sizeof(OPENFILENAME);
	// �e�E�B���h�E�n���h��(MFC�ł͂Ȃ��̂�null)
	ofn.hwndOwner = nullptr;
	// �t�@�C���t�B���^�[
	ofn.lpstrFilter = TEXT("All files {*.*}\0*.*\0\0");
	// ���[�U��`�t�B���^
	ofn.lpstrCustomFilter = nullptr;
	// ���[�U��`�t�B���^��
	ofn.nMaxCustFilter = 0;
	// lpstrFilter�Œ�`���ꂽ���̂��牽�Ԗڂ��f�t�H�ɂ��邩
	ofn.nFilterIndex = 0;
	// �J�����ۂɓ��͂����o�b�t�@(�K�����������邱��)
	ofn.lpstrFile = strFile;
	// lpstrFile��
	ofn.nMaxFile = MAX_PATH;
	// �����t�@�C���̂ݑI����
	ofn.Flags = OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		std::string full_path(strFile);
		return full_path;

	}

	return INVALID_TABLE::INVALID_FILE;
}