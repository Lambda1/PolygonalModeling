#ifndef __MAIN_CAMERA_GL_HPP__
#define __MAIN_CAMERA_GL_HPP__

#include "../OpenGL/MatrixGL/MatrixGL.hpp"
#include "../OpenGL/MathGL/MathGL.hpp"

#include "./MainCamera.hpp"

#include <GL/glew.h>

class MainCameraGL : public MainCamera<GLfloat>
{
public:
	MainCameraGL()
	{
	}
	~MainCameraGL()
	{
	}

	// ’‹“_‚ÉƒJƒƒ‰‚ğŒü‚¯‚é
	MatrixGL LookAt(const GLfloat &gaze_x, const GLfloat& gaze_y, const GLfloat& gaze_z) const
	{
		return MathGL::LookAt(x, y, z, gaze_x, gaze_y, gaze_z, up_x, up_y, up_z);
	}
	MatrixGL LookAt() const
	{
		return MathGL::LookAt(x, y, z, gx, gy, gz, up_x, up_y, up_z);
	}
};

#endif