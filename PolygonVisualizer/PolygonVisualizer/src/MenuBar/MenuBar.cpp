#include "./MenuBar.hpp"

MenuBar::MenuBar()
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
		std::cout << WinFiler::SelectFile() << std::endl;
	}
}
void MenuBar::SaveModelFile()
{
	if (ImGui::MenuItem(FILE_MENU::SAVE_FILE))
	{
		std::cout << WinFiler::SaveFile() << std::endl;
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
	// ���C�����j���[�o�[����
	if (ImGui::BeginMainMenuBar())
	{
		// �t�@�C�����j���[
		FileMenu();

		ImGui::EndMainMenuBar();
	}
}