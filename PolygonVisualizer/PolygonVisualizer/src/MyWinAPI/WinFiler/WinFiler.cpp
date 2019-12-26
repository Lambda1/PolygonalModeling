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
	// �e�E�B���h�E�n���h��(MFC�ł͂Ȃ��̂�null)
	ofn.hwndOwner = nullptr;
	// �t�@�C���t�B���^�[
	ofn.lpstrFilter =
		TEXT("Wavefront {*.obj}\0*.obj\0")
		TEXT("Point Cloud {*.pcd}\0*.pcd\0")
		TEXT("4-byte binary {*.bin4}\0*.bin4\0");
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

	return ofn;
}

// public
/*
	�Z���N�g�t�@�C��
	NOTE: �I�����ꂽ�t�@�C���̃t���p�X��Ԃ�, �Ȃ��ꍇ�͋󔒂�Ԃ�.
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
	�Z�[�u�t�@�C��
	NOTE: �I�����ꂽ�t�@�C���̃t���p�X��Ԃ�, �Ȃ��ꍇ�͋󔒂�Ԃ�.
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