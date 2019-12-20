#ifndef __GUI_MANAGER_HPP__
#define __GUI_MANAGER_HPP__

#include "./GUIManagerDefine.hpp"
#include "../MenuBar/MenuBar.hpp"
#include "../GUIWindow/ToolWindow/ToolWindow.hpp"
#include "../MyModel/MyModel.hpp"
#include "../MainCamera/MainCameraGL.hpp"

#include <iostream>
#include <string>

class GUIManager
{
	// GUI処理変数
	MenuBar m_menu_bar;
	ToolWindow* m_tool_window;
	// ファイル処理
	std::string m_file_name; // OpenとSaveで共用
	// 処理フラグ
	GUI_MANAGER_DEFINE::FLAGS m_gui_flags;
	// MyViewerとの連携
	const MyModel *m_model_data_ptr; // モデルデータへのポインタ

	// 初期化処理
	void InitGUI();

	// メニューバー処理
	void ProcessMenuBar();
public:
	GUIManager();
	~GUIManager();

	// 更新
	void Update();

	// 仲介処理
	// ToolWindowへカメラポインタを渡す
	void MediationCameraPtrToToolWindow(MainCameraGL *camera);

	// Setter
	// モデルデータのセット
	// NOTE: ToolWindowも同時更新
	inline void SetModelData(const MyModel* model_data)
	{
		m_model_data_ptr = model_data;
		m_tool_window->SetModelData(model_data);
	}

	// Getter
	// GUI Managerフラグ
	inline GUI_MANAGER_DEFINE::FLAGS GetGUIFlags() const { return m_gui_flags; }
	// ファイルネーム
	inline std::string GetFileName() const { return m_file_name; }
	// モデルデータ
	inline const MyModel* GetModelData() const { return m_model_data_ptr; };
};

#endif