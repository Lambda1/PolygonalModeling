#include "./ShapeGLParticle.hpp"

void ShapeGLParticle::Execute() const
{
	glDrawArrays(GL_POINTS, 0, m_vertex_count);
}
