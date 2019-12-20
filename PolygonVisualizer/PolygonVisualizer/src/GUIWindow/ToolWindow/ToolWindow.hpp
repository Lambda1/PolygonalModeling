#ifndef __TOOL_WINDOW_HPP__
#define __TOOL_WINDOW_HPP__

#include "../GUIWindow.hpp"
#include "./ToolWindowDefine.hpp"
#include "../../MyModel/MyModel.hpp"

#include "../../imgui/imgui.h"

class ToolWindow : public GUIWindow
{
	// 定数
	inline static float ONE_MINUTE = 1000.0f;

	// モデルデータ
	const MyModel* m_model_data_ptr;

	// 表示処理
	void DisplayFrameRate();
	// モデルデータ表示
	void DisplayModelData();
public:
	ToolWindow();
	~ToolWindow();

	void Update() override;

	// Setter
	inline void SetModelData(const MyModel* model_data) { m_model_data_ptr = model_data; }
};

#endif