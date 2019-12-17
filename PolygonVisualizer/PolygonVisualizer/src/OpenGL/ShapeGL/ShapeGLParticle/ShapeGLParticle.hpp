#ifndef __SHAPE_GL_PARTICLE_HPP__
#define __SHAPE_GL_PARTICLE_HPP__

/* 点で描画 */

#include "../ShapeGL.hpp"

class ShapeGLParticle : public ShapeGL
{
	public:
		ShapeGLParticle(const GLsizei &vertex_count, const ObjectGL::Vertex *vertex) :
			ShapeGL(vertex_count, vertex)
	{
	}
	virtual ~ShapeGLParticle()
	{
	}
	
	virtual void Execute() const;
};

#endif
