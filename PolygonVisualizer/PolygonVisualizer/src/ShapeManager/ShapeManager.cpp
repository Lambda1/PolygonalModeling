#include "./ShapeManager.hpp"

ShapeManager::ShapeManager()
{
}

ShapeManager::~ShapeManager()
{
}

// public
// ÉÅÉÇÉäâï˙
void ShapeManager::DiposeMemory()
{
	m_shape.clear();
	m_shape.shrink_to_fit();
}
void ShapeManager::DiposeMemoryPop()
{

}
/* ê}å`ÇÃìoò^ */
void ShapeManager::SetShape(const ObjectGL::Vertex* data, const int& size, const GLint& position_id, const GLint& normal_id)
{
	m_shape.emplace_back(new ShapeGLSolid(static_cast<GLsizei>(size), data));
	m_shape.back()->VertexAttribPointer(position_id, normal_id);
}
// ÉèÉCÉÑìoò^
void ShapeManager::SetShapeWire(const ObjectGL::Vertex* vertex_data, const int& vertex_size, const GLint& position_id, const GLint& normal_id)
{
	m_shape.emplace_back(new ShapeGL(static_cast<GLsizei>(vertex_size), vertex_data));
	m_shape.back()->VertexAttribPointer(position_id, normal_id);
}
void ShapeManager::SetShapeWire(const ObjectGL::Vertex* vertex_data, const int& vertex_size, const GLint& position_id)
{
	m_shape.emplace_back(new ShapeGL(static_cast<GLsizei>(vertex_size), vertex_data));
	m_shape.back()->VertexAttribPointer(position_id);
}
void ShapeManager::SetShapeWireIndex(const ObjectGL::Vertex* vertex_data, const int& vertex_size, const GLuint* index_data, const GLint& index_size, const GLint& position_id, const GLint& normal_id)
{
	m_shape.emplace_back(new ShapeGLIndex(static_cast<GLsizei>(vertex_size), vertex_data, static_cast<GLsizei>(index_size), index_data));
	m_shape.back()->VertexAttribPointer(position_id, normal_id);
}
void ShapeManager::SetShapeParticle(const ObjectGL::Vertex* data, const int& size, const GLint& position_id)
{
	m_shape.emplace_back(new ShapeGLParticle(static_cast<GLsizei>(size), data));
	m_shape.back()->VertexAttribPointer(position_id);
}