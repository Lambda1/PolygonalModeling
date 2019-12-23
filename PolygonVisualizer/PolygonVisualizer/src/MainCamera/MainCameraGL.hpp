#ifndef __MAIN_CAMERA_GL_HPP__
#define __MAIN_CAMERA_GL_HPP__

#include "../OpenGL/MatrixGL/MatrixGL.hpp"
#include "../OpenGL/MathGL/MathGL.hpp"

#include "./MainCamera.hpp"

#include <GL/glew.h>

class MainCameraGL : public MainCamera<GLfloat>
{
public:
	inline static constexpr float MAX_FOV_F = static_cast<GLfloat>(MAX_FOV);
	inline static constexpr float MIN_FOV_F = static_cast<GLfloat>(MIN_FOV);
private:
	// カメラ位置の閾値
	GLfloat m_max_pos, m_min_pos;

	// 座標へのポインタ
	GLfloat *m_pos_ptr[3];
	GLfloat *m_gaze_ptr[3];
public:
	MainCameraGL():
		m_max_pos(0.0f), m_min_pos(0.0f)
	{
		// 位置
		m_pos_ptr[0] = &(this->x);
		m_pos_ptr[1] = &(this->y);
		m_pos_ptr[2] = &(this->z);
		//m_pos_ptr[3] = &(this->w);
		// 注視点
		m_gaze_ptr[0] = &(this->gx);
		m_gaze_ptr[1] = &(this->gy);
		m_gaze_ptr[2] = &(this->gz);
	}
	~MainCameraGL()
	{
	}

	// 原点リセット
	inline void ResetPos() { x = y = z = 0.0f; }
	inline void ResetGaze() { gx = gy = gz = 0.0f; }

	// 注視点にカメラを向ける
	inline MatrixGL LookAt(const GLfloat &gaze_x, const GLfloat& gaze_y, const GLfloat& gaze_z) const
	{
		return MathGL::LookAt(x, y, z, gaze_x, gaze_y, gaze_z, up_x, up_y, up_z);
	}
	inline MatrixGL LookAt() const
	{
		return MathGL::LookAt(x, y, z, gx, gy, gz, up_x, up_y, up_z);
	}

	// Setter
	inline void SetMaxPos(const GLfloat& max) { m_max_pos = max; }
	inline void SetMinPos(const GLfloat& min) { m_min_pos = min; }

	// Getter
	inline GLfloat* GetPosPtr() { return *m_pos_ptr; }
	inline GLfloat* GetGazePtr() { return *m_gaze_ptr; }
	inline GLfloat* GetFovPtr() { return &fov; }
	inline GLfloat GetMaxPos() const { return m_max_pos; }
	inline GLfloat GetMinPos() const { return m_min_pos; }
};

#endif