#ifndef __MATERIAL_GL_HPP__
#define __MATERIAL_GL_HPP__

/* NOTE: アライメントを使用 */

#include <array>
#include <GL/glew.h>

struct MaterialGL
{
	/* 反射係数 */
	alignas(16) std::array<GLfloat, 3> m_ambient;  /* 環境光 */
	alignas(16) std::array<GLfloat, 3> m_diffuse;  /* 拡散 */
	alignas(16) std::array<GLfloat, 3> m_specular; /* 鏡面 */

	alignas(4) GLfloat m_shininess; /* 輝き係数 */
};

#endif
