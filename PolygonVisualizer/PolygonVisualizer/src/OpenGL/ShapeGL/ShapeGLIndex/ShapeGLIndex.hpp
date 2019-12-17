#ifndef __SHAPE_GL_INDEX_HPP__
#define __SHAPE_GL_INDEX_HPP__

/* インデックスによる3次元図形の描画 */

#include "../ShapeGL.hpp"

class ShapeGLIndex : public ShapeGL
{
	protected:
		const GLsizei m_index_count; /* 頂点数 */

	public:
		/* 頂点数, 頂点属性の配列, 頂点インデックスの要素数, 頂点インデックスを格納した配列 */
		ShapeGLIndex(const GLsizei &vertex_count, const ObjectGL::Vertex *vertex, const GLsizei &index_count, const GLuint *index) :
			ShapeGL(vertex_count, vertex, index_count, index), m_index_count(index_count)
	{
	}
		virtual ~ShapeGLIndex(){}

		virtual void Execute() const;
};

#endif
