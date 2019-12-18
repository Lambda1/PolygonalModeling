#ifndef __TOOL_WINDOW_HPP__
#define __TOOL_WINDOW_HPP__

#include "../GUIWindow.hpp"
#include "./ToolWindowDefine.hpp"

#include "../../imgui/imgui.h"

class ToolWindow : public GUIWindow
{
public:
	ToolWindow();
	~ToolWindow();

	void Update() override;
};

#endif