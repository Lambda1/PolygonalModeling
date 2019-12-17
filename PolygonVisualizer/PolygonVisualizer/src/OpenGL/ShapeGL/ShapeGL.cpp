#include "./ShapeGL.hpp"

ShapeGL::ShapeGL() :
	m_vertex_count(0)
{
}

ShapeGL::~ShapeGL()
{
}

void ShapeGL::Execute() const
{
	glDrawArrays(GL_LINE_LOOP, 0, m_vertex_count);
}

void ShapeGL::Draw() const
{
	m_object->Bind();
	Execute();
	m_object->UnBind();
}
