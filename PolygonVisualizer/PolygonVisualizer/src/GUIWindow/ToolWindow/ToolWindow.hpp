#ifndef __TOOL_WINDOW_HPP__
#define __TOOL_WINDOW_HPP__

#include "./ToolWindowDefine.hpp"
#include "../GUIWindow.hpp"
#include "../../MyMath/MyMath.hpp"
#include "../../ColorDefine/ImGuiColorDefine.hpp"
#include "../../MyModel/MyModel.hpp"
#include "../../MainCamera/MainCameraGL.hpp"

#include "../../imgui/imgui.h"

class ToolWindow : public GUIWindow
{
	// 定数
	inline static constexpr float ONE_MINUTE = 1000.0f;
	inline static constexpr int UI_WIDTH_SIZE = 300;
	inline static constexpr int CAMERA_COORDINATE = 3;

	// モデルデータ
	const MyModel* m_model_data_ptr;
	// カメラデータ
	// NOTE: ツール側から編集する可能性があるので非const
	MainCameraGL* m_main_camera_ptr;

	// フレームレート表示
	void DisplayFrameRate() const;
	// モデルデータ表示
	void DisplayModelData() const;

	// カメラデータ更新
	void UpdateCamera();
public:
	ToolWindow();
	~ToolWindow();

	void Update() override;

	// Setter
	inline void SetModelData(const MyModel* model_data) { m_model_data_ptr = model_data; }
	inline void SetMainCamera(MainCameraGL* camera) { m_main_camera_ptr = camera; }
};

#endif