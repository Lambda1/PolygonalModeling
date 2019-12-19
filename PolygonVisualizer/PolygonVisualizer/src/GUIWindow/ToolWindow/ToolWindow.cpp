#include "./ToolWindow.hpp"

ToolWindow::ToolWindow()
{
}

ToolWindow::~ToolWindow()
{
}
// private
void ToolWindow::DisplayFrameRate()
{
	float frame_rate = ImGui::GetIO().Framerate;
	ImGui::Text("Frame Rate:");
	ImGui::Text("%.2f[fps] (%.3f[ms/frame])", frame_rate, ONE_MINUTE / frame_rate);
}

// public
void ToolWindow::Update()
{
	ImGui::Begin(TOOL_WINDOW_DEFINE::WINDOW_NAME);

	ImGui::Separator();
	DisplayFrameRate();

	ImGui::End();
}