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

	ImGui::Text("%.3fms/frame", 1000.0f / ImGui::GetIO().Framerate);

	ImGui::End();
}