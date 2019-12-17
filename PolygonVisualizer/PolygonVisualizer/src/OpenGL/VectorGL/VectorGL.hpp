#ifndef __VECTOR_GL_HPP__
#define __VECTOR_GL_HPP__

#include <GL/glew.h>

#include <array>

namespace VectorGL
{
	inline static constexpr int m_dim = 4; /* 同次座標 & RGBA */
	using Vector = std::array<GLfloat, VectorGL::m_dim>;
};

#endif
