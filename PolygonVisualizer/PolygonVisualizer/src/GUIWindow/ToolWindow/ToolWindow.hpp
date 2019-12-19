#ifndef __TOOL_WINDOW_HPP__
#define __TOOL_WINDOW_HPP__

#include "../GUIWindow.hpp"
#include "./ToolWindowDefine.hpp"

#include "../../imgui/imgui.h"

class ToolWindow : public GUIWindow
{
	// �萔
	inline static float ONE_MINUTE = 1000.0f;

	// �\������
	void DisplayFrameRate();
public:
	ToolWindow();
	~ToolWindow();

	void Update() override;
};

#endif