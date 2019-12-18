#ifndef __SPHERE_GL_HPP__
#define __SPHERE_GL_HPP__

#include "../ObjectGL/ObjectGL.hpp"

#include <GL/glew.h>

#include <iostream>
#include <cmath>
#include <vector>

class SphereGL
{
	inline static constexpr GLfloat PI = 3.14159f;

	int m_slices, m_stacks; /* 球の分割数 */
	std::vector<ObjectGL::Vertex> m_vertex; /* 頂点 */
	std::vector<GLuint> m_index; /* 頂点インデックス */

	void Make();
	void MakeIndex();

	public:
	SphereGL(const int &slices = 16, const int &stacks = 8):
		m_slices(slices), m_stacks(stacks)
	{
		Make();
		MakeIndex();
	}
	~SphereGL()
	{
	}

	/* Getter */
	inline const ObjectGL::Vertex *GetVertex() const { return m_vertex.data(); }
	inline const int GetVertexSize() const { return static_cast<int>(m_vertex.size()); }
	inline const GLuint *GetIndex() const { return m_index.data(); }
	inline const int GetIndexSize() const { return static_cast<int>(m_index.size()); }
};

#endif