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
	// �萔
	inline static constexpr float ONE_MINUTE = 1000.0f;
	inline static constexpr float SLIDER_SPEED = 2.0f;
	inline static constexpr int UI_WIDTH_SIZE = 300;
	inline static constexpr int CAMERA_COORDINATE = 3;
	inline static constexpr float DRAG_MAX = 1000.0f;
	inline static constexpr float DRAG_RESOLUTION = 0.01f;

	// ���f���f�[�^
	MyModel* m_model_data_ptr;
	// �J�����f�[�^
	// NOTE: �c�[��������ҏW����\��������̂Ŕ�const
	MainCameraGL* m_main_camera_ptr;
	// ���f���s��ݒ�
	// NOTE: 3�x�N�g��
	float m_translation[3], m_scale, m_rotate[3];

	// �t���[�����[�g�\��
	void DisplayFrameRate() const;
	// ���f���f�[�^�\��
	void DisplayModelData() const;

	// �J�����f�[�^�X�V
	void UpdateCamera();
	// ���f���f�[�^�X�V
	void UpdateModel();
public:
	ToolWindow();
	~ToolWindow();

	void Update() override;

	// Setter
	inline void SetModelData(MyModel* model_data) { m_model_data_ptr = model_data; }
	inline void SetMainCamera(MainCameraGL* camera) { m_main_camera_ptr = camera; }
};

#endif