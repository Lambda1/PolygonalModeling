#ifndef __OBJECT_GL_HPP__
#define __OBJECT_GL_HPP__

#include "../../DebugInfo.hpp"

#include <GL/glew.h>

#include <iostream>

class ObjectGL
{
	GLuint m_vao, m_vbo, m_ibo;

	inline static constexpr int m_dim = 3; /* 3次元 */
	inline static constexpr int m_nor = 3; /* 法線ベクトル(RGB) */

	public:
	struct Vertex
	{
		GLfloat position[m_dim]; /* 位置 */
		GLfloat normal[m_nor];   /* 法線 */
	};

	/* 次元, 頂点数, 頂点属性の配列, 頂点インデックスの要素数, 頂点インデックスの配列 */
	ObjectGL(const GLsizei v_count,const Vertex *vertex, const GLsizei index_count = 0, const GLuint *index = nullptr);
	virtual ~ObjectGL();

	ObjectGL(const ObjectGL &) = delete;
	ObjectGL& operator=(const ObjectGL &rhs) = delete;

	inline void Bind() const { glBindVertexArray(m_vao); }
	inline void UnBind() const { glBindVertexArray(0); }

	/* 結合されているVBOをin変数から参照可能にする */
	/* NOTE: VAOの有効化まで行う */
	inline void VertexAttribPointer(const GLint &vertex_id,const GLint &normal_id)
	{
		/* 頂点 */
		glVertexAttribPointer(vertex_id, m_dim, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->position);
		glEnableVertexAttribArray(vertex_id);
		/* 法線 */
		glVertexAttribPointer(normal_id, m_nor, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->normal);
		glEnableVertexAttribArray(normal_id);

		glBindVertexArray(0); /* VAO解除 */
	}
	// 頂点データのみ
	inline void VertexAttribPointer(const GLint& vertex_id)
	{
		/* 頂点 */
		glVertexAttribPointer(vertex_id, m_dim, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->position);
		glEnableVertexAttribArray(vertex_id);

		glBindVertexArray(0); /* VAO解除 */
	}
	inline void VertexAttribPointerSimple(const GLint &id){ glVertexAttribPointer(id, m_dim, GL_FLOAT, GL_FALSE, 0, 0); }
	inline void EnableVertexAttribArray(const GLint &id){ glEnableVertexAttribArray(id); }
};

#endif
