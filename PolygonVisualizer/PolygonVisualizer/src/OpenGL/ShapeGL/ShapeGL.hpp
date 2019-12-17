#ifndef __SHAPE_GL_HPP__
#define __SHAPE_GL_HPP__

#include "../ObjectGL/ObjectGL.hpp"

#include <memory>

class ShapeGL
{
	std::shared_ptr<ObjectGL> m_object;

	protected:
	const GLsizei m_vertex_count;

	public:
	ShapeGL(const GLsizei vertex_count,const ObjectGL::Vertex *vertex,const GLsizei &index_count = 0, const GLuint *index = nullptr) :
		m_object(new ObjectGL(vertex_count, vertex, index_count, index)), m_vertex_count(vertex_count)
	{
	}
	ShapeGL();
	virtual ~ShapeGL();

	virtual void Execute() const;
	void Draw() const;

	/* ObjectGLの機能呼び出し */
	inline void VertexAttribPointer(const GLint &vertex_id,const GLint &color_id) { m_object->VertexAttribPointer(vertex_id, color_id); }
	inline void VertexAttribPointer(const GLint &id){ m_object->VertexAttribPointer(id); }
	inline void EnableVertexAttribArray(const GLint &id){ m_object->EnableVertexAttribArray(id); }
};

#endif
