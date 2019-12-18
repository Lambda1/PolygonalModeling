#ifndef __CUBE_GL_HPP__
#define __CUBE_GL_HPP__

/* 大きさrateの直方体 */

#include "../ObjectGL/ObjectGL.hpp"

#include <GL/glew.h>

#include <vector>

class CubeGL
{
	inline static constexpr int vertex_num = 36; /* 頂点数 */
	inline static constexpr int surface_vertex_num = 6; /* 1面当たりの頂点数 */
	inline static constexpr GLfloat length = 0.5f;

	std::vector<ObjectGL::Vertex> m_vertex; /* 頂点(3)+法線(3) */
	std::vector<GLuint> m_index; /* 頂点インデックス */

	void Make(const GLfloat &rate = 1.0f);
	void MakeIndex();

	public:
	CubeGL();
	CubeGL(const GLfloat &leng);
	~CubeGL();

	/* Getter */
	inline const ObjectGL::Vertex *GetVertex() const { return m_vertex.data(); }
	inline const int GetVertexSize() const { return static_cast<int>(m_vertex.size()); }
	inline const GLuint *GetIndex() const { return m_index.data(); }
	inline const int GetIndexSize() const { return static_cast<int>(m_index.size()); }
};

#endif
