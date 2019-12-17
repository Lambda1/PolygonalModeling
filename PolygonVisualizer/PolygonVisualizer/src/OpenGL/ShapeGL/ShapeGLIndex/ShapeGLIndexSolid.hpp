#ifndef __SHAPE_GL_INDEX_SOLID_HPP__
#define __SHAPE_GL_INDEX_SOLID_HPP__

/* インデックスを用いた三角形による描画 */

#include "./ShapeGLIndex.hpp"

class ShapeGLIndexSolid : public ShapeGLIndex
{
	public:
		ShapeGLIndexSolid(const GLsizei &vertex_count, const ObjectGL::Vertex *vertex, const GLsizei &index_count, const GLuint *index) :
			ShapeGLIndex(vertex_count, vertex, index_count, index)
	{
	}
		virtual ~ShapeGLIndexSolid(){}

		virtual void Execute() const;
};

#endif
