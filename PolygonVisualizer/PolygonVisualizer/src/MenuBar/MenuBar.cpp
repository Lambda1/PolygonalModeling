#include "./MenuBar.hpp"

MenuBar::MenuBar():
	m_menu_flag(MENU_FLAGS::NONE)
{
	// ���j���[�e�[�u������
	InitTable();
}

MenuBar::~MenuBar()
{
}
// private
// �e�[�u��������
void MenuBar::InitTable()
{
	m_menu_table.emplace_back(&MenuBar::OpenModelFile);
	m_menu_table.emplace_back(&MenuBar::SaveModelFile);
}

// ���f���t�@�C���I�[�v��
void MenuBar::OpenModelFile()
{
	if (ImGui::MenuItem(FILE_MENU::OPEN_FILE))
	{
		m_open_file = WinFiler::SelectFile();
		// �t�@�C�����I������Ă���Ƃ�, �t���O�𗧂Ă�
		if (m_open_file.size() != 0) { m_menu_flag |= MENU_FLAGS::OPEN_FILE; }
	}
}
// �Z�[�u�t�@�C��
void MenuBar::SaveModelFile()
{
	if (ImGui::MenuItem(FILE_MENU::SAVE_FILE))
	{
		m_save_file = WinFiler::SaveFile();
		// �t�@�C�����I������Ă���Ƃ�, �t���O�𗧂Ă�
		if (m_open_file.size() != 0) { m_menu_flag |= MENU_FLAGS::SAVE_FILE; }
	}
}
// �t�@�C�����j���[
void MenuBar::FileMenu()
{
	if (ImGui::BeginMenu(FILE_MENU::BAR_NAME))
	{
		// ���j���[�e�[�u������e�������s��
		for (auto itr = m_menu_table.begin(); itr != m_menu_table.end(); ++itr) { (this->*(*itr))(); }
		ImGui::EndMenu();
	}
}

// public
void MenuBar::Update()
{
	// �t���O�N���A
	m_menu_flag = MENU_FLAGS::NONE;

	// ���C�����j���[�o�[����
	if (ImGui::BeginMainMenuBar())
	{
		// �t�@�C�����j���[
		FileMenu();

		// ���j���[�o�[�I������
		ImGui::EndMainMenuBar();
	}
}