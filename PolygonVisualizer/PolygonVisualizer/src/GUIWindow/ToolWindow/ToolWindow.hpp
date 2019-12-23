#ifndef __TOOL_WINDOW_HPP__
#define __TOOL_WINDOW_HPP__

#include "./ToolWindowDefine.hpp"
#include "../GUIWindow.hpp"
#include "../../MyMath/MyMath.hpp"
#include "../../ColorDefine/ImGuiColorDefine.hpp"
#include "../../MyModel/MyModel.hpp"
#include "../../MainCamera/MainCameraGL.hpp"

#include "../../imgui/imgui.h"

#define DEBUG_TOOL_WINDOW true

#if DEBUG_TOOL_WINDOW
	#include <GLFW/glfw3.h>
#endif

class ToolWindow : public GUIWindow
{
	// 定数
	inline static constexpr float ONE_MINUTE = 1000.0f;
	inline static constexpr float SLIDER_SPEED = 2.0f;
	inline static constexpr int UI_WIDTH_SIZE = 300;
	inline static constexpr int CAMERA_COORDINATE = 3;
	inline static constexpr float DRAG_MAX = 1000.0f;
	inline static constexpr float DRAG_RESOLUTION = 0.01f;

	// モデルデータ
	MyModel* m_model_data_ptr;
	// カメラデータ
	// NOTE: ツール側から編集する可能性があるので非const
	MainCameraGL* m_main_camera_ptr;
	// モデル行列設定
	// NOTE: 3ベクトル
	float m_translation[3], m_scale, m_rotate;
	bool  m_rotate_bits[3]; // 回転軸ビット
	// デモ用
	// NOTE: 最終的には使用しない
	bool m_is_demo;
	int  m_demo_step;

	// フレームレート表示
	void DisplayFrameRate() const;
	// モデルデータ表示
	void DisplayModelData() const;

	// カメラデータ更新
	void UpdateCamera();
	// モデルデータ更新
	void UpdateModel();
	// デバッグモード
	void DebugMode();

	// V-Sync
	void SwitchVSync() const;
	
	inline int BoolToInt(const bool& val) const { return (val) ? 1 : 0; }
public:
	ToolWindow();
	~ToolWindow();

	void Update() override;

	// Setter
	inline void SetModelData(MyModel* model_data) { m_model_data_ptr = model_data; }
	inline void SetMainCamera(MainCameraGL* camera) { m_main_camera_ptr = camera; }
};

#endif