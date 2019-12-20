#ifndef __TOOL_WINDOW_HPP__
#define __TOOL_WINDOW_HPP__

#include "./ToolWindowDefine.hpp"
#include "../GUIWindow.hpp"
#include "../../ColorDefine/ImGuiColorDefine.hpp"
#include "../../MyModel/MyModel.hpp"

#include "../../imgui/imgui.h"

class ToolWindow : public GUIWindow
{
	// �萔
	inline static float ONE_MINUTE = 1000.0f;

	// ���f���f�[�^
	const MyModel* m_model_data_ptr;

	// �\������
	void DisplayFrameRate();
	// ���f���f�[�^�\��
	void DisplayModelData();
public:
	ToolWindow();
	~ToolWindow();

	void Update() override;

	// Setter
	inline void SetModelData(const MyModel* model_data) { m_model_data_ptr = model_data; }
};

#endif