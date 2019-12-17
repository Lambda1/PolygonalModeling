#include "./ShapeGLIndex.hpp"

void ShapeGLIndex::Execute() const
{
	/* 図形種類, 頂点数, インデックスの型, インデックスデータの格納場所(先頭からなら0) */
	glDrawElements(GL_LINES, m_index_count, GL_UNSIGNED_INT, 0);
}
