#include "./ToolWindow.hpp"

ToolWindow::ToolWindow()
{
}

ToolWindow::~ToolWindow()
{
}

void ToolWindow::Update()
{
	ImGui::Begin(TOOL_WINDOW_DEFINE::WINDOW_NAME);

	ImGui::End();
}