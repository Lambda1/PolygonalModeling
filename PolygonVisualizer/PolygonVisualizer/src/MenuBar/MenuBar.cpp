#include "./MenuBar.hpp"

MenuBar::MenuBar()
{
	// メニューテーブル生成
	InitTable();
}

MenuBar::~MenuBar()
{
}
// private
// テーブル初期化
void MenuBar::InitTable()
{
	m_menu_table.emplace_back(&MenuBar::OpenModelFile);
	m_menu_table.emplace_back(&MenuBar::SaveModelFile);
}

// モデルファイルオープン
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
// ファイルメニュー
void MenuBar::FileMenu()
{
	if (ImGui::BeginMenu(FILE_MENU::BAR_NAME))
	{
		// メニューテーブルから各処理を行う
		for (auto itr = m_menu_table.begin(); itr != m_menu_table.end(); ++itr) { (this->*(*itr))(); }
		ImGui::EndMenu();
	}
}

// public
void MenuBar::Update()
{
	// メインメニューバー処理
	if (ImGui::BeginMainMenuBar())
	{
		// ファイルメニュー
		FileMenu();

		ImGui::EndMainMenuBar();
	}
}