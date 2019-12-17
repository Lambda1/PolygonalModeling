#include "./ShapeGLIndexSolid.hpp"

void ShapeGLIndexSolid::Execute() const
{
	/* 三角形描画 */
	glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0);
}
