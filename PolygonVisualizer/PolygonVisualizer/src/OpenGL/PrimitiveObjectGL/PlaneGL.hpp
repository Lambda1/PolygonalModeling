#ifndef __PLANE_GL_HPP__
#define __PLANE_GL_HPP__

#include "../ObjectGL/ObjectGL.hpp"

#include <GL/glew.h>

#include <vector>

class PlaneGL
{
	inline static constexpr int vertex_num = 6; /* 頂点数 */
	inline static constexpr GLfloat length = 0.5f;

	std::vector<ObjectGL::Vertex> m_vertex; /* 頂点(3)+法線(3) */
	std::vector<GLuint> m_index; /* 頂点インデックス */

	void Make(const GLfloat &rate);
	void MakeIndex();

	public:
	PlaneGL();
	PlaneGL(const GLfloat &size);
	~PlaneGL();

	/* Getter */
	inline const ObjectGL::Vertex *GetVertex() const { return m_vertex.data(); }
	inline const int GetVertexSize() const { return static_cast<int>(m_vertex.size()); }
	inline const GLuint *GetIndex() const { return m_index.data(); }
	inline const int GetIndexSize() const { return static_cast<int>(m_index.size()); }

};

#endif
