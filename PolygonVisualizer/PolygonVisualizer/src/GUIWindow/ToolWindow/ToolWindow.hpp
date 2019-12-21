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
	inline static float ONE_MINUTE = 1000.0f;

	// モデルデータ
	const MyModel* m_model_data_ptr;
	// カメラデータ
	// NOTE: ツール側から編集する可能性があるので非const
	MainCameraGL* m_main_camera_ptr;

	// 表示処理
	void DisplayFrameRate() const;
	// モデルデータ表示
	void DisplayModelData() const;
	// カメラ設定表示
	void DisplayCameaInfo() const;
public:
	ToolWindow();
	~ToolWindow();

	void Update() override;

	// Setter
	inline void SetModelData(const MyModel* model_data) { m_model_data_ptr = model_data; }
	inline void SetMainCamera(MainCameraGL* camera) { m_main_camera_ptr = camera; }
};

#endif