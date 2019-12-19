#include "./ShapeManager.hpp"

ShapeManager::ShapeManager()
{
}

ShapeManager::~ShapeManager()
{
}

// public
/* ê}å`ÇÃìoò^ */
void ShapeManager::SetShape(const ObjectGL::Vertex* data, const int& size, const GLint& position_id, const GLint& normal_id)
{
	m_shape.emplace_back(new ShapeGLSolid(static_cast<GLsizei>(size), data));
	m_shape.back()->VertexAttribPointer(position_id, normal_id);
}
void ShapeManager::SetShapeParticle(const ObjectGL::Vertex* data, const int& size, const GLint& position_id)
{
	m_shape.emplace_back(new ShapeGLParticle(static_cast<GLsizei>(size), data));
	m_shape.back()->VertexAttribPointer(position_id);
}