#include "./MenuBar.hpp"

MenuBar::MenuBar():
	m_menu_flag(MENU_FLAGS::NONE)
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
		m_open_file = WinFiler::SelectFile();
		// ファイルが選択されているとき, フラグを立てる
		if (m_open_file.size() != 0) { m_menu_flag |= MENU_FLAGS::OPEN_FILE; }
	}
}
// セーブファイル
void MenuBar::SaveModelFile()
{
	if (ImGui::MenuItem(FILE_MENU::SAVE_FILE))
	{
		m_save_file = WinFiler::SaveFile();
		// ファイルが選択されているとき, フラグを立てる
		if (m_open_file.size() != 0) { m_menu_flag |= MENU_FLAGS::SAVE_FILE; }
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
	// フラグクリア
	m_menu_flag = MENU_FLAGS::NONE;

	// メインメニューバー処理
	if (ImGui::BeginMainMenuBar())
	{
		// ファイルメニュー
		FileMenu();

		// メニューバー終了処理
		ImGui::EndMainMenuBar();
	}
}