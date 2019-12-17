#include "./ShapeGLSolid.hpp"

void ShapeGLSolid::Execute() const
{
	/* 三角形で描画 */
	glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);
}
