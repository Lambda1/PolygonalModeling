#ifndef __SHAPE_GL_SOLID_HPP__
#define __SHAPE_GL_SOLID_HPP__

/* 立体を三角形の集合で描画 */

#include "../ShapeGL.hpp"

class ShapeGLSolid : public ShapeGL
{
	public:
		ShapeGLSolid(const GLsizei &vertex_count, const ObjectGL::Vertex *vertex) :
			ShapeGL(vertex_count, vertex)
	{
	}
	virtual ~ShapeGLSolid()
	{
	}
	
	virtual void Execute() const;
};

#endif
